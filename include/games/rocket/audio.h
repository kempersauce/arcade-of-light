#pragma once
#include <HardwareSerial.h>

#include "audio/audio_sender.h"  // for AudioSender

namespace kss {
namespace games {
namespace rocket {

class RocketAudio : public audio::AudioSender {
 public:
  // File names for single effects
  const char* explosion = "EXPLODE1.WAV";
  const char* win = "BOOM.WAV";
  const char* targetWin = "TRGTHIT5.WAV";
  const char* levelWin = "LIFTOFF.WAV";

  // File names for Background
  const char* winBG = "EARTH.WAV";
  const char* stdBG = "EARTH.WAV";

  // Level Intro Sounds
  struct LevelSounds {
    const char* intro;
    const char* background;

    LevelSounds(const char* intro, const char* background)
        : intro{intro}, background{background} {}
  };

  LevelSounds level_sounds[5] = {
      LevelSounds{"EARTHVOX.WAV", "EARTH.WAV"},
      LevelSounds{"MOONVOX.WAV", "MOONJAZZ.WAV"},
      LevelSounds{"MARSVOX.WAV", "MARS.WAV"},
      LevelSounds{"JPTRVOX.WAV", "JUPITER.WAV"},
      LevelSounds{"PLUTOVOX.WAV", "PLUTO.WAV"},
  };

  // File names and controls for start/stop channels
  const char* boost = "THRUST2.WAV";
  bool boostIsPlaying = false;
  const char* targetHover = "TRGTSEQ.WAV";
  bool targetHoverIsPlaying = false;
  const char* fireworkLaunch = "TRGTMIS1.WAV";
  bool fireworkLaunchIsPlaying = false;
  const char* fireworkExplode = "EXPLODE1.WAV";

  // CONSTRUCTOR - starts Serial (inhereted from AudioSender)
  RocketAudio() : AudioSender() {}

  // SINGLE EFFECT METHODS
  void playExplosion() { PlayWav(explosion); }
  void playWin() { PlayWav(win); }
  void playTargetWin() { PlayWav(targetWin); }
  void playLevelWin() { PlayWav(levelWin, 1); }
  void playLevelIntro() {
    // PlayWav();
  }
  void playFireWorkLaunch() { PlayWav(fireworkLaunch); }
  void playFireWorkExplode() { PlayWav(fireworkExplode); }

  void killChannels() {
    StopChannel(2);
    delay(5);  // TODO can we get rid of these delays?
    StopChannel(1);
    delay(5);
    // serial.println("<aa>"); // TODO what does this do exactly?
    // delay(5);
    // serial.println("<aa>");
    // delay(5);
  }

  void playLevelIntro(const size_t level) {
    killChannels();
    PlayWav(level_sounds[level].intro);
    setBackground(level_sounds[level].background);
  }

  // START/STOP METHODS

  // CHANNEL 1: BOOST
  void startPlayBoost() {
    if (!boostIsPlaying) {
      PlayWav(boost, 1);
      boostIsPlaying = true;
    }
  }

  void stopPlayBoost() {
    StopChannel(1);
    boostIsPlaying = false;
  }

  // CHANNEL 2: TARGET
  void startPlayTargetHover() {
    if (!targetHoverIsPlaying) {
      PlayWav(targetHover, 2);
      targetHoverIsPlaying = true;
    }
  }

  void stopPlayTargetHover() {
    StopChannel(2);
    targetHoverIsPlaying = false;
  }

  // CHANNEL 1: FireworkLaunch

  // BACKGROUND METHODS
  void playStdBG() { setBackground(stdBG); }
  void playWinBG() { setBackground(winBG); }
};

}  // namespace rocket
}  // namespace games
}  // namespace kss
