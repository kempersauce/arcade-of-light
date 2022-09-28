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

const Score GetCongaScore() {
  ScoreBuilder conga{120, 2};

  // tom h
  conga.SetBeat(0, 5);
  conga.SetBeat(0, 5.5);
  conga.SetBeat(0, 6);
  conga.SetBeat(0, 6.5);

  // hh closed
  conga.SetBeat(1, 2);
  conga.SetBeat(1, 4);
  conga.SetBeat(1, 5);
  conga.SetBeat(1, 5.5);
  conga.SetBeat(1, 6);
  conga.SetBeat(1, 6.5);
  conga.SetBeat(1, 7);

  // crash
  conga.SetBeat(2, 7.75);

  // clap
  conga.SetBeat(3, 1);
  conga.SetBeat(3, 2);
  conga.SetBeat(3, 3);
  conga.SetBeat(3, 4);
  conga.SetBeat(3, 5);
  conga.SetBeat(3, 6);
  conga.SetBeat(3, 7);
  conga.SetBeat(3, 7.75);

  // bd
  conga.SetBeat(4, 1);
  conga.SetBeat(4, 2);
  conga.SetBeat(4, 3);
  conga.SetBeat(4, 3.75);
  conga.SetBeat(4, 4);
  conga.SetBeat(4, 5);
  conga.SetBeat(4, 5.75);
  conga.SetBeat(4, 6);
  conga.SetBeat(4, 6.75);
  conga.SetBeat(4, 7);
  conga.SetBeat(4, 7.75);

  // sd
  conga.SetBeat(5, 1);
  conga.SetBeat(5, 2);
  conga.SetBeat(5, 3);
  conga.SetBeat(5, 4.75);
  conga.SetBeat(5, 5);
  conga.SetBeat(5, 6);
  conga.SetBeat(5, 7);
  conga.SetBeat(5, 7.75);
  conga.SetBeat(5, 8.75);

  return conga.GetScore();
}

Score Conga = GetCongaScore();

}  // namespace audio
}  // namespace kss
