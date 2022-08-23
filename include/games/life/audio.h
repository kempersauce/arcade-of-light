#pragma once

#include <HardwareSerial.h>

#include <memory>  // for std::make_shared

#include "audio/audio_sender.h"      // for AudioSender
#include "audio/background_music.h"  // for BackgroundMusic

namespace kss {
namespace games {
namespace life {

class LifeAudio {
  std::shared_ptr<audio::AudioSender> audio_sender =
      std::make_shared<audio::AudioSender>();

 public:
  // File names for single effects
  const char* shuffle = "GYCYCHIP.WAV";
  bool shuffleIsStarted = false;

  const char* stop = "TRGTHIT5.WAV";
  const char* unStop = "TRGTHIT1.WAV";

  const char* speedUp = "DIO.WAV";
  bool isSpeedingUp = false;

  audio::SoundEffectBespoke speedDown{audio_sender, 1, "TGTHIT1.WAV"};

  audio::SoundEffectBespoke colorShift{audio_sender, 2, "ABORTSEQ.WAV"};

  // Background Music
  audio::BackgroundMusic background{audio_sender, "CDL.WAV"};

  // SINGLE EFFECT METHODS
  void playTimeStop() { audio_sender->PlayWav(stop); }

  void playTimeStart() { audio_sender->PlayWav(unStop); }

  void startRandom() {
    audio_sender->PlayWav(shuffle, 1);
    shuffleIsStarted = true;
  }

  void startSpeedUp() {
    if (!isSpeedingUp) {
      isSpeedingUp = true;
      audio_sender->PlayWav(speedUp, 1);
    }
  }

  void startSpeedDown() { speedDown.Play(); }

  void playColorShift() { colorShift.Play(); }

  // START/STOP METHODS
  void stopChannels() {
    audio_sender->StopChannel(1);
    audio_sender->StopChannel(2);
  }

  void stopPlayRandom() {
    if (shuffleIsStarted) {
      audio_sender->StopChannel(1);
      shuffleIsStarted = false;
    }
  }

  void stopColorShift() { colorShift.Stop(); }

  void stopSpeed() {
    if (isSpeedingUp) {
      audio_sender->StopChannel(1);
      isSpeedingUp = false;
    }
    speedDown.Stop();
  }

  // CHANNEL 1: FireworkLaunch

  // BACKGROUND METHODS
  void playStdBG() { background.Play(); }
};

}  // namespace life
}  // namespace games
}  // namespace kss
