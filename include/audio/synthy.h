#pragma once

#include <Audio.h>
#include <Bounce.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Wire.h>

// #include "audio/channel.h"    // for Channel
#include "audio/constants.h"  // for k*
// #include "audio/sounds.h"     // for InitAudio
#include "serial/debug.h"  // for debug::*

namespace kss {
namespace audio {
namespace _synthy {
AudioSynthWaveform waveform1;   // xy=171,84 PAUL SHIT
AudioSynthWaveform waveform2;   // xy=178,148 PAUL SHIT
AudioOutputI2S i2s1;            // xy=360,98 PAUL SHIT
AudioOutputAnalogStereo dacs1;  // xy=372,173
AudioMixer4 effectMixer;

// CHORUS EFFECT
AudioEffectChorus   l_chorusEffect;
AudioEffectChorus   r_chorusEffect;
// Number of samples in each delay line
#define CHORUS_DELAY_LENGTH (16*AUDIO_BLOCK_SAMPLES)
// Allocate the delay lines for left and right channels
short l_delayline[CHORUS_DELAY_LENGTH];
short r_delayline[CHORUS_DELAY_LENGTH];
// number of "voices" in the chorus which INCLUDES the original voice
int n_chorus = 2;

//only send moving note to chorus effect 
AudioConnection patchCordChorusL(waveform1, 0, l_chorusEffect, 0);
AudioConnection patchCordChorusR(waveform1, 1, r_chorusEffect, 1);
AudioConnection patchCordChorusLOut(waveform1, 0, effectMixer, 0);
AudioConnection patchCordChorusROut(waveform1, 1, effectMixer, 1);


AudioConnection patchCordRawWave2L(waveform2, 0, effectMixer, 2);
AudioConnection patchCordRawWave2R(waveform2, 1, effectMixer, 3);

AudioConnection patchCord1(effectMixer, 0, i2s1, 0);
AudioConnection patchCord2(effectMixer, 0, i2s1, 1);
AudioConnection patchCord3(effectMixer, 0, dacs1, 0);
AudioConnection patchCord4(effectMixer, 0, dacs1, 1);

AudioControlSGTL5000 sgtl5000_1;  // xy=239,232
}  // namespace synth
using namespace _synthy;

class Synthy {
 public:
  float frequency = 256;  // middle C
  float sequence[4] = {256, 311.13, 369.99, 554.37};
  uint32_t next_hit = 0;
  unsigned long last_time = millis();

  size_t i = 0;

  Synthy() {
    debug::println("hello");
  };

  const void InitSynth() {
    Serial.begin(9600);

    AudioMemory(14);

    // Comment these out if not using the audio adaptor board.
    // This may wait forever if the SDA & SCL pins lack
    // pullup resistors
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.8);  // caution: very loud - use oscilloscope only!

    // configure both waveforms for 440 Hz and maximum amplitude
    waveform1.frequency(440);
    waveform2.frequency(440);
    waveform1.amplitude(1.0);
    waveform2.amplitude(1.0);

    waveform1.begin(WAVEFORM_TRIANGLE);

    // Initialize the effect - left channel
    // address of delayline
    // total number of samples in the delay line
    // number of voices in the chorus INCLUDING the original voice
    if(!l_chorusEffect.begin(l_delayline,CHORUS_DELAY_LENGTH,n_chorus)) {
      Serial.println("AudioEffectChorus - left channel begin failed");
      while(1);
    }

    // Initialize the effect - right channel
    // address of delayline
    // total number of samples in the delay line
    // number of voices in the chorus INCLUDING the original voice
    if(!r_chorusEffect.begin(r_delayline,CHORUS_DELAY_LENGTH,n_chorus)) {
      Serial.println("AudioEffectChorus - left channel begin failed");
      while(1);
    }
    // Initially the effect is off. It is switched on when the
    // PASSTHRU button is pushed.
    l_chorusEffect.voices(0);
    r_chorusEffect.voices(0);


    effectMixer.gain(0, 0.5);
    effectMixer.gain(1, 0.5);

    Serial.println("setup done");
    AudioProcessorUsageMaxReset();
    AudioMemoryUsageMaxReset();
  }

  const void Play() {
    audioDebug();
    AudioNoInterrupts();
    const uint32_t now = millis();
    if (now >= next_hit) {
      // do it
      if (++i >= 4) {
        i = 0;
      }
    }
    next_hit = now + 500;
  

  waveform1.frequency(sequence[i]);
  waveform2.frequency(391.995);

  // waveform1.amplitude(1.0);
  // waveform2.amplitude(1.0);
  AudioInterrupts();

  AudioNoInterrupts();
  waveform1.begin(0);
  waveform2.begin(WAVEFORM_SINE);
  AudioInterrupts();
  debug::println("played note");
  //add effect
  l_chorusEffect.voices(n_chorus);
  r_chorusEffect.voices(n_chorus);
  audioDebug();
  }

  const void audioDebug() {
    if(0) {
      if(millis() - last_time >= 5000) {
        debug::println("Proc = ");
        debug::println(AudioProcessorUsage());
        debug::println(" (");    
        debug::println(AudioProcessorUsageMax());
        debug::println("),  Mem = ");
        debug::println(AudioMemoryUsage());
        debug::println(" (");    
        debug::println(AudioMemoryUsageMax());
        debug::println(")");
        last_time = millis();
      }
    }
  }

};  // class
}  // namespace audio
}  // namespace kss