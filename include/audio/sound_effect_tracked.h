#pragma once

#include <memory>  // for shared_ptr

#include "audio/audio_sender.h"          // for AudioSender
#include "audio/sound_effect_bespoke.h"  // for SoundEffect

namespace kss {
namespace audio {

// TODO do we need this? we can remove tracking from *Bespoke but it still plays
// regardless

// This hard-wires a sound effect to a specific channel, but should be used
// sparingly. The is_playing is tracked internally and doesn't account for other
// sounds being played over this one on the same channel.
class SoundEffectTracked : public SoundEffectBespoke {
 public:
  bool is_playing{false};

  SoundEffectTracked(std::shared_ptr<AudioSender> audio_sender,
                     const size_t channel, const char* filename)
      : SoundEffectBespoke{audio_sender, channel, filename} {}

  virtual const void Play() override {
    audio_sender->PlayWav(filename, channel);
    is_playing = true;
  }

  virtual const void Stop() override {
    if (is_playing) {
      audio_sender->StopChannel(channel);
      is_playing = false;
    }
  }
};

}  // namespace audio
}  // namespace kss