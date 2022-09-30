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

const Score GetFlorianScore() {
  ScoreBuilder florian{120, 2};

  // tom h
//   florian.SetBeat(0, 7.5);
//   florian.SetBeat(0, 8);

  // hh closed
  florian.SetBeat(1, 1);
  florian.SetBeat(1, 1.5);
  florian.SetBeat(1, 1.75);
  florian.SetBeat(1, 2);
  florian.SetBeat(1, 2.5);
  florian.SetBeat(1, 2.75);
  florian.SetBeat(1, 3.5);
  florian.SetBeat(1, 3.75);
  florian.SetBeat(1, 4);
  florian.SetBeat(1, 4.5);
  florian.SetBeat(1, 4.75);
  florian.SetBeat(1, 5);
  florian.SetBeat(1, 5.5);
  florian.SetBeat(1, 5.75);
  florian.SetBeat(1, 6);
  florian.SetBeat(1, 6.5);
  florian.SetBeat(1, 6.75);
  florian.SetBeat(1, 7.5);
  florian.SetBeat(1, 7.75);
  florian.SetBeat(1, 8);
  florian.SetBeat(1, 8.5);
  florian.SetBeat(1, 8.75);


  // crash
//   florian.SetBeat(2, 1);

  // clap
  florian.SetBeat(3, 4);
  florian.SetBeat(3, 8);

  // bd
  florian.SetBeat(4, 1);
  florian.SetBeat(4, 5);
  florian.SetBeat(4, 8.5);

  // sd
  florian.SetBeat(5, 2);
  florian.SetBeat(5, 4);
  florian.SetBeat(5, 6);
  florian.SetBeat(5, 8);

  return florian.GetScore();
}

Score Florian = GetFlorianScore();

}  // namespace audio
}  // namespace kss
