// #include "audio/slave_driver.h"  // for SlaveDriver
// #include "serial/debug.h"        // for debug::*

// using namespace kss::audio;

// SlaveDriver slaveDriver;

// void setup() {
//   debug::Init();
//   debug::println("-=- Beginning SETUP -=-");

//   delay(5000);

//   // Fire up the boombox
//   InitAudio();

//   auto& channel = slaveDriver.GetChannelByIndex(2);
//   channel.Play("FUEL50.WAV");

//   auto& channel2 = slaveDriver.GetIdleChannel();
//   channel2.Play("MARSVOX.WAV");
//   slaveDriver.GetChannelByIndex(0).Repeat("BOOM.WAV");

//   while (channel.IsPlaying()) {
//     delay(1);
//   }

//   slaveDriver.GetChannelByIndex(1).Repeat("BOOM.WAV");

//   channel.Play("FUEL100.WAV");

//   slaveDriver.GetIdleChannel().Repeat("MOONVOX.WAV");

//   // Wait for at least one idle channel to free-up
//   while (channel2.IsPlaying()) {
//     delay(1);
//   }
//   slaveDriver.GetIdleChannel().Repeat("JPTRVOX.WAV");

//   debug::println("starting the loop");
// }

// void loop() { slaveDriver.UpdateAll(); }
