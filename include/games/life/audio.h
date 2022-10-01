#pragma once

#include "audio/background_music.h"      // for BackgroundMusic
#include "audio/manager.h"               // for audio::Manager
#include "audio/sound_effect.h"          // for SoundEffect
#include "audio/sound_effect_bespoke.h"  // for SoundEffectBespoke

namespace kss {
namespace games {
namespace life {

class LifeAudio : public audio::Manager {
 public:
  // Single Effects
  audio::SoundEffectBespoke shuffle{sender, 1, "GYCYCHIP.WAV"};

  audio::SoundEffect stop{sender, "TRGTHIT5.WAV"};
  audio::SoundEffect unStop{sender, "TRGTHIT1.WAV"};

  audio::SoundEffectBespoke speedUp{sender, 1, "DIO.WAV"};
  audio::SoundEffectBespoke speedDown{sender, 1, "TGTHIT1.WAV"};

  audio::SoundEffectBespoke colorShift{sender, 2, "ABORTSEQ.WAV"};

  // Background Music
  audio::BackgroundMusic background{sender, "CDL.WAV"};

  // SINGLE EFFECT METHODS
  const void playTimeStop() { stop.Play(); }

  const void playTimeStart() { unStop.Play(); }

  const void startRandom() { shuffle.Play(); }

  const void startSpeedUp() {
    if (!speedUp.is_playing) {
      speedUp.Play();
    }
  }

  const void startSpeedDown() {
    if (!speedDown.is_playing) {
      speedDown.Play();
    }
  }

  const void playColorShift() { colorShift.Play(); }

  const void stopPlayRandom() { shuffle.Stop(); }

  const void stopColorShift() { colorShift.Stop(); }

  const void stopSpeed() {
    speedUp.Stop();
    speedDown.Stop();
  }

  // CHANNEL 1: FireworkLaunch

  // BACKGROUND METHODS
  const void playStdBG() { background.Play(); }
};

}  // namespace life
}  // namespace games
}  // namespace kss
