#pragma once

#include <HardwareSerial.h>

#include "audio/audio_sender.h"  // for AudioSender

namespace kss {
namespace games {
namespace life {

class LifeAudio : public audio::AudioSender {
 public:
  // File names for single effects
  const char* shuffle = "GYCYCHIP.WAV";
  bool shuffleIsStarted = false;

  char* stop = "TRGTHIT5.WAV";
  char* unStop = "TRGTHIT1.WAV";

  char* speedUp = "DIO.WAV";
  bool isSpeedingUp = false;

  char* speedDown = "TGTHIT1.WAV";
  bool isSpeedingDown = false;

  char* colorShift = "ABORTSEQ.WAV";
  bool colorIsShifting = false;

  // File names for Background
  char* stdBG = "CDL.WAV";
  char* idleBG = "CDL.WAV";

  // File names and controls for start/stop channels

  // CONSTRUCTOR - starts Serial (inhereted from AudioSender)
  LifeAudio() : AudioSender() {}

  // SINGLE EFFECT METHODS
  void playTimeStop() { PlayWav(stop); }

  void playTimeStart() { PlayWav(unStop); }

  void startRandom() {
    PlayWav(shuffle, 1);
    shuffleIsStarted = true;
  }

  void startSpeedUp() {
    if (!isSpeedingUp) {
      isSpeedingUp = true;
      PlayWav(speedUp, 1);
    }
  }

  void startSpeedDown() {
    if (!isSpeedingDown) {
      PlayWav(speedDown, 1);
      isSpeedingDown = true;
    }
  }

  void playColorShift() {
    if (!colorIsShifting) {
      PlayWav(colorShift, 2);
      colorIsShifting = true;
    }
  }

  // START/STOP METHODS
  void stopChannels() {
    StopChannel(1);
    StopChannel(2);
  }

  void stopPlayRandom() {
    if (shuffleIsStarted) {
      StopChannel(1);
      shuffleIsStarted = false;
    }
  }

  void stopColorShift() {
    if (colorIsShifting) {
      StopChannel(2);
      colorIsShifting = false;
    }
  }

  void stopSpeed() {
    if (isSpeedingUp) {
      StopChannel(1);
      isSpeedingUp = false;
    } else if (isSpeedingDown) {
      StopChannel(1);
      isSpeedingDown = false;
    }
  }

  // CHANNEL 1: FireworkLaunch

  // BACKGROUND METHODS
  void playStdBG() { setBackground(stdBG); }
  void playH2HIdleBG() { setBackground(idleBG); }
};

}  // namespace life
}  // namespace games
}  // namespace kss
