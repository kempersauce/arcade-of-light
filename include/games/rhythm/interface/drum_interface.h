#pragma once

#include "audio/beat_patterns/all.h"                  // for all beat patterns
#include "audio/beat_patterns/chachacha.h"            // for Chachacha
#include "audio/constants.h"                          // for k*
#include "audio/score.h"                              // for Score
#include "audio/track.h"                              // for AudioTrack
#include "controls/button.h"                          // for Button
#include "controls/rhythm.h"                          // for RhythmController
#include "games/rhythm/interface/player_interface.h"  // for PlayerInterface
#include "math/random.h"                              // for random::*
#include "serial/hw_serials.h"                        // for kHwSerials

namespace kss {
namespace games {
namespace rhythm {

class DrumInterface : public PlayerInterface {
  static constexpr size_t num_beats{6};
  audio::Score* beat_scores[num_beats]{
    // Ghost only
      &audio::beats::Reggae,
      &audio::beats::Procession, // not this one
      
      &audio::beats::BootsAndCats,   // Down
      &audio::beats::Procession, // Left
      &audio::beats::Fiddy, // Right
      &audio::beats:: Florian,  // Up
  };

  audio::AudioTrack track{&audio::beats::BootsAndCats};

 public:
  DrumInterface(controls::RhythmController* controller, uint8_t serial_no)
      : PlayerInterface(controller, serial_no) {}

  void Start() override { track.Play(); }

  void Update() override {
    for (uint8_t i = 0; i < controller->button_count; ++i) {
      auto butt = controller->buttons[i];
      // Play drum sounds with A+B
      if (butt == controller->a || butt == controller->b) {
        if (butt->IsDepressing()) {
          synth.StartInput(i);
        }
        if (butt->IsReleasing()) {
          synth.StopInput(i);
        }
      }

      // Joystick selects drum track
      else {
        if (butt->IsDepressing()) {
          Debug("beat index" + i);
          track.SwitchImmediatelyTo(beat_scores[i]);
        }
      }
    }

    // Ghost drummer plays!
    static uint32_t last_check_time{time::Now()};
    static const uint32_t check_time_delay_millis{1000};
    if (controller->IsIdle()) {
      // Debug("Drummer is Idle! Go Go Gadget Ghost Drummer");
      if (time::Now() - last_check_time > check_time_delay_millis) {
        // if (math::random::Bool(0.2)) {
        //   const uint8_t beat_index = math::random::Int8(num_beats);
        //   Debug("Ghost Drummer Switching tracks to beat_index " + beat_index);
        //   track.SwitchImmediatelyTo(beat_scores[math::random::Int8(num_beats)]);
        // }
        last_check_time =
            time::Now() - math::random::Int16(check_time_delay_millis);
      }
    }

    // Play the drum track
    track.Update();
    while (track.HasNotes()) {
      uint8_t note = track.GetNextNote();
      // Don't play the notes associated with the A+B buttons
      // Unless we're idling, then let ghost drummer play
      if (!controller->IsIdle() &&
          (note == audio::kAChannelNum || note == audio::kBChannelNum)) {
        // Debug("Skipping A+B when not idle");
        continue;
      }

      synth.StartInput(note);
    }
  }
};

}  // namespace rhythm
}  // namespace games
}  // namespace kss
