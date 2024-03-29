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

  LevelAudio(std::shared_ptr<audio::AudioSender> sender, const char* intro,
             const char* background)
      : Manager(sender), intro{sender, intro}, background{sender, background} {}
};

class RocketAudio : public audio::Manager {
 public:
  // Single effects
  audio::SoundEffect explosion{sender, "EXPLODE1.WAV"};
  audio::SoundEffect win{sender, "BOOM.WAV"};
  audio::SoundEffect targetWin{sender, "TRGTHIT5.WAV"};
  audio::SoundEffectBespoke levelWin{sender, 1, "LIFTOFF.WAV"};
  audio::SoundEffectBespoke lose{sender, 1, "ABORTSEQ.WAV"};

  // Level specific audio
  LevelAudio level_sounds[5] = {
      LevelAudio{sender, "EARTHVOX.WAV", "EARTH.WAV"},
      LevelAudio{sender, "MOONVOX.WAV", "MOONJAZZ.WAV"},
      LevelAudio{sender, "MARSVOX.WAV", "MARS.WAV"},
      LevelAudio{sender, "JPTRVOX.WAV", "JUPITER.WAV"},
      LevelAudio{sender, "PLUTOVOX.WAV", "PLUTO.WAV"},
  };

  // File names and controls for start/stop channels
  audio::SoundEffectBespoke boost{sender, 1, "THRUST2.WAV"};

  // Just leaving this one open for now
  // I don't think we need a specific channel for it
  audio::SoundEffectBespoke super_boost{sender, 2, "SPRBOOST.WAV"};

  audio::SoundEffectBespoke targetHover{sender, 3, "TRGTSEQ.WAV"};
  audio::SoundEffect fireworkLaunch{sender, "TRGTMIS1.WAV"};
  audio::SoundEffect fireworkExplode{sender, "EXPLODE1.WAV"};

  // SINGLE EFFECT METHODS
  void playWin() { win.Play(); }
  void playTargetWin() { targetWin.Play(); }
  void playLevelWin() { levelWin.Play(); }

  void killChannels() {
    boost.Stop();
    super_boost.Stop();
    targetHover.Stop();
    levelWin.Stop();
    lose.Stop();
    sender->StopChannel(4);
    sender->StopChannel(5);
  }

  void playLevelIntro(const size_t level) {
    killChannels();
    level_sounds[level].intro.Play();
    level_sounds[level].background.Repeat();
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
};

}  // namespace rocket
}  // namespace games
}  // namespace kss
