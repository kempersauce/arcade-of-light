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

const Score GetChachachaScore() {
  ScoreBuilder chachacha{120, 2};

  // tom h
  chachacha.SetBeat(0, 2.5);
  chachacha.SetBeat(0, 4);
  chachacha.SetBeat(0, 6);
  chachacha.SetBeat(0, 7);
  chachacha.SetBeat(0, 7.5);
  chachacha.SetBeat(0, 8);

  // hh closed
  chachacha.SetBeat(1, 1);
  chachacha.SetBeat(1, 1.5);
  chachacha.SetBeat(1, 2);
  chachacha.SetBeat(1, 3);
  chachacha.SetBeat(1, 3.5);
  chachacha.SetBeat(1, 4);
  chachacha.SetBeat(1, 5);
  chachacha.SetBeat(1, 5.5);
  chachacha.SetBeat(1, 6);
  chachacha.SetBeat(1, 7);
  chachacha.SetBeat(1, 7.5);
  chachacha.SetBeat(1, 8);

  // crash
  chachacha.SetBeat(2, 2);
  chachacha.SetBeat(2, 4);
  chachacha.SetBeat(2, 6);
  chachacha.SetBeat(2, 8);

  // clap
  chachacha.SetBeat(3, 7);
  chachacha.SetBeat(3, 7.5);
  chachacha.SetBeat(3, 8);

  // bd
  chachacha.SetBeat(4, 1);
  chachacha.SetBeat(4, 2);
  chachacha.SetBeat(4, 3);
  chachacha.SetBeat(4, 4);
  chachacha.SetBeat(4, 4.5);
  chachacha.SetBeat(4, 5);
  chachacha.SetBeat(4, 6);
  chachacha.SetBeat(4, 7);  
  chachacha.SetBeat(4, 8);

  // sd
  chachacha.SetBeat(5, 1);
  chachacha.SetBeat(5, 1.5);
  chachacha.SetBeat(5, 1.75);
  chachacha.SetBeat(5, 2);
  chachacha.SetBeat(5, 3);
  chachacha.SetBeat(5, 3.5);
  chachacha.SetBeat(5, 4.5);
  chachacha.SetBeat(5, 5);
  chachacha.SetBeat(5, 5.5);
  chachacha.SetBeat(5, 6.5);

  return chachacha.GetScore();
}

Score Chachacha = GetChachachaScore();

}  // namespace audio
}  // namespace kss
