#pragma once

#include <HardwareSerial.h>

#include <memory>  // for std::make_shared

#include "audio/audio_sender.h"      // for AudioSender
#include "audio/background_music.h"  // for BackgroundMusic

namespace kss {
namespace games {
namespace life {

class LifeAudio {
 public:
  std::shared_ptr<audio::AudioSender> audio_sender;

  // File names for single effects
  const char* shuffle = "GYCYCHIP.WAV";
  bool shuffleIsStarted = false;

  const char* stop = "TRGTHIT5.WAV";
  const char* unStop = "TRGTHIT1.WAV";

  const char* speedUp = "DIO.WAV";
  bool isSpeedingUp = false;

  const char* speedDown = "TGTHIT1.WAV";
  bool isSpeedingDown = false;

  const char* colorShift = "ABORTSEQ.WAV";
  bool colorIsShifting = false;

  // File names for Background
  const char* stdBG = "CDL.WAV";
  const char* idleBG = "CDL.WAV";

  audio::BackgroundMusic background;

  // File names and controls for start/stop channels

  // CONSTRUCTOR - starts Serial (inhereted from AudioSender)
  LifeAudio()
      : audio_sender(std::make_shared<audio::AudioSender>()),
        background{audio_sender, stdBG} {}

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

  void startSpeedDown() {
    if (!isSpeedingDown) {
      audio_sender->PlayWav(speedDown, 1);
      isSpeedingDown = true;
    }
  }

  void playColorShift() {
    if (!colorIsShifting) {
      audio_sender->PlayWav(colorShift, 2);
      colorIsShifting = true;
    }
  }

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

  void stopColorShift() {
    if (colorIsShifting) {
      audio_sender->StopChannel(2);
      colorIsShifting = false;
    }
  }

  void stopSpeed() {
    if (isSpeedingUp) {
      audio_sender->StopChannel(1);
      isSpeedingUp = false;
    } else if (isSpeedingDown) {
      audio_sender->StopChannel(1);
      isSpeedingDown = false;
    }
  }

  // CHANNEL 1: FireworkLaunch

  // BACKGROUND METHODS
  void playStdBG() { background.Play(); }
  void playH2HIdleBG() { audio_sender->setBackground(idleBG); }
};

}  // namespace life
}  // namespace games
}  // namespace kss
