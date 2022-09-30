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

const Score GetShuffleScore() {
  ScoreBuilder shuffle{60, 1};

  // tom h
//   shuffle.SetBeat(0, 5);
//   shuffle.SetBeat(0, 5.5);
//   shuffle.SetBeat(0, 6);
//   shuffle.SetBeat(0, 6.5);

  // hh closed
  shuffle.SetBeat(1, 1);
  shuffle.SetBeat(1, 2);
  shuffle.SetBeat(1, 2.7);
  shuffle.SetBeat(1, 3);
  shuffle.SetBeat(1, 4);
  shuffle.SetBeat(1, 4.7);

  // crash
//   shuffle.SetBeat(2, 7.75);

  // clap
  shuffle.SetBeat(3, 2);
  shuffle.SetBeat(3, 2.69);
  shuffle.SetBeat(3, 4);

  // bd
  shuffle.SetBeat(4, 1);
  shuffle.SetBeat(4, 2);
  shuffle.SetBeat(4, 2.75);
  shuffle.SetBeat(4, 3);
  shuffle.SetBeat(4, 4);
  shuffle.SetBeat(4, 4.75);

  // sd
  shuffle.SetBeat(5, 2);
  shuffle.SetBeat(5, 4);

  return shuffle.GetScore();
}

Score Shuffle = GetShuffleScore();

}  // namespace audio
}  // namespace kss
