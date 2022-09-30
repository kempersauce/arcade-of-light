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

const Score GetProcessionScore() {
  ScoreBuilder procession{120, 2};

  // tom h
  procession.SetBeat(0, 8);
  procession.SetBeat(0, 8.33);
  procession.SetBeat(0, 8.67);

  // hh closed
  procession.SetBeat(1, 1);
  procession.SetBeat(1, 2.5);
  procession.SetBeat(1, 2.75);
  procession.SetBeat(1, 3);
  procession.SetBeat(1, 3.5);
  procession.SetBeat(1, 4.5);
  procession.SetBeat(1, 5);
  procession.SetBeat(1, 7);
  procession.SetBeat(1, 7.15);
  procession.SetBeat(1, 7.25);
  procession.SetBeat(1, 7.35);
  procession.SetBeat(1, 7.45);
  procession.SetBeat(1, 7.55);
  procession.SetBeat(1, 7.65);
  procession.SetBeat(1, 7.75);
  procession.SetBeat(1, 7.85);
  procession.SetBeat(1, 7.95);
  procession.SetBeat(1, 8);
  procession.SetBeat(1, 8.5);
  procession.SetBeat(1, 8.75);


  // crash
  procession.SetBeat(2, 1);

  // clap
  procession.SetBeat(3, 1);
  procession.SetBeat(3, 2.5);
  procession.SetBeat(3, 2.75);
  procession.SetBeat(3, 3);
  procession.SetBeat(3, 3.5);
  procession.SetBeat(3, 4.5);
  procession.SetBeat(3, 5);
  procession.SetBeat(3, 7);
  procession.SetBeat(3, 7.25);
  procession.SetBeat(3, 7.5);
  procession.SetBeat(3, 7.75);
  procession.SetBeat(3, 8);
  procession.SetBeat(3, 8.5);
  

  // bd
  procession.SetBeat(4, 1);
  procession.SetBeat(4, 3);
  procession.SetBeat(4, 5);

  // sd
  procession.SetBeat(5, 2.12);
  procession.SetBeat(5, 2.43);
  procession.SetBeat(5, 2.74);
  procession.SetBeat(5, 3);
  procession.SetBeat(5, 3.5);
  procession.SetBeat(5, 8);
  procession.SetBeat(5, 8.3);
  procession.SetBeat(5, 8.6);


  return procession.GetScore();
}

Score Procession = GetProcessionScore();

}  // namespace audio
}  // namespace kss
