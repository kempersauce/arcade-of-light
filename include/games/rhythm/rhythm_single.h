#pragma once

#include <vector>  // for vector

#include "animation/animation.h"                // for Animation
#include "animation/exploder.h"                 // for Exploder
#include "animation/explosion.h"                // for Explosion
#include "animation/single_color_background.h"  // for SingleColorBG
#include "animation/starscape.h"                // for Starscape
#include "audio/synth_sender_raw.h"             // for SynthSenderRaw
#include "controls/rhythm.h"                    // for RhythmController
#include "games/game.h"                         // for Game
#include "math/random.h"                        // for random::*
#include "serial/debug.h"                       // for Debug
#include "serial/hw_serials.h"                  // for kHwSerials
#include "time/now.h"                           // for Now

namespace kss {
namespace games {
namespace rhythm {

namespace _rhythm_single {
constexpr float bpm{120};
constexpr uint32_t beat_length_millis{1000 * 60 / bpm};

constexpr uint32_t beat_proximity_threshold{100};
constexpr uint32_t beat_proximity_threshold_shift{25};

constexpr uint8_t bg_brightness_max{75};
constexpr uint8_t bg_brightness_base{50};
constexpr uint8_t bg_brightness_diff{bg_brightness_max - bg_brightness_base};

constexpr uint32_t bg_pulse_fade_millis{beat_length_millis / 2};
constexpr uint32_t bg_pulse_ramp_millis{85};
constexpr uint8_t player_hues[4]{
    0,    // red
    45,   // yellow
    130,  // teal
    200   // lavendar
};

const animation::Explosion kExploderPrototype{2, 350, 150, 25, 0,
                                              0, 0,   128, 160};

}  // namespace _rhythm_single
using namespace _rhythm_single;

class RhythmGameSingle : public Game {
  const uint8_t player_no;

  uint32_t metronome_last_hit{0};

  // Sticks
  controls::RhythmController controller;

  // Sounds
  audio::SynthSenderRaw synth;

  // Animations
  animation::SingleColorBG background;  // black bg
  animation::NoiseAnimation noise_block;

  std::vector<animation::Explosion*> explosives;

  // Success tracking
  uint8_t on_beat_count{0};
  static constexpr uint8_t on_beat_count_threshold{8};

 public:
  struct ExternalExplosion {
    uint8_t hue;
    uint8_t count;
    uint8_t size;
    ExternalExplosion(uint8_t hue, uint8_t count, uint8_t size)
        : hue{hue}, count{count}, size{size} {}
  };

 private:
  void CreateExplosion(ExternalExplosion explo) {
    Debug("Creating Explo:::");
    Debug_var(explo.hue);
    Debug_var(explo.count);
    Debug_var(explo.size);
    Debug_endl();
    for (size_t i = 0; i < explo.count; ++i) {
      animation::Explosion* explody = new animation::Explosion(
          40 + (explo.size * 15), 0, beat_length_millis * explo.size,
          25 * explo.size, 15, 0, 0, 255, explo.hue);
      explody->ExplodeAt(math::random::Int8(display->size.x),
                         math::random::Int16(display->size.y));
      explosives.push_back(explody);
    }
  }

  std::vector<ExternalExplosion>* external_explosions;

  void ExplodeForBeatProximity(ExternalExplosion explo) {
    if (on_beat_count < on_beat_count_threshold + 5) {
      ++on_beat_count;
    }
    if (external_explosions != NULL) {
      //   Debug("Adding External explosion from player " + player_no);
      external_explosions->push_back(explo);
    } else {
      //   Debug("Explodiong");
      CreateExplosion(explo);
    }
  }

  void MoveExplosions() {
    // Move each explosive, they're all active
    for (auto explosive : explosives) {
      //   Debug("Moving explosions...");
      explosive->Move();
    }
  }

  void RemoveDeadExplosions() {
    // Remove dead explosives
    for (auto it = explosives.begin(); it < explosives.end();) {
      //   Debug("Cleaning dead explosions...");
      if ((*it)->IsBurnedOut()) {
        // Debug("Deleting explosion...");
        delete *it;
        it = explosives.erase(it);
      } else {
        ++it;
      }
    }
  }

 public:
  // called by main game
  void AddExternalExplosions() {
    if (external_explosions != NULL) {
      for (auto& explo : *external_explosions) {
        CreateExplosion(explo);
      }
    }
  }

  RhythmGameSingle(display::Display* display,
                   controls::RhythmController controller)
      : Game(display),
        player_no{0},
        controller{controller},
        synth{serial::kHwSerials[player_no]},
        noise_block{
            player_hues[player_no], 20, {display->size.x, display->size.y / 4}},
        external_explosions{NULL} {}

  RhythmGameSingle(display::Display* display,
                   controls::RhythmController controller, uint8_t player_no,
                   std::vector<ExternalExplosion>* external_explosions)
      : Game(display),
        player_no{player_no},
        controller{controller},
        synth{serial::kHwSerials[player_no]},
        noise_block{
            player_hues[player_no], 20, {display->size.x, display->size.y / 4}},
        external_explosions{external_explosions} {}

