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

const Score GetFiddyScore() {
  ScoreBuilder fiddy{120, 2};

  // tom h
  fiddy.SetBeat(0, 1.5);
  fiddy.SetBeat(0, 4.75);
  fiddy.SetBeat(0, 5.5);
  fiddy.SetBeat(0, 6.75);
  fiddy.SetBeat(0, 7.5);
  fiddy.SetBeat(0, 8.75);
  
  // hh closed
  fiddy.SetBeat(1, 1);
  fiddy.SetBeat(1, 1.5);
  fiddy.SetBeat(1, 2);
  fiddy.SetBeat(1, 2.5);
  fiddy.SetBeat(1, 3);
  fiddy.SetBeat(1, 3.5);
  fiddy.SetBeat(1, 4);
  fiddy.SetBeat(1, 4.5);
  fiddy.SetBeat(1, 5);
  fiddy.SetBeat(1, 5.5);
  fiddy.SetBeat(1, 6);
  fiddy.SetBeat(1, 6.5);
  fiddy.SetBeat(1, 7);
  fiddy.SetBeat(1, 7.5);
  fiddy.SetBeat(1, 8);
  fiddy.SetBeat(1, 8.5);

  // crash
//   fiddy.SetBeat(2, 1);

  // clap
  fiddy.SetBeat(3, 2);
  fiddy.SetBeat(3, 4);
  fiddy.SetBeat(3, 6);
  fiddy.SetBeat(3, 8);

  // bd
  fiddy.SetBeat(4, 1.5);
  fiddy.SetBeat(4, 2.75);
  fiddy.SetBeat(4, 3.5);
  fiddy.SetBeat(4, 4.75);
  fiddy.SetBeat(4, 5.5);
  fiddy.SetBeat(4, 6.75);
  fiddy.SetBeat(4, 7.5);
  fiddy.SetBeat(4, 8.75);
  
  // sd
  fiddy.SetBeat(5, 2);
  fiddy.SetBeat(5, 4);
  fiddy.SetBeat(5, 6);
  fiddy.SetBeat(5, 8);

  return fiddy.GetScore();
}

Score Fiddy = GetFiddyScore();

}  // namespace audio
}  // namespace kss
