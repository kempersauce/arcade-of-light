#pragma once

#include <memory>  // for shared_ptr

#include "audio/audio_sender.h"          // for AudioSender
#include "audio/sound_effect_bespoke.h"  // for SoundEffectBespoke

namespace kss {
namespace audio {

class BackgroundMusic : public SoundEffectBespoke {
 public:
  BackgroundMusic(std::shared_ptr<AudioSender> audio_sender,
                  const char* filename)
      : SoundEffectBespoke(audio_sender, filename, 0) {}
};

}  // namespace audio
}  // namespace kss