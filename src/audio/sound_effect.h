#pragma once

#include <memory>  // for shared_ptr

#include "audio/audio_sender.h"  // for AudioSender

namespace kss {
namespace audio {

class SoundEffect {
 protected:
  std::shared_ptr<AudioSender> sender;
  const char* filename;

 public:
  SoundEffect(std::shared_ptr<AudioSender> sender, const char* filename)
      : sender{sender}, filename{filename} {}

  virtual void Play() { sender->PlayWav(filename); }
};

}  // namespace audio
}  // namespace kss
