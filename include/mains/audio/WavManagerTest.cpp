#include "audio/sounds.h"       // for InitAudio
#include "audio/wav_manager.h"  // for WavAudioManager
#include "pins/pin_setup.h"     // for pins::Init
#include "serial/debug.h"       // for Debug

using namespace kss;
using namespace kss::audio;

WavAudioManager wav_manager;

void setup() {
  Debug_init();
  pins::Init();
  // Fire up the boombox
  audio::InitAudio();

  Debug("-=- Beginning SETUP -=-");

  auto& channel = wav_manager.GetChannelByIndex(2);
  channel.Play("FUEL50.WAV");

  auto& channel2 = wav_manager.GetIdleChannel();
  channel2.Play("MARSVOX.WAV");
  wav_manager.GetChannelByIndex(0).Play("MOONJAZZ.WAV");
  wav_manager.GetIdleChannel().Play("MOONVOX.WAV");

  while (wav_manager.GetChannelByIndex(0).IsPlaying()) {
    delay(1);
  }
  wav_manager.GetChannelByIndex(0).Play("EARTH.WAV");
  wav_manager.GetIdleChannel().Play("EARTHVOX.WAV");

  while (wav_manager.GetChannelByIndex(0).IsPlaying()) {
    delay(1);
  }
  wav_manager.GetChannelByIndex(0).Play("MARS.WAV");
  wav_manager.GetIdleChannel().Play("MARSVOX.WAV");

  while (wav_manager.GetChannelByIndex(0).IsPlaying()) {
    delay(1);
  }
  wav_manager.GetChannelByIndex(0).Play("JUPITER.WAV");
  wav_manager.GetIdleChannel().Play("JPTRVOX.WAV");

  while (wav_manager.GetChannelByIndex(0).IsPlaying()) {
    delay(1);
  }
  wav_manager.GetChannelByIndex(0).Play("PLUTO.WAV");
  wav_manager.GetIdleChannel().Play("PLUTOVOX.WAV");

  while (wav_manager.GetChannelByIndex(0).IsPlaying()) {
    delay(1);
  }
  wav_manager.GetChannelByIndex(0).Play("BOOM.WAV");

  //   wav_manager.GetChannelByIndex(1).Repeat("BOOM.WAV");

  // channel.Play("FUEL100.WAV");

  //   wav_manager.GetIdleChannel().Repeat("MOONVOX.WAV");

  // Wait for at least one idle channel to free-up
  //   while (channel2.IsPlaying()) {
  //     delay(1);
  //   }
  //   wav_manager.GetIdleChannel().Repeat("JPTRVOX.WAV");

  Debug("starting the loop");
}

void loop() { wav_manager.UpdateAll(); }
