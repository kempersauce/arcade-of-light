#pragma once

#include <vector>  // for vector

#include "animation/animation.h"                      // for Animation
#include "animation/charge_bar.h"                     // for ChargeBar
#include "animation/charge_full.h"                    // for ChargeBar
#include "animation/exploder.h"                       // for Exploder
#include "animation/explosion.h"                      // for Explosion
#include "animation/sine_wave.h"                      // for SineWave
#include "animation/single_color_background.h"        // for SingleColorBG
#include "animation/single_color_block.h"             // for SingleColorBlock
#include "animation/wave_pulse.h"                     // for WavePulse
#include "animation/wave_pulse_stars.h"               // for WavePulseStars
#include "audio/synth_sender_raw.h"                   // for SynthSenderRaw
#include "controls/rhythm.h"                          // for RhythmController
#include "games/game.h"                               // for Game
#include "games/rhythm/constants.h"                   // for k*
#include "games/rhythm/interface/drum_interface.h"    // for DrumInterface
#include "games/rhythm/interface/player_interface.h"  // for PlayerInterface
#include "games/rhythm/interface/synth_interface.h"   // for SynthInterface
#include "math/random.h"                              // for random::*
#include "serial/debug.h"                             // for Debug
#include "serial/hw_serials.h"                        // for kHwSerials
#include "time/now.h"                                 // for Now

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

}  // namespace _rhythm_single
using namespace _rhythm_single;

class RhythmGameSingle : public Game {
  const uint8_t player_no;

  uint32_t metronome_last_hit{0};

  // Sticks
  controls::RhythmController controller;
  PlayerInterface* const player_interface;

  // Animations
  animation::SingleColorBG background;
  animation::WavePulseStars wave_pulse_stars[4];
  animation::SineWave sine_wave;
  animation::WavePulse wave_pulse_shadow;
  animation::WavePulse wave_pulse[4];
  animation::ChargeBar charge_bar;
  animation::ChargeFull charge_full;

  const size_t hit_bar_height;
  animation::SingleColorBlock hit_bar;

  // Explosions for when you do good
  std::vector<animation::Explosion> explosions;

  // Success tracking
  uint16_t on_beat_count{0};  // Debug, start almost there
  static constexpr uint8_t on_beat_count_threshold{8};

 public:
  RhythmGameSingle(display::Display* display,
                   controls::RhythmController controller, uint8_t player_no,
                   engines::NoiseGenerator* noise_generator = NULL)
      : Game(display),
        player_no{player_no},
        controller{controller},
        player_interface{player_no == 0 ? (PlayerInterface*)new DrumInterface(
                                              &this->controller, player_no)
                                        : (PlayerInterface*)new SynthInterface(
                                              &this->controller, player_no)},
        wave_pulse_stars{
            {display->size.height / 6, 0, noise_generator == NULL ? (noise_generator = new engines::NoiseGenerator(display->size, 7)) : noise_generator,
             kPlayerHues[player_no]},
            {display->size.height / 6, 1, noise_generator,
             kPlayerHues[player_no]},
            {display->size.height / 6, 1, noise_generator,
             kPlayerHues[player_no]},
            {display->size.height / 6, 1, noise_generator,
             kPlayerHues[player_no]},
        },
        sine_wave{CHSV(kPlayerOffhues[player_no], 255, 255), 0.5},
        wave_pulse{
            {15, 0, CRGB::DarkGray},
            {5, 1, CRGB::DarkGray},
            {10, 1, CRGB::DarkGray},
            {5, 1, CRGB::DarkGray},
        },
        charge_bar{CRGB::White},
        charge_full{-1},
        hit_bar_height{display->size.height / 5},
        hit_bar{hit_bar_height, hit_bar_height + 1, CRGB::White} {
    // TODO Tune these sine waves
    sine_wave.waves.emplace_back(100, display->size.width / 4.0f, .1);
    sine_wave.waves.emplace_back(100, display->size.width / 8.0f, -0.1);
    sine_wave.waves.emplace_back(50, display->size.width / 8.0f, -0.1);
    sine_wave.waves.emplace_back(50, display->size.width / 8.0f, -0.2);
    sine_wave.waves.emplace_back(25, display->size.width / 12.0f, .2);
    sine_wave.waves.emplace_back(25, display->size.width / 12.0f, -.2);
  }

  // Track the beat so we can Draw backgrounds
  uint8_t beat{0};
  void UpdateMetronome() {
    // Using while to catch up if behind - bad?
    while (metronome_last_hit + beat_length_millis <= time::Now()) {
      metronome_last_hit += beat_length_millis;

      // Track the current beat
      if (++beat == 4) {
        beat = 0;
      }

      // Decrease success rate, hope they've hit something
      if (on_beat_count > 0) {
        --on_beat_count;
      }

      //   Debug("BEAT!");
      //   Debug_var(metronome_last_hit);
      //   Debug_var(time::Now());
    }
  }

  void SetPulseHeight() {
    // 0 -> 1 over a beat
    const float t_offset =
        (float)(time::Now() - metronome_last_hit) / (float)beat_length_millis;

    for (uint8_t beet = 0; beet < 4; ++beet) {
      const uint8_t bet = (beat + beet) % 4;
      // 0 -> 1 over 4 beats
      const float t4_offset = ((float)bet + t_offset) / 4.0f;

      // y = 0 -> screen size, adjusted by hit_bar_height
      const float y =
          fmod(hit_bar_height + (float)display->size.height * (1 - t4_offset),
               display->size.height);
      wave_pulse[beet].y = y;
      wave_pulse_stars[beet].y = y;
    }
  }

