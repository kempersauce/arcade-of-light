#pragma once

#include <memory>  // for shared_ptr

#include "audio/audio_sender.h"  // for AudioSender

namespace kss {
namespace audio {

class SoundEffect {
 protected:
  const std::shared_ptr<AudioSender> audio_sender;
  const char* filename;

 public:
  SoundEffect(std::shared_ptr<AudioSender> audio_sender, const char* filename)
      : audio_sender{audio_sender}, filename{filename} {}

  virtual const void Play() { audio_sender->PlayWav(filename); }
};

}  // namespace audio
}  // namespace kss