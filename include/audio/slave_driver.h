#pragma once

#include <Audio.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Wire.h>

#include <string>
#include <vector>

#include "audio/channel.h"    // for Channel
#include "audio/constants.h"  // for k*
#include "audio/sounds.h"     // for InitAudio
#include "serial/debug.h"     // for debug::*

namespace kss {
namespace audio {

namespace slave_driver {

AudioPlaySdWav playSdWav[kChannelCount];

AudioMixer4 bgMixer;
AudioMixer4 mixer1;
AudioMixer4 mixer2;
AudioMixer4 effectMixer;
AudioMixer4 mixMaster;

AudioOutputI2S audioOutput;

// Sound effect channels to mixers

AudioConnection patchCordBGa(playSdWav[0], 0, bgMixer, 0);
AudioConnection patchCordBGb(playSdWav[0], 1, bgMixer, 1);

AudioConnection patchCord1a(playSdWav[1], 0, mixer1, 0);
AudioConnection patchCord1b(playSdWav[1], 1, mixer1, 1);
AudioConnection patchCord2a(playSdWav[2], 0, mixer1, 2);
AudioConnection patchCord2b(playSdWav[2], 1, mixer1, 3);

AudioConnection patchCord3a(playSdWav[3], 0, mixer2, 0);
AudioConnection patchCord3b(playSdWav[3], 1, mixer2, 1);
AudioConnection patchCord4a(playSdWav[4], 0, mixer2, 2);
AudioConnection patchCord4b(playSdWav[4], 1, mixer2, 3);

// Sound effects to single mixer
AudioConnection patchCordEffects1a(mixer1, 0, effectMixer, 0);
AudioConnection patchCordEffects1b(mixer1, 1, effectMixer, 1);
AudioConnection patchCordEffects2a(mixer2, 0, effectMixer, 2);
AudioConnection patchCordEffects2b(mixer2, 1, effectMixer, 3);

// Effects and Background to Master Mixer
AudioConnection patchCordToMaster1a(effectMixer, 0, mixMaster, 0);
AudioConnection patchCordToMaster1b(effectMixer, 1, mixMaster, 1);
AudioConnection patchCordToMaster2a(bgMixer, 0, mixMaster, 2);
AudioConnection patchCordToMaster2b(bgMixer, 1, mixMaster, 3);

// Master Mixer out
AudioConnection patchCordOut1a(mixMaster, 0, audioOutput, 0);
AudioConnection patchCordOut1b(mixMaster, 1, audioOutput, 1);

}  // namespace slave_driver
using namespace slave_driver;

class SlaveDriver {
  std::vector<Channel> channels;

 public:
  SlaveDriver() {
    for (size_t i = 0; i < kChannelCount; ++i) {
      channels.emplace_back(&playSdWav[i]);
    }
  }

  Channel& GetChannelByIndex(const size_t index) { return channels[index]; }

  Channel& GetIdleChannel() {
    const static size_t first_channel = 3;

    // Find first available channel, starting with first_channel
    for (size_t channel = first_channel; channel < kChannelCount; ++channel) {
      if (!channels[channel].IsPlaying()) {
        return channels[channel];
      }
    }

    // Default to first_channel if they're all already playing something
    debug::println("OVERWRITE==OVERWRITE==OVERWRITE (all channels playing)");
    return channels[first_channel];
  }

  Channel& GetChannel(const char channel_marker) {
    if (channel_marker == '?') {
      return GetIdleChannel();
    }

    const size_t index = GetChannelIndex(channel_marker);
    return channels[index];
  }

  // This is left for debug convenience only, unused by production code
  Channel& PlayWav(const char* file_name) {
    Channel& channel = GetIdleChannel();
    channel.Play(file_name);
    return channel;
  }

  void UpdateAll() {
	for(auto& channel : channels) {
		channel.Update();
	}
  }
};

}  // namespace audio
}  // namespace kss
