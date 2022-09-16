#pragma once

namespace kss {
namespace audio {

// Reference: https://www.seventhstring.com/resources/notefrequencies.html
float C[] {16.35, 32.70, 65.41, 130.8, 261.6, 523.3, 1047, 2093, 4186};
float Cs[] {};
float D[] {};
float Eb[] {};
float E[] {};
float F[] {};
float Fs[] {};
float G[] {};
float Gs[] {};
float A[] {};
float Bb[] {};
float B[] {};

float C_Pentatonic[10] { C[3], D[3], F[3], G[3], A[3],
                       C[4], D[4], F[4], G[4], A[4]};

float Cs_HarmonicMinor[21] {Cs[3], Eb[3], E[3], Fs[3], Gs[3], A[3], C[3],
                  Cs[4], Eb[4], E[4], Fs[4], Gs[4], A[4], C[4],
                  Cs[5], Eb[5], E[5], Fs[5], Gs[5], A[5], C[5],};

}
}