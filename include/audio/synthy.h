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
#include "serial/debug.h"  // for Debug

namespace kss {
namespace audio {
namespace _synthy {
AudioSynthWaveform waveform1;   // xy=171,84 PAUL SHIT
AudioSynthWaveform waveform2;   // xy=178,148 PAUL SHIT
AudioSynthWaveform waveform3;   // xy=171,84 PAUL SHIT
AudioSynthWaveform waveform4;   // xy=178,148 PAUL SHIT
AudioSynthWaveform waveform5;   // xy=171,84 PAUL SHIT
AudioSynthWaveform waveform6;   // xy=178,148 PAUL SHIT
AudioOutputI2S i2s1;            // xy=360,98 PAUL SHIT
AudioOutputAnalogStereo dacs1;  // xy=372,173
AudioMixer4 effectMixer;
AudioMixer4 mixer1;
AudioMixer4 mixerMaster;

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

// only send moving note to chorus effect 
AudioConnection patchCordChorusL(waveform1, 0, l_chorusEffect, 0);
AudioConnection patchCordChorusR(waveform1, 1, r_chorusEffect, 1);
// Effects Mixer
AudioConnection patchCordChorusLOut(l_chorusEffect, 0, effectMixer, 0);
AudioConnection patchCordChorusROut(r_chorusEffect, 1, effectMixer, 1);
AudioConnection patchCordRawWave2L(waveform2, 0, effectMixer, 2);
AudioConnection patchCordRawWave2R(waveform2, 1, effectMixer, 3);
//mixer1 - input from other 4
AudioConnection patchCordRawWave3(waveform3, 0, mixer1, 0);
AudioConnection patchCordRawWave4(waveform4, 0, mixer1, 1);
AudioConnection patchCordRawWave5(waveform5, 0, mixer1, 2);
AudioConnection patchCordRawWave6(waveform6, 0, mixer1, 3);
//mixerMaster - put it all togeter
AudioConnection patchCordMaster1(mixer1, 0, mixerMaster, 0);
AudioConnection patchCordMaster2(effectMixer, 1, mixerMaster, 1);

// final output
AudioConnection patchCord1(mixerMaster, 0, i2s1, 0);
AudioConnection patchCord2(mixerMaster, 0, i2s1, 1);
AudioConnection patchCord3(mixerMaster, 0, dacs1, 0);
AudioConnection patchCord4(mixerMaster, 0, dacs1, 1);

AudioControlSGTL5000 sgtl5000_1;  // xy=239,232
}  // namespace synth
using namespace _synthy;

class Synthy {
 public:
  float frequency = 256;  // middle C
  
  // NOTE REFERENCE: https://pages.mtu.edu/~suits/notefreqs.html
  float sequence[4] = {256, 311.13, 369.99, 554.37};
  float cMaj7[6] = {256.00, 329.63, 392.00, 493.88, 659.25, 783.99};
  uint32_t next_hit = 0;
  unsigned long last_time = millis();

  float wave1Amplitude = 0;
  float wave2Amplitude = 0;
  float wave3Amplitude = 0;
  float wave4Amplitude = 0;
  float wave5Amplitude = 0;
  float wave6Amplitude = 0;

  size_t i = 0;

  Synthy() {
    Debug("hello");
  };

  const void InitSynth() {
    Serial.begin(9600);

    AudioMemory(14);

    // Comment these out if not using the audio adaptor board.
    // This may wait forever if the SDA & SCL pins lack
    // pullup resistors
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.8);  // caution: very loud - use oscilloscope only!

    // set up dat chord
    waveform1.frequency(cMaj7[0]);
    waveform2.frequency(cMaj7[1]);
    waveform3.frequency(cMaj7[2]);
    waveform4.frequency(cMaj7[3]);
    waveform5.frequency(cMaj7[4]);
    waveform6.frequency(cMaj7[5]);

    waveform1.amplitude(wave1Amplitude);
    waveform2.amplitude(wave2Amplitude);
    waveform3.amplitude(wave3Amplitude);
    waveform4.amplitude(wave4Amplitude);
    waveform5.amplitude(wave5Amplitude);
    waveform6.amplitude(wave6Amplitude);

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
  

  // waveform1.frequency(sequence[i]);
  // waveform2.frequency(391.995);
  AudioNoInterrupts();
  waveform1.amplitude(wave1Amplitude);
  waveform2.amplitude(wave2Amplitude);
  waveform3.amplitude(wave3Amplitude);
  waveform4.amplitude(wave4Amplitude);
  waveform5.amplitude(wave5Amplitude);
  waveform6.amplitude(wave6Amplitude);
  AudioInterrupts();

  AudioNoInterrupts();
  waveform1.begin(WAVEFORM_SAWTOOTH);
  waveform2.begin(WAVEFORM_SAWTOOTH);
  waveform3.begin(WAVEFORM_SAWTOOTH);
  waveform4.begin(WAVEFORM_SAWTOOTH);
  waveform5.begin(WAVEFORM_SAWTOOTH);
  waveform6.begin(WAVEFORM_SAWTOOTH);
  AudioInterrupts();
  Debug("played note");
  //add effect
  l_chorusEffect.voices(n_chorus);
  r_chorusEffect.voices(n_chorus);
  audioDebug();
  }

  const void audioDebug() {
    if(0) {
      if(millis() - last_time >= 5000) {
        Debug("Proc = ");
        Debug(AudioProcessorUsage());
        Debug(" (");    
        Debug(AudioProcessorUsageMax());
        Debug("),  Mem = ");
        Debug(AudioMemoryUsage());
        Debug(" (");    
        Debug(AudioMemoryUsageMax());
        Debug(")");
        last_time = millis();
      }
    }
  }

};  // class
}  // namespace audio
}  // namespace kss