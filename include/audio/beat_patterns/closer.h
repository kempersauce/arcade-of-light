#pragma once

#include "audio/beat_patterns/constants.h"  // for kChannel*
#include "audio/score.h"                    // for Score

namespace kss {
namespace audio {
namespace beats {

const Score GetCloserScore() {
  ScoreBuilder closer{60, 2};

  // tom h
  //   closer.SetBeat(kChannelTom, 7.5);
  //   closer.SetBeat(kChannelTom, 8);

  // hh closed
  closer.SetBeat(kChannelHHClosed, 1);
  closer.SetBeat(kChannelHHClosed, 1.25);
  closer.SetBeat(kChannelHHClosed, 1.5);
  closer.SetBeat(kChannelHHClosed, 1.75);

  // crash
  //   closer.SetBeat(kChannelCrash, 1);

  // clap
  closer.SetBeat(kChannelClap, 4);
  closer.SetBeat(kChannelClap, 8);

  // bd
  closer.SetBeat(kChannelBassDrum, 1);
  closer.SetBeat(kChannelBassDrum, 2);
  closer.SetBeat(kChannelBassDrum, 3);
  closer.SetBeat(kChannelBassDrum, 4);
  closer.SetBeat(kChannelBassDrum, 5);
  closer.SetBeat(kChannelBassDrum, 6);
  closer.SetBeat(kChannelBassDrum, 7);
  closer.SetBeat(kChannelBassDrum, 8);

  // sd
  closer.SetBeat(kChannelSnare, 2);
  closer.SetBeat(kChannelSnare, 4);
  closer.SetBeat(kChannelSnare, 6);
  closer.SetBeat(kChannelSnare, 8);

  return closer.GetScore();
}

Score Closer = GetCloserScore();

}  // namespace beats
}  // namespace audio
}  // namespace kss
