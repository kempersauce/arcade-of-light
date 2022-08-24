#pragma once

#include <memory>  // for std::shared_ptr

#include "audio/audio_sender.h"          // for AudioSender
#include "audio/background_music.h"      // for BackgroundMusic
#include "audio/manager.h"               // for audio::Manager
#include "audio/sound_effect.h"          // for SoundEffect
#include "audio/sound_effect_bespoke.h"  // for SoundEffectBespoke

namespace kss {
namespace games {
namespace rocket {

// Sub-manager handles level-specific sounds
class LevelAudio : public audio::Manager {
 public:
  audio::SoundEffect intro;
  audio::BackgroundMusic background;

  LevelAudio(std::shared_ptr<audio::AudioSender> audio_sender,
             const char* intro, const char* background)
      : Manager(audio_sender),
        intro{audio_sender, intro},
        background{audio_sender, background} {}
};

class RocketAudio : public audio::Manager {
 public:
  // Single effects
  audio::SoundEffect explosion{audio_sender, "EXPLODE1.WAV"};
  audio::SoundEffect win{audio_sender, "BOOM.WAV"};
  audio::SoundEffect targetWin{audio_sender, "TRGTHIT5.WAV"};
  audio::SoundEffectBespoke levelWin{audio_sender, 1, "LIFTOFF.WAV"};

  // Background music
  audio::BackgroundMusic winBG{audio_sender, "EARTH.WAV"};
  audio::BackgroundMusic stdBG{audio_sender, "EARTH.WAV"};

  // Level specific audio
  LevelAudio level_sounds[5] = {
      LevelAudio{audio_sender, "EARTHVOX.WAV", "EARTH.WAV"},
      LevelAudio{audio_sender, "MOONVOX.WAV", "MOONJAZZ.WAV"},
      LevelAudio{audio_sender, "MARSVOX.WAV", "MARS.WAV"},
      LevelAudio{audio_sender, "JPTRVOX.WAV", "JUPITER.WAV"},
      LevelAudio{audio_sender, "PLUTOVOX.WAV", "PLUTO.WAV"},
  };

  // File names and controls for start/stop channels
  audio::SoundEffectBespoke boost{audio_sender, 1, "THRUST2.WAV"};
  audio::SoundEffectBespoke targetHover{audio_sender, 2, "TRGTSEQ.WAV"};
  audio::SoundEffect fireworkLaunch{audio_sender, "TRGTMIS1.WAV"};
  audio::SoundEffect fireworkExplode{audio_sender, "EXPLODE1.WAV"};

  // SINGLE EFFECT METHODS
  void playExplosion() { explosion.Play(); }
  void playWin() { win.Play(); }
  void playTargetWin() { targetWin.Play(); }
  void playLevelWin() { levelWin.Play(); }
  void playFireWorkLaunch() { fireworkLaunch.Play(); }
  void playFireWorkExplode() { fireworkExplode.Play(); }

  void killChannels() {
    audio_sender->StopChannel(2);
    delay(5);  // TODO can we get rid of these delays?
    audio_sender->StopChannel(1);
    delay(5);
    // serial.println("<aa>"); // TODO what does this do exactly?
    // delay(5);
    // serial.println("<aa>");
    // delay(5);
  }

  void playLevelIntro(const size_t level) {
    killChannels();
    level_sounds[level].intro.Play();
    level_sounds[level].background.Play();
  }

  // START/STOP METHODS

  // CHANNEL 1: BOOST
  void startPlayBoost() {
    if (!boost.is_playing) {
      boost.Play();
    }
  }

  void stopPlayBoost() { boost.Stop(); }

  // CHANNEL 2: TARGET
  void startPlayTargetHover() {
    if (!targetHover.is_playing) {
      targetHover.Play();
    }
  }

  void stopPlayTargetHover() { targetHover.Stop(); }

  // CHANNEL 1: FireworkLaunch

  // BACKGROUND METHODS
  void playStdBG() { stdBG.Play(); }
  void playWinBG() { winBG.Play(); }
};

}  // namespace rocket
}  // namespace games
}  // namespace kss
