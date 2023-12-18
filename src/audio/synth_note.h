#pragma once

#include <Audio.h>

#include "audio/music_notes.h"  // for notes::*
#include "serial/debug.h"       // for Debug

namespace kss {
namespace audio {

struct SynthNote {
  AudioSynthWaveform wave;
  AudioFilterBiquad filter;
  AudioEffectEnvelope envelope;

  AudioConnection patch_wave_out;
  AudioConnection patch_filter_out;

  SynthNote()
      : patch_wave_out{wave, 0, filter, 0},
        patch_filter_out{filter, 0, envelope, 0} {
    // Set up wave
    wave.begin(1, 0, WAVEFORM_SINE);

    // set up filter
    filter.setLowpass(0, 800, 0.707);

    // set up envelope
    envelope.attack(1);
    envelope.hold(100);
    envelope.decay(200);
    envelope.sustain(0.5);
    envelope.release(200);
  }
};

}  // namespace audio
}  // namespace kss
