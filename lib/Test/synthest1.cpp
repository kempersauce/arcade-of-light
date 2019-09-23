#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=406,530
AudioEffectEnvelope      envelope1;      //xy=604,542
AudioOutputI2S           i2s1;           //xy=763,540
AudioConnection          patchCord1(waveform1, envelope1);
AudioConnection          patchCord2(envelope1, 0, i2s1, 0);
AudioConnection          patchCord3(envelope1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=506,796
// GUItool: end automatically generated code

void setup() {
  AudioMemory(15);
  // put your setup code here, to run once:


 sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);
  waveform1.begin(1, 440, WAVEFORM_SINE);

envelope1.attack(1);
envelope1.hold(100);
envelope1.decay(200);
envelope1.sustain(0.5);
envelope1.release(200);


}

void loop() {
  // put your main code here, to run repeatedly:

envelope1.noteOn();
delay(3000);   //sleep the program for 3 seconds.
envelope1.noteOff();
delay(1000);

}
