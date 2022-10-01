#pragma once

#include <memory>  // for std::shared_ptr

#include "audio/audio_sender.h"  // for AudioSender

namespace kss {
namespace audio {

// Base class used by games to implement their own audio manager
class Manager {
 protected:
  std::shared_ptr<audio::AudioSender> sender;

 public:
  // Default constructor creates its own AudioSender
  Manager() : sender{std::make_shared<audio::AudioSender>()} {}

  // But you can also re-use an existing AudioSender
  Manager(std::shared_ptr<audio::AudioSender> sender) : sender{sender} {}
};

}  // namespace audio
}  // namespace kss
