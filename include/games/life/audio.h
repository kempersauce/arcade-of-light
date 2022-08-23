#pragma once

#include <memory>  // for std::shared_ptr

#include "audio/audio_sender.h"      // for AudioSender
#include "audio/background_music.h"  // for BackgroundMusic

namespace kss {
namespace games {
namespace life {

class LifeAudio {
  std::shared_ptr<audio::AudioSender> audio_sender =
      std::make_shared<audio::AudioSender>();

 public:
  // Single Effects
  audio::SoundEffectBespoke shuffle{audio_sender, 1, "GYCYCHIP.WAV"};

  audio::SoundEffect stop{audio_sender, "TRGTHIT5.WAV"};
  audio::SoundEffect unStop{audio_sender, "TRGTHIT1.WAV"};

  audio::SoundEffectBespoke speedUp{audio_sender, 1, "DIO.WAV"};
  audio::SoundEffectBespoke speedDown{audio_sender, 1, "TGTHIT1.WAV"};

  audio::SoundEffectBespoke colorShift{audio_sender, 2, "ABORTSEQ.WAV"};

  // Background Music
  audio::BackgroundMusic background{audio_sender, "CDL.WAV"};

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
