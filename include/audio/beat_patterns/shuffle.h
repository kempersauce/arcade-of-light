#pragma once

#include "audio/beat_patterns/constants.h"  // for kChannel*
#include "audio/score.h"                    // for Score

namespace kss {
namespace audio {
namespace beats {

const Score GetShuffleScore() {
  ScoreBuilder shuffle{60, 1};

  // tom h
  //   shuffle.SetBeat(kChannelTom, 5);
  //   shuffle.SetBeat(kChannelTom, 5.5);
  //   shuffle.SetBeat(kChannelTom, 6);
  //   shuffle.SetBeat(kChannelTom, 6.5);

  // hh closed
  shuffle.SetBeat(kChannelHHClosed, 1);
  shuffle.SetBeat(kChannelHHClosed, 2);
  shuffle.SetBeat(kChannelHHClosed, 2.7);
  shuffle.SetBeat(kChannelHHClosed, 3);
  shuffle.SetBeat(kChannelHHClosed, 4);
  shuffle.SetBeat(kChannelHHClosed, 4.7);

  // crash
  //   shuffle.SetBeat(kChannelCrash, 7.75);

  // clap
  shuffle.SetBeat(kChannelClap, 2);
  shuffle.SetBeat(kChannelClap, 2.69);
  shuffle.SetBeat(kChannelClap, 4);

  // bd
  shuffle.SetBeat(kChannelBassDrum, 1);
  shuffle.SetBeat(kChannelBassDrum, 2);
  shuffle.SetBeat(kChannelBassDrum, 2.75);
  shuffle.SetBeat(kChannelBassDrum, 3);
  shuffle.SetBeat(kChannelBassDrum, 4);
  shuffle.SetBeat(kChannelBassDrum, 4.75);

  // sd
  shuffle.SetBeat(kChannelSnare, 2);
  shuffle.SetBeat(kChannelSnare, 4);

  return shuffle.GetScore();
}

Score Shuffle = GetShuffleScore();

}  // namespace beats
}  // namespace audio
}  // namespace kss
