#pragma once
#include <AudioSender.h>
#include <HardwareSerial.h>
class LifeAudio : public AudioSender {
 public:
  // File names for single effects
  char* shuffle = "<11GYCYCHIP.WAV>";
  bool shuffleIsStarted = false;
  char* stop = "<TRGTHIT5.WAV>";
  char* unStop = "<TRGTHIT1.WAV>";
  char* speedUp = "<11DIO.WAV>";
  bool isSpeedingUp = false;
  char* speedDown = "<11TGTHIT1.WAV>";
  bool isSpeedingDown = false;
  char* colorShift = "<21ABORTSEQ.WAV>";
  bool colorIsShifting = false;

  // File names for Background
  char* stdBG = "CDL";
  char* idleBG = "CDL";

  // File names and controls for start/stop channels

  // CONSTRUCTOR - starts Serial (inhereted from AudioSender)
  LifeAudio() : AudioSender() {}

  // SINGLE EFFECT METHODS
  void playTimeStop() { sendMsg(stop); }
  void playTimeStart() { sendMsg(unStop); }
  void startRandom() {
    sendMsg(shuffle);
    shuffleIsStarted = true;
  }
  void startSpeedUp() {
    if (!isSpeedingUp) {
      isSpeedingUp = true;
      sendMsg(speedUp);
    }
  }
  void startSpeedDown() {
    if (!isSpeedingDown) {
      sendMsg(speedDown);
      isSpeedingDown = true;
    }
  }
  void playColorShift() {
    if (!colorIsShifting) {
      sendMsg(colorShift);
      colorIsShifting = true;
    }
  }

  // START/STOP METHODS
  void stopChannels() {
    sendMsg("<10>");
    sendMsg("<20>");
  }
  void stopPlayRandom() {
    if (shuffleIsStarted) {
      sendMsg("<10>");
      shuffleIsStarted = false;
    }
  }
  void stopColorShift() {
    if (colorIsShifting) {
      sendMsg("<20>");
      colorIsShifting = false;
    }
  }
  void stopSpeed() {
    if (isSpeedingUp) {
      sendMsg("<20>");
      isSpeedingUp = false;
    } else if (isSpeedingDown) {
      sendMsg("<20>");
      isSpeedingDown = false;
    }
  }

  // CHANNEL 1: FireworkLaunch

  // BACKGROUND METHODS
  void playStdBG() { setBackground(stdBG); }
  void playH2HIdleBG() { setBackground(idleBG); }
};