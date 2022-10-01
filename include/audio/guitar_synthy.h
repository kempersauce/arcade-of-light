#pragma once

#include <Audio.h>

#include "audio/music_notes.h"  // for notes::*
#include "serial/debug.h"       // for Debug

namespace kss {
namespace audio {
namespace _guitar {

AudioSynthKarplusStrong string1;
AudioSynthKarplusStrong string2;
AudioSynthKarplusStrong string3;
AudioSynthKarplusStrong string4;
AudioSynthKarplusStrong string5;
AudioSynthKarplusStrong string6;
AudioMixer4 mixer1;
AudioMixer4 mixer2;
AudioOutputI2S i2s1;
AudioConnection patchCord1(string1, 0, mixer1, 0);
AudioConnection patchCord2(string2, 0, mixer1, 1);
AudioConnection patchCord3(string3, 0, mixer1, 2);
AudioConnection patchCord4(string4, 0, mixer1, 3);
AudioConnection patchCord5(mixer1, 0, mixer2, 0);
AudioConnection patchCord6(string5, 0, mixer2, 1);
AudioConnection patchCord7(string6, 0, mixer2, 2);
AudioConnection patchCord8(mixer2, 0, i2s1, 0);
AudioConnection patchCord9(mixer2, 0, i2s1, 1);

class GuitarSynthy {
 public:
  GuitarSynthy() { Debug("hello"); }
  const int finger_delay = 200;

  const float CmajorGuitar[6]{notes::C[3], notes::G[3],
                              notes::C[4], notes::E[4],
                              notes::G[4], notes::C[5]};  // C - E - G
  //   const float DminorGuitar[6] {notes::D[3], notes::A[3], notes::D[4],
  //   notes::F[4], notes::A[4], notes::D[5]};  // D - F - A
  const float CmajorInversionGuitar[6]{notes::E[3], notes::C[4], notes::E[4],
                                       notes::G[4], notes::C[5], notes::E[5]};
  //   const float FmajorGuitar[6] {notes::F[3], notes::C[4], notes::F[4],
  //   notes::A[4], notes::C[5], notes::F[5]};  // F - A - C
  const float AminorGuitar[6]{notes::A[3], notes::E[4], notes::A[4],
                              notes::C[5], notes::E[5], notes::A[5]};
  //   const float GmajorGuitar[6] {notes::G[3], notes::D[4], notes::G[4],
  //   notes::B[4], notes::D[5], notes::G[5]};  // G - B - D
  const float AminorInversionGuitar[6]{notes::E[3], notes::A[3], notes::C[4],
                                       notes::E[4], notes::A[4], notes::E[5]};
  const float *chord = CmajorGuitar;

  int8_t chordNum = 0;

  //   static constexpr float chords[6][4] {*notes::CmajorGuitar,
  //   *notes::DminorGuitar, *notes::FmajorGuitar, *notes::GmajorGuitar};

  void InitGuitarSynth() {
    mixer1.gain(0, 0.15);
    mixer1.gain(1, 0.15);
    mixer1.gain(2, 0.15);
    mixer1.gain(3, 0.15);
    mixer2.gain(1, 0.15);
    mixer2.gain(2, 0.15);
  }

  //   const void playString1() { string1.noteOn(chords[chordNum][0], 1); }

  //   const void playString2() { string2.noteOn(chords[chordNum][1], 1); }

  //   const void playString3() { string3.noteOn(chords[chordNum][2], 1); }

  //   const void playString4() { string4.noteOn(chords[chordNum][3], 1); }

  //   const void playString5() { string5.noteOn(chords[chordNum][4], 1); }

  //   const void playString6() { string6.noteOn(chords[chordNum][5], 1); }

  const void setChord(int8_t newChordNum) {
    chordNum = newChordNum;
    if (chordNum == 0) {
      chord = CmajorGuitar;
    } else if (chordNum == 1) {
      chord = CmajorInversionGuitar;
    } else if (chordNum == 2) {
      chord = AminorGuitar;
    } else if (chordNum == 3) {
      chord = AminorInversionGuitar;
    }
  }

  const void strumUp(float velocity = 1) {
    string1.noteOn(chord[0], velocity);
    delay(finger_delay);
    string2.noteOn(chord[1], velocity);
    delay(finger_delay);
    string3.noteOn(chord[2], velocity);
    delay(finger_delay);
    string4.noteOn(chord[3], velocity);
    delay(finger_delay);
    string5.noteOn(chord[4], velocity);
    delay(finger_delay);
    string6.noteOn(chord[5], velocity);
    delay(finger_delay);
  }

  const void strumDown(float velocity = 1) {
    string1.noteOn(chord[5], velocity);
    delay(finger_delay);
    string2.noteOn(chord[4], velocity);
    delay(finger_delay);
    string3.noteOn(chord[3], velocity);
    delay(finger_delay);
    string4.noteOn(chord[2], velocity);
    delay(finger_delay);
    string5.noteOn(chord[1], velocity);
    delay(finger_delay);
    string6.noteOn(chord[0], velocity);
    delay(finger_delay);
  }

  const void actionUp() { setChord(1); }
  const void actionDown() { setChord(0); }
  const void actionLeft() { setChord(2); }
  const void actionRight() { setChord(3); }
  const void actionA() { strumUp(); }
  const void actionB() { strumDown(); }
};

}  // namespace _guitar
}  // namespace audio
}  // namespace kss
