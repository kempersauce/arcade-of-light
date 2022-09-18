#include "audio/music_notes.h"  // for notes
#include "audio/sounds.h"       // for InitAudio
#include "audio/track.h"        // for AudioTrack
#include "serial/debug.h"       // for Debug

using namespace kss::audio;

AudioTrack track;

AudioOutputI2S audio_out;
AudioConnection patch_out{track.synth.envelope, 0, audio_out, 0};

void setup() {
  Debug_init();

  // Fire up the boombox
  InitAudio();

  track.synth.wave.frequency(notes::C_Pentatonic[2]);
  track.Play();
  Debug("starting the loop");
}

void loop() { track.Update(); }
