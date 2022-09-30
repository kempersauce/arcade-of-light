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

const Score GetCloserScore() {
  ScoreBuilder closer{60, 2};

  // tom h
//   closer.SetBeat(0, 7.5);
//   closer.SetBeat(0, 8);

  // hh closed
  closer.SetBeat(1, 1);
  closer.SetBeat(1, 1.25);
  closer.SetBeat(1, 1.5);
  closer.SetBeat(1, 1.75);

  // crash
//   closer.SetBeat(2, 1);

  // clap
  closer.SetBeat(3, 2);
  closer.SetBeat(3, 4);
  closer.SetBeat(3, 6);
  closer.SetBeat(3, 8);

  // bd
  closer.SetBeat(4, 1);
  closer.SetBeat(4, 2);
  closer.SetBeat(4, 3);
  closer.SetBeat(4, 4);
  closer.SetBeat(4, 5);
  closer.SetBeat(4, 6);
  closer.SetBeat(4, 7);
  closer.SetBeat(4, 8);

  // sd
  closer.SetBeat(5, 2);
//   closer.SetBeatEveryMeasure(5, 4);
  closer.SetBeat(5, 6);
//   closer.SetBeatEveryMeasure(5, 8);

  return closer.GetScore();
}

Score Closer = GetCloserScore();

}  // namespace audio
}  // namespace kss
