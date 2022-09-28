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

const Score GetTwistScore() {
  ScoreBuilder twist{120, 1};

  // tom h
  twist.SetBeat(0, 4);
  twist.SetBeat(0, 4.5);

  // hh closed
  twist.SetBeat(1, 1);
  twist.SetBeat(1, 1.5);
  twist.SetBeat(1, 2);
  twist.SetBeat(1, 2.5);
  twist.SetBeat(1, 3);
  twist.SetBeat(1, 3.5);
  twist.SetBeat(1, 4);
  twist.SetBeat(1, 4.5);

  // crash
  twist.SetBeat(2, 1);
  twist.SetBeat(2, 2);
  twist.SetBeat(2, 3);
  twist.SetBeat(2, 4);

  // clap
  twist.SetBeat(3, 2);
  twist.SetBeat(3, 4);

  // bd
  twist.SetBeat(4, 1);
  twist.SetBeat(4, 2);
  twist.SetBeat(4, 3);
  twist.SetBeat(4, 4);

  // sd
  twist.SetBeat(5, 2);

  return twist.GetScore();
}

Score Twist = GetTwistScore();

}  // namespace audio
}  // namespace kss
