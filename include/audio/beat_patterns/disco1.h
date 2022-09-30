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

const Score GetDisco1Score() {
  ScoreBuilder disco1{120, 1};

  // tom h
  disco1.SetBeat(0, 1);
  disco1.SetBeat(0, 4.5);
  disco1.SetBeat(0, 4.75);

  // hh closed
  disco1.SetBeat(1, 1);
  disco1.SetBeat(1, 1.25);
  disco1.SetBeat(1, 1.5);
  disco1.SetBeat(1, 1.75);
  disco1.SetBeat(1, 2);
  disco1.SetBeat(1, 2.25);
  disco1.SetBeat(1, 2.5);
  disco1.SetBeat(1, 2.75);
  disco1.SetBeat(1, 3);
  disco1.SetBeat(1, 3.25);
  disco1.SetBeat(1, 3.5);
  disco1.SetBeat(1, 3.75);
  disco1.SetBeat(1, 4);
  disco1.SetBeat(1, 4.25);
  disco1.SetBeat(1, 4.5);
  disco1.SetBeat(1, 4.75);

  // crash
  disco1.SetBeat(2, 1);
  disco1.SetBeat(2, 2);
  disco1.SetBeat(2, 3);
  disco1.SetBeat(2, 4);

  // clap
  disco1.SetBeat(3, 2.5);
  disco1.SetBeat(3, 2.75);
  disco1.SetBeat(3, 3);

  // bd
  disco1.SetBeat(4, 1);
  disco1.SetBeat(4, 1.75);
  disco1.SetBeat(4, 2);
  disco1.SetBeat(4, 2.5);
  disco1.SetBeat(4, 3);
  disco1.SetBeat(4, 3.75);
  disco1.SetBeat(4, 4);
  disco1.SetBeat(4, 4.5);
  
  // sd
  disco1.SetBeat(5, 2);
  disco1.SetBeat(5, 4);

  return disco1.GetScore();
}

Score Disco1 = GetDisco1Score();

}  // namespace audio
}  // namespace kss
