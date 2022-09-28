#include "audio/music_notes.h"  // for notes
#include "audio/sounds.h"       // for InitAudio
#include "audio/track.h"        // for AudioTrack
#include "pins/pin_setup.h"     // for pins::Init
#include "serial/debug.h"       // for Debug

using namespace kss;
using namespace kss::audio;

AudioTrack track;

AudioOutputI2S audio_out;
AudioConnection patch_out{track.synth.envelope, 0, audio_out, 0};

void setup() {
  Debug_init();
  pins::Init();

  // Fire up the boombox
  InitAudio();

  track.synth.wave.frequency(notes::C_Pentatonic[2]);
  track.Play();
  Debug("starting the loop");
}

void loop() { track.Update(); }
