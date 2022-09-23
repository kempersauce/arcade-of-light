#pragma once

#include <vector>  // for vector

#include "animation/animation.h"     // for Animation
#include "animation/exploder.h"      // for Exploder
#include "animation/explosion.h"     // for Explosion
#include "animation/starscape.h"     // for Starscape
#include "audio/synth_sender_raw.h"  // for SynthSenderRaw
#include "controls/dir_pad.h"        // for DirPad
#include "games/game.h"              // for Game
#include "math/random.h"             // for random::*
#include "serial/debug.h"            // for Debug
#include "serial/hw_serials.h"       // for kHwSerials
#include "time/now.h"                // for Now

namespace kss {
namespace games {
namespace rhythm {

namespace _rhythm_single {
constexpr float bpm{120};
constexpr uint32_t beat_length_millis{1000 * 60 / bpm};

constexpr uint32_t beat_proximity_threshold{75};
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
  controls::DirPad controller;

  // Sounds
  audio::SynthSenderRaw synth;

  // Animations
  animation::NoiseAnimation background;

  std::vector<animation::Explosion*> explosives;

  void CreateExplosion(uint8_t explosion_hue) {
    animation::Explosion* explody = new animation::Explosion(
        75, 0, beat_length_millis * 2, 45, 15, 0, 0, 255, explosion_hue);
    explody->ExplodeAt(math::random::Int8(display->size.x),
                       math::random::Int16(display->size.y));
    explosives.push_back(explody);
  }

  std::vector<uint8_t>* external_explosion_hues;

  void ExplodeForBeatProximity(uint8_t explosion_hue) {
    if (external_explosion_hues != NULL) {
      //   Debug("Adding External explosion from player " + player_no);
      external_explosion_hues->push_back(player_hues[player_no]);
    } else {
      //   Debug("Explodiong");
      CreateExplosion(explosion_hue);
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
    if (external_explosion_hues != NULL) {
      for (auto explosion_hue : *external_explosion_hues) {
        CreateExplosion(explosion_hue);
      }
    }
  }

  RhythmGameSingle(display::Display* display, controls::DirPad controller)
      : Game(display),
        player_no{0},
        controller{controller},
        synth{serial::kHwSerials[player_no]},
        background{player_hues[player_no], 20, display->size},
        external_explosion_hues{NULL} {}

  RhythmGameSingle(display::Display* display, controls::DirPad controller,
                   uint8_t player_no,
                   std::vector<uint8_t>* external_explosion_hues)
      : Game(display),
        player_no{player_no},
        controller{controller},
        synth{serial::kHwSerials[player_no]},
        background{player_hues[player_no], 20, display->size},
        external_explosion_hues{external_explosion_hues} {}

  void UpdateMetronome() {
    // Using while to catch up if behind - bad?
    while (metronome_last_hit + beat_length_millis <= time::Now()) {
      metronome_last_hit += beat_length_millis;
      // synth.StartInput(??);
      Debug("BEAT!");
      Debug_var(metronome_last_hit);
      Debug_var(time::Now());
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
      background.brightness = bg_brightness_max - brightness_offset;
    } else if (beat_length_millis - time_since_beat < bg_pulse_ramp_millis) {
      // bg_pulse_ramp_millis -> 0
      const uint32_t time_until_beat = beat_length_millis - time_since_beat;

      // 1 -> 0 over bg_pulse_ramp_millis
      const float t_factor =
          (float)time_until_beat / (float)bg_pulse_ramp_millis;

      // bg_brightness_diff -> 0 over bg_pulse_ramp_millis
      const uint8_t brightness_offset = t_factor * bg_brightness_diff;

      // bg_brightness_base -> bg_brightness_max over bg_pulse_ramp_millis
      background.brightness = bg_brightness_max - brightness_offset;
    } else {
      background.brightness = bg_brightness_base;
    }
  }

  void DetectBeatProximity() {
    const uint32_t last_beat_distance = time::Now() - metronome_last_hit;
    const uint32_t next_beat_distance =
        (metronome_last_hit + beat_length_millis) - time::Now();
    const uint32_t beat_distance = min(last_beat_distance, next_beat_distance);
    if (beat_distance <= beat_proximity_threshold) {
      ExplodeForBeatProximity(player_hues[player_no]);
    }
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

    background.draw(display);

    for (auto explosive : explosives) {
      explosive->draw(display);
    }

    // exploder.draw(display);
  }
};

}  // namespace rhythm
}  // namespace games
}  // namespace kss
