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

const Score GetMickeyScore() {
  ScoreBuilder mickey{120, 2};

  // tom h
  mickey.SetBeat(0, 7.5);
  mickey.SetBeat(0, 8);

  // hh closed
  mickey.SetBeat(1, 1);
  mickey.SetBeat(1, 2);
//   mickey.SetBeat(1, 3);
  mickey.SetBeat(1, 4);
  mickey.SetBeat(1, 5);
  mickey.SetBeat(1, 6);
//   mickey.SetBeat(1, 7);
  mickey.SetBeat(1, 8);
  mickey.SetBeat(1, 8.5);

  // crash
//   mickey.SetBeat(2, 1);

  // clap
  mickey.SetBeat(3, 8);
  mickey.SetBeat(3, 8.5);

  // bd
  mickey.SetBeat(4, 1);
  mickey.SetBeat(4, 2.5);
  mickey.SetBeat(4, 3.5);
  mickey.SetBeat(4, 5);
  mickey.SetBeat(4, 6.5);
  mickey.SetBeat(4, 7.5);
  mickey.SetBeat(4, 8);

  // sd
  mickey.SetBeat(5, 2);
  mickey.SetBeat(5, 4);
  mickey.SetBeat(5, 6);
  mickey.SetBeat(5, 7.5);
  mickey.SetBeat(5, 8);

  return mickey.GetScore();
}

Score Mickey = GetMickeyScore();

}  // namespace audio
}  // namespace kss
