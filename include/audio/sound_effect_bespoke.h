#pragma once

#include <memory>  // for shared_ptr

#include "audio/audio_sender.h"  // for AudioSender
#include "audio/sound_effect.h"  // for SoundEffect

namespace kss {
namespace audio {

// This hard-wires a sound effect to a specific channel, but should be used
// sparingly. The is_playing is tracked internally and doesn't account for other
// sounds being played over this one on the same channel.
class SoundEffectBespoke : public SoundEffect {
  const size_t channel;

 public:
  bool is_playing{false};

  SoundEffectBespoke(std::shared_ptr<AudioSender> audio_sender,
                     const size_t channel, const char* filename)
      : SoundEffect{audio_sender, filename}, channel{channel} {}

  virtual const void Play() override {
    audio_sender->PlayWav(filename, channel);
    is_playing = true;
  }

  const void Stop() {
    if (is_playing) {
      audio_sender->StopChannel(channel);
      is_playing = false;
    }
  }
};

}  // namespace audio
}  // namespace kss