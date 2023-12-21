// Waveform Example - Create 2 waveforms with adjustable
// frequency and phase
//
// This example is meant to be used with 3 buttons (pin 0,
// 1, 2) and 2 knobs (pins 16/A2, 17/A3), which are present
// on the audio tutorial kit.
//   https://www.pjrc.com/store/audio_tutorial_kit.html
//
// Use an oscilloscope to view the 2 waveforms.
//
// Button0 changes the waveform shape
//
// Knob A2 changes the frequency of both waveforms
//   You should see both waveforms "stretch" as you turn
//
// Knob A3 changes the phase of waveform #1
//   You should see the waveform shift horizontally
//
// This example code is in the public domain.

#include <Audio.h>
#include <Bounce.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Wire.h>

AudioSynthWaveform waveform1;   // xy=171,84
AudioSynthWaveform waveform2;   // xy=178,148
AudioOutputI2S i2s1;            // xy=360,98
AudioOutputAnalogStereo dacs1;  // xy=372,173
AudioConnection patchCord1(waveform1, 0, i2s1, 0);
AudioConnection patchCord2(waveform1, 0, dacs1, 0);
AudioConnection patchCord3(waveform2, 0, i2s1, 1);
AudioConnection patchCord4(waveform2, 0, dacs1, 1);
AudioControlSGTL5000 sgtl5000_1;  // xy=239,232

// Bounce button0 = Bounce(0, 15);
// Bounce button1 = Bounce(1, 15);
// Bounce button2 = Bounce(2, 15);

int current_waveform = 0;

const int16_t myWaveform[256] = {
    0,      1895,   3748,   5545,   7278,   8934,   10506,  11984,  13362,
    14634,  15794,  16840,  17769,  18580,  19274,  19853,  20319,  20678,
    20933,  21093,  21163,  21153,  21072,  20927,  20731,  20492,  20221,
    19929,  19625,  19320,  19022,  18741,  18486,  18263,  18080,  17942,
    17853,  17819,  17841,  17920,  18058,  18254,  18507,  18813,  19170,
    19573,  20017,  20497,  21006,  21538,  22085,  22642,  23200,  23753,
    24294,  24816,  25314,  25781,  26212,  26604,  26953,  27256,  27511,
    27718,  27876,  27986,  28049,  28068,  28047,  27989,  27899,  27782,
    27644,  27490,  27326,  27159,  26996,  26841,  26701,  26582,  26487,
    26423,  26392,  26397,  26441,  26525,  26649,  26812,  27012,  27248,
    27514,  27808,  28122,  28451,  28787,  29124,  29451,  29762,  30045,
    30293,  30495,  30643,  30727,  30738,  30667,  30509,  30254,  29897,
    29433,  28858,  28169,  27363,  26441,  25403,  24251,  22988,  21620,
    20150,  18587,  16939,  15214,  13423,  11577,  9686,   7763,   5820,
    3870,   1926,   0,      -1895,  -3748,  -5545,  -7278,  -8934,  -10506,
    -11984, -13362, -14634, -15794, -16840, -17769, -18580, -19274, -19853,
    -20319, -20678, -20933, -21093, -21163, -21153, -21072, -20927, -20731,
    -20492, -20221, -19929, -19625, -19320, -19022, -18741, -18486, -18263,
    -18080, -17942, -17853, -17819, -17841, -17920, -18058, -18254, -18507,
    -18813, -19170, -19573, -20017, -20497, -21006, -21538, -22085, -22642,
    -23200, -23753, -24294, -24816, -25314, -25781, -26212, -26604, -26953,
    -27256, -27511, -27718, -27876, -27986, -28049, -28068, -28047, -27989,
    -27899, -27782, -27644, -27490, -27326, -27159, -26996, -26841, -26701,
    -26582, -26487, -26423, -26392, -26397, -26441, -26525, -26649, -26812,
    -27012, -27248, -27514, -27808, -28122, -28451, -28787, -29124, -29451,
    -29762, -30045, -30293, -30495, -30643, -30727, -30738, -30667, -30509,
    -30254, -29897, -29433, -28858, -28169, -27363, -26441, -25403, -24251,
    -22988, -21620, -20150, -18587, -16939, -15214, -13423, -11577, -9686,
    -7763,  -5820,  -3870,  -1926};

void setup() {
  Serial.begin(9600);

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(10);

  // Comment these out if not using the audio adaptor board.
  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);  // caution: very loud - use oscilloscope only!

  // Confirgure both to use "myWaveform" for WAVEFORM_ARBITRARY
  //   waveform1.arbitraryWaveform(myWaveform, 172.0);
  //   waveform2.arbitraryWaveform(myWaveform, 172.0);

  // configure both waveforms for 440 Hz and maximum amplitude
  waveform1.frequency(440);
  waveform2.frequency(440);
  waveform1.amplitude(1.0);
  waveform2.amplitude(1.0);

  //   current_waveform = WAVEFORM_TRIANGLE;
  waveform1.begin(WAVEFORM_TRIANGLE);
}

void loop() {
  //   float knob_A2 = (float)analogRead(A2) / 1023.0;
  //   float knob_A3 = (float)analogRead(A3) / 1023.0;

  AudioNoInterrupts();
  // use Knob A2 to adjust the frequency of both waveforms
  waveform1.frequency(256);
  waveform2.frequency(391.995);
  // use Knob A3 to adjust the phase of only waveform #1
  //   waveform1.phase(360.0);
  AudioInterrupts();

  // Button 0 changes the waveform type
  //   if (button0.fallingEdge()) {
  //     switch (current_waveform) {
  //       case WAVEFORM_SINE:
  //         current_waveform = WAVEFORM_SAWTOOTH;
  //         Serial.println("Sawtooth");
  //         break;
  //       case WAVEFORM_SAWTOOTH:
  //         current_waveform = WAVEFORM_SAWTOOTH_REVERSE;
  //         Serial.println("Reverse Sawtooth");
  //         break;
  //       case WAVEFORM_SAWTOOTH_REVERSE:
  //         current_waveform = WAVEFORM_SQUARE;
  //         Serial.println("Square");
  //         break;
  //       case WAVEFORM_SQUARE:
  //         current_waveform = WAVEFORM_TRIANGLE;
  //         Serial.println("Triangle");
  //         break;
  //       case WAVEFORM_TRIANGLE:
  //         current_waveform = WAVEFORM_TRIANGLE_VARIABLE;
  //         Serial.println("Variable Triangle");
  //         break;
  //       case WAVEFORM_TRIANGLE_VARIABLE:
  //         current_waveform = WAVEFORM_ARBITRARY;
  //         Serial.println("Arbitary Waveform");
  //         break;
  //       case WAVEFORM_ARBITRARY:
  //         current_waveform = WAVEFORM_PULSE;
  //         Serial.println("Pulse");
  //         break;
  //       case WAVEFORM_PULSE:
  //         current_waveform = WAVEFORM_SAMPLE_HOLD;
  //         Serial.println("Sample & Hold");
  //         break;
  //       case WAVEFORM_SAMPLE_HOLD:
  //         current_waveform = WAVEFORM_SINE;
  //         Serial.println("Sine");
  //         break;
  //     }
  AudioNoInterrupts();
  waveform1.begin(current_waveform);
  waveform2.begin(WAVEFORM_SINE);
  AudioInterrupts();
  //   }
}