  // Track the beat so we can Draw backgrounds
  uint8_t beat{0};
  void UpdateMetronome() {
    // Using while to catch up if behind - bad?
    while (metronome_last_hit + beat_length_millis <= time::Now()) {
      metronome_last_hit += beat_length_millis;
      if (++beat == 4) {
        beat = 0;

        // Track how on-the-beat the player is
        if (on_beat_count > 0) {
          --on_beat_count;
        }
      }

      // Move the block animation up the tower
      noise_block.location.y = beat * display->size.y / 4;

      // Trigger the click track to the audio chip
      synth.SendClickTrack(beat);

      //   Debug("BEAT!");
      //   Debug_var(metronome_last_hit);
      //   Debug_var(time::Now());
    }
  }

  void UpdateBgBrightness() {
    const uint32_t time_since_beat = time::Now() - metronome_last_hit;
    if (time_since_beat < bg_pulse_fade_millis) {
      // 0 -> 1 over bg_pulse_fade_millis
      const float t_factor =
          (float)time_since_beat / (float)bg_pulse_fade_millis;

      // 0 -> bg_brightness_diff over bg_pulse_fade_millis
      const uint8_t brightness_offset = t_factor * bg_brightness_diff;

      // bg_brightness_max -> bg_brightness_base over bg_pulse_fade_millis
      noise_block.brightness = bg_brightness_max - brightness_offset;
    } else if (beat_length_millis - time_since_beat < bg_pulse_ramp_millis) {
      // bg_pulse_ramp_millis -> 0
      const uint32_t time_until_beat = beat_length_millis - time_since_beat;

      // 1 -> 0 over bg_pulse_ramp_millis
      const float t_factor =
          (float)time_until_beat / (float)bg_pulse_ramp_millis;

      // bg_brightness_diff -> 0 over bg_pulse_ramp_millis
      const uint8_t brightness_offset = t_factor * bg_brightness_diff;

      // bg_brightness_base -> bg_brightness_max over bg_pulse_ramp_millis
      noise_block.brightness = bg_brightness_max - brightness_offset;
    } else {
      noise_block.brightness = bg_brightness_base;
    }
  }

  void DetectBeatProximity() {
    const uint32_t last_beat_distance = time::Now() - metronome_last_hit;
    const uint32_t next_beat_distance =
        (metronome_last_hit + beat_length_millis) - time::Now();

    const uint32_t beat_distance = min(last_beat_distance, next_beat_distance);
    if (last_beat_distance <=
            beat_proximity_threshold + beat_proximity_threshold_shift ||
        next_beat_distance <=
            beat_proximity_threshold - beat_proximity_threshold_shift) {
      Debug("Exploding Full Beat");
      Debug_var(beat_distance);
      ExplodeForBeatProximity({player_hues[player_no], 1, 2});
      return;
    }

    const uint32_t half_beat_distance = beat_length_millis / 2 - beat_distance;
    if (half_beat_distance <=
        (beat_proximity_threshold + beat_proximity_threshold_shift) / 2) {
      Debug("Exploding Half Beat");
      Debug_var(beat_distance);
      ExplodeForBeatProximity({player_hues[player_no], 1, 1});
      return;
    }

    // const uint32_t quarter_beat_distance =
    //     beat_length_millis / 4 - half_beat_distance;
    // if (beat_length_millis / 4 - beat_distance <= beat_proximity_threshold)
    // {
    //   ExplodeForBeatProximity(
    //       {player_hues[player_no], math::random::Int8_incl(2, 3), 1});
    //   return;
    // }
  }

  void setup() override {}

  void loop() override {
    // Update metronome first to get our timestamps right
    UpdateMetronome();

    bool any_pressing = false;
    for (uint8_t i = 0; i < controller.button_count; ++i) {
      if (controller.buttons[i]->IsDepressing()) {
        synth.StartInput(i);
        any_pressing = true;
      }
      if (controller.buttons[i]->IsReleasing()) {
        synth.StopInput(i);
      }
    }

    UpdateBgBrightness();

    if (any_pressing) {
      DetectBeatProximity();
    }
    MoveExplosions();
    RemoveDeadExplosions();

    // Draw Time
    background.Draw(display);

    // Draw double rainbow on success
    if (on_beat_count >= on_beat_count_threshold) {
      noise_block.use_rainbow_hue = true;
      noise_block.Draw(display);
      const size_t old_y = noise_block.location.y;
      noise_block.location.y = ((beat + 6) % 4) * display->size.y / 4;
      noise_block.Draw(display);
      noise_block.location.y = old_y;
    } else {
      // Single block no rainbow, no success
      noise_block.use_rainbow_hue = false;
      noise_block.Draw(display);
    }

    for (auto explosive : explosives) {
      explosive->Draw(display);
    }

    // exploder.Draw(display);
  }
};

}  // namespace rhythm
}  // namespace games
}  // namespace kss