  const animation::Explosion explodotype{8, 600,  350, 55, 12,
                                         0, -250, 0,   0,  NULL};
  void AddExplosions() {
    Debug("Exploding");
    explosions.push_back(explodotype);
    explosions.back().ExplodeAt(display->size.width / 4, hit_bar_height,
                                {0, 15});
    explosions.push_back(explodotype);
    explosions.back().ExplodeAt(display->size.width * 3 / 4, hit_bar_height,
                                {0, 15});

    explosions.push_back(explodotype);
    explosions.back().SetGravity(250);
    explosions.back().ExplodeAt(display->size.width / 4, hit_bar_height,
                                {0, -15});
    explosions.push_back(explodotype);
    explosions.back().SetGravity(250);
    explosions.back().ExplodeAt(display->size.width * 3 / 4, hit_bar_height,
                                {0, -15});
  }

  void MoveExplosions() {
    // Remove dead explosives
    for (auto it = explosions.begin(); it < explosions.end();) {
      it->Move();
      if (it->IsBurnedOut()) {
        it = explosions.erase(it);
      } else {
        ++it;
      }
    }
  }

  void SetWavePulseShadow() {
    animation::WavePulse* closest = NULL;
    size_t closest_distance;
    for (auto& wave : wave_pulse) {
      const size_t distance =
          max(wave.y, hit_bar_height) - min(wave.y, hit_bar_height);
      if (closest == NULL || distance < closest_distance) {
        closest = &wave;
        closest_distance = distance;
      }
    }

    wave_pulse_shadow = *closest;
    wave_pulse_shadow.color.fadeToBlackBy(64);

    // Total fade over shadow_fade_time_millis ms
    const static uint32_t shadow_fade_time_millis = 750;
    wave_pulse_shadow.fade_per_milli =
        wave_pulse_shadow.opacity / shadow_fade_time_millis;
  }

  static constexpr uint32_t beat_hit_downtime_millis{beat_proximity_threshold *
                                                     2};
  uint32_t last_beat_hit_millis;
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
      if (time::Now() - last_beat_hit_millis >= beat_hit_downtime_millis) {
        on_beat_count += 4;
        AddExplosions();
        last_beat_hit_millis = time::Now();
      }
      return;
    }

    const uint32_t half_beat_distance = beat_length_millis / 2 - beat_distance;
    if (half_beat_distance <=
        (beat_proximity_threshold + beat_proximity_threshold_shift) / 2) {
      Debug("Exploding Half Beat");
      Debug_var(beat_distance);
      if (time::Now() - last_beat_hit_millis >= beat_hit_downtime_millis) {
        on_beat_count += 2;
        AddExplosions();
        last_beat_hit_millis = time::Now();
      }
      return;
    }

    SetWavePulseShadow();

    // const uint32_t quarter_beat_distance =
    //     beat_length_millis / 4 - half_beat_distance;
    // if (beat_length_millis / 4 - beat_distance <= beat_proximity_threshold)
    // {
    //   return;
    // }
  }

  void setup() override {
    // Initialize all our timing here, after the game has been created
    // so we start and stay N'SYNC
    metronome_last_hit = time::Now();
    player_interface->Start();
  }

  void loop() override {
    // Update metronome first to get our timestamps right
    UpdateMetronome();

    // Play music! That's the whole game!
    player_interface->Update();

    for (uint8_t i = 0; i < controller.button_count; ++i) {
      auto& wave = sine_wave.waves[i % sine_wave.waves.size()];
      if (controller.buttons[i]->IsDepressing()) {
        wave.On();
      }
      if (controller.buttons[i]->IsReleasing()) {
        wave.Off();
      }
    }

    if (controller.AnyDepressing()) {
      DetectBeatProximity();
    }

    // Set charge bar height
    charge_bar.height = on_beat_count;

    // Set the pulse height
    SetPulseHeight();

    // Move our animations
    background.Move();
    for (auto& wp_stars : wave_pulse_stars) {
      wp_stars.Move();
    }
    wave_pulse_shadow.Move();
    for (auto& wp : wave_pulse) {
      wp.Move();
    }
    sine_wave.Move();
    charge_bar.Move();
    charge_full.Move();
    hit_bar.Move();

    MoveExplosions();

    // Draw Time
    background.Draw(display);

    // Draw stars in the background
    for (auto& wp_stars : wave_pulse_stars) {
      wp_stars.Draw(display);
    }

    sine_wave.Draw(display);

    // Draw beat pulse waves
    wave_pulse_shadow.Draw(display);
    for (auto& wp : wave_pulse) {
      wp.Draw(display);
    }

    // Draw charge bars
    if (on_beat_count < display->size.height - 1) {
      charge_bar.Draw(display);
    } else {
      charge_full.Draw(display);
    }

    hit_bar.Draw(display);

    for (auto& explody : explosions) {
      explody.Draw(display);
    }
  }
};

}  // namespace rhythm
}  // namespace games
}  // namespace kss
