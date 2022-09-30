#pragma once

#include "audio/score.h"

// channels:
// 0 - tom h
// 1 - hh closed
// 2 - crash
// 3 - clap
// 4 - bd
// 5 - sd

namespace kss {
namespace audio {

const Score GetHiphop1Score() {
  ScoreBuilder hiphop1{120, 2};

  // tom h
  hiphop1.SetBeat(0, 2);
  hiphop1.SetBeat(0, 6);

  // hh closed
  hiphop1.SetBeat(1, 1);
  hiphop1.SetBeat(1, 1.5);
  hiphop1.SetBeat(1, 2);
  hiphop1.SetBeat(1, 2.5);
  hiphop1.SetBeat(1, 3);
  hiphop1.SetBeat(1, 3.5);
  hiphop1.SetBeat(1, 4);
  hiphop1.SetBeat(1, 4.5);
  hiphop1.SetBeat(1, 5);
  hiphop1.SetBeat(1, 5.5);
  hiphop1.SetBeat(1, 6);
  hiphop1.SetBeat(1, 6.5);
  hiphop1.SetBeat(1, 7);
  hiphop1.SetBeat(1, 7.5);
  hiphop1.SetBeat(1, 8);
  hiphop1.SetBeat(1, 8.5);

  // crash
//   hiphop1.SetBeat(2, 1);

  // clap
  hiphop1.SetBeat(3, 8);
  hiphop1.SetBeat(3, 8.5);

  // bd
  hiphop1.SetBeat(4, 1);
  hiphop1.SetBeat(4, 2.75);
  hiphop1.SetBeat(4, 3.25);
  hiphop1.SetBeat(4, 3.5);
  hiphop1.SetBeat(4, 4.5);
  hiphop1.SetBeat(4, 5);
  hiphop1.SetBeat(4, 6.75);
  hiphop1.SetBeat(4, 7.25);
  hiphop1.SetBeat(4, 7.5);

  // sd
  hiphop1.SetBeat(5, 2);
  hiphop1.SetBeat(5, 4);
  hiphop1.SetBeat(5, 6);
  hiphop1.SetBeat(5, 8);

  return hiphop1.GetScore();
}

Score Hiphop1 = GetHiphop1Score();

}  // namespace audio
}  // namespace kss
