#pragma once

namespace kss {
namespace audio {
namespace notes {

// Reference: https://www.seventhstring.com/resources/notefrequencies.html
// clang-format off
constexpr float C[9]{16.35, 32.70, 65.41, 130.8, 261.6, 523.3, 1047, 2093, 4186};
constexpr float Cs[9]{17.32, 34.65, 69.30, 138.6, 277.2, 554.4, 1109, 2217, 4435};
constexpr float D[9]{18.35, 36.71, 73.42, 146.8, 293.7, 587.3, 1175, 2349, 4699};
constexpr float Eb[9]{19.45, 38.89, 77.78, 155.6, 311.1, 622.3, 1245, 2489, 4978};
constexpr float E[9]{20.60, 41.20, 82.41, 164.8, 329.6, 659.3, 1319, 2637, 5274};
constexpr float F[9]{21.83, 43.65, 87.31, 174.6, 349.2, 698.5, 1397, 2794, 5588};
constexpr float Fs[9]{23.12, 46.25, 92.50, 185.0, 370.0, 740.0, 1480, 2960, 5920};
constexpr float G[9]{24.50, 49.00, 98.00, 196.0, 392.0, 784.0, 1568, 3136, 6272};
constexpr float Gs[9]{25.96, 51.91, 103.8, 207.7, 415.3, 830.6, 1661, 3322, 6645};
constexpr float A[9]{27.50, 55.00, 110.0, 220.0, 440.0, 880.0, 1760, 3520, 7040};
constexpr float Bb[9]{29.14, 58.27, 116.5, 233.1, 466.2, 932.3, 1865, 3729, 7459};
constexpr float B[9]{30.87, 61.74, 123.5, 246.9, 493.9, 987.8, 1976, 3951, 7902};

float C_Pentatonic3[10] { C[3], D[3], F[3], G[3], A[3],
                          C[4], D[4], F[4], G[4], A[4]};

float C_Pentatonic4[10] { C[4], D[4], F[4], G[4], A[4],
                          C[5], D[5], F[5], G[5], A[5]};

float Cs_HarmonicMinor[21] {Cs[3], Eb[3], E[3], Fs[3], Gs[3], A[3], C[3],
                            Cs[4], Eb[4], E[4], Fs[4], Gs[4], A[4], C[4],
                            Cs[5], Eb[5], E[5], Fs[5], Gs[5], A[5], C[5],};

constexpr float all_notes[9][12]{*C, *Cs, *D, *Eb, *E, *F, *Fs, *G, *Gs, *A, *Bb, *B};
// clang-format on


}  // namespace notes
}  // namespace audio
}  // namespace kss
