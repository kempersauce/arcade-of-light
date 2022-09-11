#include "audio/slave_driver.h"  // for SlaveDriver
#include "serial/debug.h"        // for Debug

using namespace kss::audio;

SlaveDriver slaveDriver;

void setup() {
  Debug_init();
  Debug("-=- Beginning SETUP -=-");

  // Fire up the boombox
  InitAudio();

//   auto& channel = slaveDriver.GetChannelByIndex(2);
//   channel.Play("FUEL50.WAV");

//   auto& channel2 = slaveDriver.GetIdleChannel();
//   channel2.Play("MARSVOX.WAV");
  slaveDriver.GetChannelByIndex(0).Play("MOONJAZZ.WAV");
  slaveDriver.GetIdleChannel().Play("MOONVOX.WAV");

  while (slaveDriver.GetChannelByIndex(0).IsPlaying()) {
    delay(1);
  }
  slaveDriver.GetChannelByIndex(0).Play("EARTH.WAV");
  slaveDriver.GetIdleChannel().Play("EARTHVOX.WAV");

  while (slaveDriver.GetChannelByIndex(0).IsPlaying()) {
    delay(1);
  }
  slaveDriver.GetChannelByIndex(0).Play("MARS.WAV");
  slaveDriver.GetIdleChannel().Play("MARSVOX.WAV");

  while (slaveDriver.GetChannelByIndex(0).IsPlaying()) {
    delay(1);
  }
  slaveDriver.GetChannelByIndex(0).Play("JUPITER.WAV");
  slaveDriver.GetIdleChannel().Play("JPTRVOX.WAV");

  while (slaveDriver.GetChannelByIndex(0).IsPlaying()) {
    delay(1);
  }
  slaveDriver.GetChannelByIndex(0).Play("PLUTO.WAV");
  slaveDriver.GetIdleChannel().Play("PLUTOVOX.WAV");

  while (slaveDriver.GetChannelByIndex(0).IsPlaying()) {
    delay(1);
  }
  slaveDriver.GetChannelByIndex(0).Play("BOOM.WAV");

//   slaveDriver.GetChannelByIndex(1).Repeat("BOOM.WAV");

  //channel.Play("FUEL100.WAV");

//   slaveDriver.GetIdleChannel().Repeat("MOONVOX.WAV");

  // Wait for at least one idle channel to free-up
//   while (channel2.IsPlaying()) {
//     delay(1);
//   }
//   slaveDriver.GetIdleChannel().Repeat("JPTRVOX.WAV");

  Debug("starting the loop");
}

void loop() { slaveDriver.UpdateAll(); }
