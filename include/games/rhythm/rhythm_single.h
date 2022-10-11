#pragma once

#include <vector>  // for vector

#include "animation/animation.h"                      // for Animation
#include "animation/charge_bar.h"                     // for ChargeBar
#include "animation/charge_full.h"                    // for ChargeBar
#include "animation/exploder.h"                       // for Exploder
#include "animation/explosion.h"                      // for Explosion
#include "animation/explosions.h"                     // for Explosions
#include "animation/sine_wave.h"                      // for SineWave
#include "animation/single_color_background.h"        // for SingleColorBG
#include "animation/single_color_block.h"             // for SingleColorBlock
#include "animation/wave_out.h"                       // for WaveOut
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
  animation::WaveOut3 idle_animation;

  animation::SingleColorBG background;
  animation::WavePulseStars wave_pulse_stars[4];
  animation::SineWave sine_wave;
  animation::WavePulse wave_pulse_shadow;
  animation::WavePulse wave_pulse[4];
  animation::ChargeBar charge_bar;
  animation::ChargeFull charge_full;

  const size_t beat_height;
  const size_t hit_bar_height;
  animation::SingleColorBlock hit_bar;

  // Explosions for when you do good
  animation::Explosions explosions;

  // Success tracking
  uint16_t on_beat_count{0};  // Debug, start almost there
  uint16_t on_beat_count_max{48};
  float on_beat_units;
  uint16_t on_beat_height{0};
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
        idle_animation{kPlayerHues[player_no], 255, display->size},
        wave_pulse_stars{
            {display->size.height / 6, 0,
             noise_generator == NULL
                 ? (noise_generator =
                        new engines::NoiseGenerator(display->size, 7))
                 : noise_generator,
             kPlayerOffhues[player_no]},
            {display->size.height / 6, 1, noise_generator,
             kPlayerOffhues[player_no]},
            {display->size.height / 6, 1, noise_generator,
             kPlayerOffhues[player_no]},
            {display->size.height / 6, 1, noise_generator,
             kPlayerOffhues[player_no]},
        },
        sine_wave{CHSV(kPlayerHues[player_no], 255, 255), 0.5},
        wave_pulse{
            {15, 0, CRGB::DarkGray},
            {5, 1, CRGB::DarkGray},
            {10, 1, CRGB::DarkGray},
            {5, 1, CRGB::DarkGray},
        },
        charge_bar{CRGB::White},
        charge_full{-1},
        beat_height{display->size.height / 4},
        hit_bar_height{display->size.height / 5},
        hit_bar{hit_bar_height, hit_bar_height + 1, CRGB::White},
        on_beat_units{display->size.height / 32} {
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

  inline size_t GetDistanceFromHitBar(const float y) const {
    return max(y, hit_bar_height) - min(y, hit_bar_height);
  }

  size_t min_distance_from_hitbar;
  animation::WavePulse* closest_wave_to_hitbar;
  void SetPulseHeight() {
    min_distance_from_hitbar = SIZE_MAX;
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

      // Record info about the closest wave
      const size_t distance = GetDistanceFromHitBar(y);
      if (distance < min_distance_from_hitbar) {
        min_distance_from_hitbar = distance;
        closest_wave_to_hitbar = &wave_pulse[beet];
      }
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

  void SetWavePulseShadow() {
    wave_pulse_shadow = *closest_wave_to_hitbar;
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
    // Call it if we're within ~10px on a 300px display
    if (min_distance_from_hitbar <= beat_height / 7.5) {
      Debug("Exploding Full Beat");
      Debug_var(min_distance_from_hitbar);
      Debug_var(beat_height);
      if (time::Now() - last_beat_hit_millis >= beat_hit_downtime_millis) {
        on_beat_count += 2;
        AddExplosions();
        last_beat_hit_millis = time::Now();
        if (on_beat_count > on_beat_count_max) {
          on_beat_count = on_beat_count_max;
        }
      }
      return;
    }

    // Also, if we're within ~5px from the half-beat on a 300px display
    if (beat_height / 2 - min_distance_from_hitbar <= beat_height / 15) {
      Debug("Exploding Half Beat");
      Debug_var(min_distance_from_hitbar);
      Debug_var(beat_height);
      if (time::Now() - last_beat_hit_millis >= beat_hit_downtime_millis) {
        on_beat_count += 1;
        AddExplosions();
        last_beat_hit_millis = time::Now();
        if (on_beat_count > on_beat_count_max) {
          on_beat_count = on_beat_count_max;
        }
      }
      return;
    }

    // Show em where they screwed up
    SetWavePulseShadow();
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

    // Show Idle animation if we're idle
    idle_animation.Move();  // move always to stay together
    if (controller.IsIdle()) {
      idle_animation.Draw(display);
      return;
    }

    for (uint8_t i = 0; i < controller.button_count; ++i) {
      auto& wave = sine_wave.waves[i % sine_wave.waves.size()];
      if (controller.buttons[i]->IsDepressing()) {
        wave.On();
      }
      if (controller.buttons[i]->IsReleasing()) {
        wave.Off();
      }
    }

    // Set the pulse height
    SetPulseHeight();

    // Detect hits on the beat
    if (controller.AnyDepressing()) {
      DetectBeatProximity();
    }

    // Set charge bar height
    charge_bar.height = on_beat_count * on_beat_units;

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

    explosions.Move();

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
    const bool was_charged = on_beat_height >= display->size.height - 1;
    on_beat_height = on_beat_count * on_beat_units;
    if (on_beat_height < display->size.height - 1) {
      charge_bar.Draw(display);
    } else {
      // Eliminate full charge flicker by pumping this up when it hits
      if (!was_charged) {
        on_beat_count += 2;
      }
      charge_full.Draw(display);
    }

    hit_bar.Draw(display);

    explosions.Draw(display);
  }
};

}  // namespace rhythm
}  // namespace games
}  // namespace kss
