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
 protected:
  const size_t channel;

 public:
  bool is_playing{false};

  SoundEffectBespoke(std::shared_ptr<AudioSender> sender, const size_t channel,
                     const char* filename)
      : SoundEffect{sender, filename}, channel{channel} {}

  virtual void Play() override {
    sender->PlayWav(filename, channel);
    is_playing = true;
  }

  virtual void Repeat() {
    sender->RepeatWav(filename, channel);
    is_playing = true;
  }

  const void Stop() {
    if (is_playing) {
      sender->StopChannel(channel);
      is_playing = false;
    }
  }
};

}  // namespace audio
}  // namespace kss
