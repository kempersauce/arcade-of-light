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

const Score GetReggaeScore() {
  ScoreBuilder reggae{120, 2};

  // tom h
  reggae.SetBeat(0, 7.5);
  reggae.SetBeat(0, 8);

  // hh closed
  reggae.SetBeat(1, 1);
  reggae.SetBeat(1, 2);
  reggae.SetBeat(1, 3);
  reggae.SetBeat(1, 4);
  reggae.SetBeat(1, 5);
  reggae.SetBeat(1, 6);
  reggae.SetBeat(1, 7);
  reggae.SetBeat(1, 8);

  // crash
  reggae.SetBeat(2, 1);

  // clap
  reggae.SetBeat(3, 8);
  reggae.SetBeat(3, 8.5);

  // bd
  reggae.SetBeat(4, 1);
  reggae.SetBeat(4, 3);
  reggae.SetBeat(4, 5);
  reggae.SetBeat(4, 7);

  // sd
  reggae.SetBeatEveryMeasure(5, 3);

  return reggae.GetScore();
}

Score Reggae = GetReggaeScore();

}  // namespace audio
}  // namespace kss
