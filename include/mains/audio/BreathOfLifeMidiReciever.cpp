#include <Wire.h>
#include <MIDI.h>

#include "audio/channel.h"       // for Channel
#include "audio/sounds.h"        // for audio::Init
#include "audio/wav_manager.h"   // for WavAudioManager
#include "engines/framerate.h"   // for Framerate
#include "pins/pin_setup.h"      // for pins::Init
#include "serial/debug.h"        // for Debug
#include "serial/ez_receiver.h"  // for EZReceiver
#include "time/now.h"            // for time::*
#include "audio/midi_breath_config.h"

using namespace kss;
using namespace kss::audio;

WavAudioManager wav_manager;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial4, MIDI);


void ProcessMidiMessage() {
  int note, velocity, channel, wavChannel, d1, d2, chimeIndex;
  byte type = MIDI.getType();
  note = MIDI.getData1();
  velocity = MIDI.getData2();
  channel = MIDI.getChannel();
  if(type == midi::NoteOn) {
    Serial.println(String("Note On:  ch=") + channel + ", note=" + note + ", velocity=" + velocity);

    chimeIndex = noteSampleMapping(note);
    const char *wavFile = getChimeAudioName(channel, chimeIndex, velocity);

    wavChannel = channel - 1;
    char wavChannelChar = chimeIndex;
    Channel& channel = wav_manager.PlayWav(wavFile);
    // channel.Play(wavFile);
  }

}


//=============================================================================//
// SETUP AND LOOP
void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  // Fire up the boombox
  audio::Init();


  // Set gain on channels
  float gain = 0.5;
  float gainStandard = 0.5;
  for(int channel_index = 0; channel_index < 6; channel_index++ ){
    Channel& channel = wav_manager.GetChannel(channel_index);
    channel.SetGain(gain);
  }

  // Get Midi going
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(57600);
  Serial.println("MIDI Setup Complete");

  time::SetLoopTime();
  Channel& channel = wav_manager.PlayWav("FUEL50.WAV");
  while (channel.IsPlaying()) {
    time::SetLoopTime();
  }

  Debug("starting the loop");
}

void loop() {
  time::SetLoopTime();
  if (MIDI.read()) {
    ProcessMidiMessage();
  }
  wav_manager.UpdateAll();

  //   framerate.PrintFrameRate();
}
