#pragma once
#include <HardwareSerial.h>

#include "audio/audio_sender.h"  // for AudioSender
class RocketAudio : public AudioSender {
 public:
  // File names for single effects
  char* explosion = "EXPLODE1";
  char* win = "BOOM";
  char* targetWin = "<TRGTHIT5.WAV>";
  char* levelWin = "<11LIFTOFF.WAV>";

  // File names for Background
  char* winBG = "EARTH";
  char* stdBG = "<9EARTH.WAV>";

  // Level Intro Sounds
  char* level1Intro = "<EARTHVOX.WAV>";
  char* level1BG = "<9EARTH.WAV>";
  char* level2Intro = "<MOONVOX.WAV>";
  char* level2BG = "<9MOONJAZZ.WAV>";
  char* level3Intro = "<MARSVOX.WAV>";
  char* level3BG = "<9MARS.WAV>";
  char* level4Intro = "<JPTRVOX.WAV>";
  char* level4BG = "<9JUPITER.WAV>";
  char* level5Intro = "<PLUTOVOX.WAV>";
  char* level5BG = "<9PLUTO.WAV>";

  // File names and controls for start/stop channels
  char* boost = "THRUST2";
  bool boostIsPlaying = false;
  char* targetHover = "TRGTSEQ";
  char* targetHoverFull = "<21TRGTSEQ.WAV>";
  bool targetHoverIsPlaying = false;
  char* fireworkLaunch = "WHOOSH";
  char* fireworkLaunchLong = "<TRGTMIS1.WAV>";
  bool fireworkLaunchIsPlaying = false;
  char* fireworkExplode = "EXPLODE1";
  char* fireworkExplodeLong = "<EXPLODE1.WAV>";

  // CONSTRUCTOR - starts Serial (inhereted from AudioSender)
  RocketAudio() : AudioSender() {}

  // SINGLE EFFECT METHODS
  void playExplosion() { playWav(explosion); }
  void playWin() { playWav(win); }
  void playTargetWin() { sendMsg(targetWin); }
  void playLevelWin() { serial.println(levelWin); }
  void playLevelIntro() {
    // playWav()
  }
  void playFireWorkLaunch() { sendMsg(fireworkLaunchLong); }
  void playFireWorkExplode() { sendMsg(fireworkExplodeLong); }

  void killChannels() {
    serial.println("<20>");
    delay(5);
    serial.println("<10>");
    delay(5);
    serial.println("<aa>");
    delay(5);
    serial.println("<aa>");
    delay(5);
  }

  void playLevelIntro(int levelNum) {
    switch (levelNum) {
      case 1:
        // delay(100);
        killChannels();
        serial.println("<EARTHVOX.WAV>");
        delay(5);
        serial.println("<9EARTH.WAV>");
        delay(5);
        break;
      case 2:
        killChannels();
        sendMsg(level2Intro);
        sendMsg(level2BG);
        break;
      case 3:
        killChannels();
        sendMsg(level3Intro);
        sendMsg(level3BG);
        break;
      case 4:
        killChannels();
        sendMsg(level4Intro);
        sendMsg(level4BG);
        break;
      case 5:
        killChannels();
        sendMsg(level5Intro);
        sendMsg(level5BG);
        break;
    }
  }

  // START/STOP METHODS

  // CHANNEL 1: BOOST
  void startPlayBoost() {
    if (!boostIsPlaying) {
      startWavOnChannel(boost, 1);
      boostIsPlaying = true;
    }
  }
  void stopPlayBoost() {
    stopWavOnChannel(1);
    boostIsPlaying = false;
  }

  // CHANNEL 2: TARGET
  void startPlayTargetHover() {
    if (!targetHoverIsPlaying) {
      sendMsg(targetHoverFull);
      targetHoverIsPlaying = true;
    }
  }
  void stopPlayTargetHover() {
    sendMsg("<20>");
    targetHoverIsPlaying = false;
  }

  // CHANNEL 1: FireworkLaunch

  // BACKGROUND METHODS
  void playStdBG() { sendMsg(stdBG); }
  void playWinBG() { setBackground(winBG); }
};