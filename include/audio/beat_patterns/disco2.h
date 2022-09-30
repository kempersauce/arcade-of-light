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

const Score GetDisco2Score() {
  ScoreBuilder disco2{120, 1};

  // tom h
  disco2.SetBeat(0, 2);
  disco2.SetBeat(0, 4);

  // hh closed
  disco2.SetBeat(1, 1);
  disco2.SetBeat(1, 1.25);
  disco2.SetBeat(1, 1.5);
  disco2.SetBeat(1, 1.75);
  disco2.SetBeat(1, 2);
  disco2.SetBeat(1, 2.25);
  disco2.SetBeat(1, 2.5);
  disco2.SetBeat(1, 2.75);
  disco2.SetBeat(1, 3);
  disco2.SetBeat(1, 3.25);
  disco2.SetBeat(1, 3.5);
  disco2.SetBeat(1, 3.75);
  disco2.SetBeat(1, 4);
  disco2.SetBeat(1, 4.25);
  disco2.SetBeat(1, 4.5);
  disco2.SetBeat(1, 4.75);

  // crash
  disco2.SetBeat(2, 1);

  // clap
  disco2.SetBeat(3, 1);
  disco2.SetBeat(3, 4);
  disco2.SetBeat(3, 4.5);

  // bd
  disco2.SetBeat(4, 1);
  disco2.SetBeat(4, 2);
  disco2.SetBeat(4, 2.25);
  disco2.SetBeat(4, 3);
  disco2.SetBeat(4, 3.75);
  disco2.SetBeat(4, 4);

  // sd
  disco2.SetBeat(5, 2);
  disco2.SetBeat(5, 4);
  disco2.SetBeat(5, 4.5);
  disco2.SetBeat(5, 4.75);

  return disco2.GetScore();
}

Score Disco2 = GetDisco2Score();

}  // namespace audio
}  // namespace kss
