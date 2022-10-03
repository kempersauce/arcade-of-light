#pragma once

#include <vector>  // for vector

#include "animation/animation.h"                // for Animation
#include "animation/charge_bar.h"               // for ChargeBar
#include "animation/charge_full.h"              // for ChargeBar
#include "animation/exploder.h"                 // for Exploder
#include "animation/explosion.h"                // for Explosion
#include "animation/noise.h"                    // for NoiseAnimation
#include "animation/sine_wave.h"                // for SineWave
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
  animation::SineWave sine_wave;
  animation::NoiseAnimation noise_block;
  animation::ChargeBar charge_bar;
  animation::ChargeFull charge_full;

  // Success tracking
  uint16_t on_beat_count{0};
  static constexpr uint8_t on_beat_count_threshold{8};

 public:
  RhythmGameSingle(display::Display* display,
                   controls::RhythmController controller, uint8_t player_no = 0)
      : Game(display),
        player_no{player_no},
        controller{controller},
        synth{serial::kHwSerials[player_no]},
        sine_wave{CRGB::Cyan, 0.5},
        noise_block{
            player_hues[player_no], 20, {display->size.x, display->size.y / 4}},
        charge_bar{CRGB::White},
        charge_full{-1} {
    sine_wave.waves.emplace_back(100, display->size.width / 4.0f, .1);
    sine_wave.waves.emplace_back(20, display->size.width / 8.0f, -0.1);
    sine_wave.waves.emplace_back(10, display->size.width / 12.0f, .05);
  }

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
      on_beat_count += 4;
      return;
    }

    const uint32_t half_beat_distance = beat_length_millis / 2 - beat_distance;
    if (half_beat_distance <=
        (beat_proximity_threshold + beat_proximity_threshold_shift) / 2) {
      Debug("Exploding Half Beat");
      Debug_var(beat_distance);
      on_beat_count += 2;
      return;
    }

    // const uint32_t quarter_beat_distance =
    //     beat_length_millis / 4 - half_beat_distance;
    // if (beat_length_millis / 4 - beat_distance <= beat_proximity_threshold)
    // {
    //   return;
    // }
  }

  void setup() override {}

  void loop() override {
    // Update metronome first to get our timestamps right
    UpdateMetronome();

    for (uint8_t i = 0; i < controller.button_count; ++i) {
      auto& wave = sine_wave.waves[i % sine_wave.waves.size()];
      if (controller.buttons[i]->IsDepressing()) {
        synth.StartInput(i);
        wave.On();
      }
      if (controller.buttons[i]->IsReleasing()) {
        synth.StopInput(i);
        wave.Off();
      }
    }

    UpdateBgBrightness();

    if (controller.AnyDepressing()) {
      DetectBeatProximity();
    }

    // Set charge bar height
    charge_bar.height = on_beat_count;

    // Move our animations
    background.Move();
    noise_block.Move();
    sine_wave.Move();
    charge_bar.Move();
    charge_full.Move();

    // Draw Time
    background.Draw(display);

    // Draw double rainbow on success
    if (on_beat_count >= display->size.height) {
      noise_block.use_rainbow_hue = true;
      noise_block.Draw(display);
      const size_t old_y = noise_block.location.y;
      noise_block.location.y = ((beat + 2) % 4) * display->size.y / 4;
      noise_block.Draw(display);
      noise_block.location.y = old_y;
    } else {
      // Single block no rainbow, no success
      noise_block.use_rainbow_hue = false;
      noise_block.Draw(display);
    }

    sine_wave.Draw(display);

    if (on_beat_count < display->size.height - 1) {
      charge_bar.Draw(display);
    } else {
      charge_full.Draw(display);
    }
  }
};

}  // namespace rhythm
}  // namespace games
}  // namespace kss
