#pragma once

#include "audio/beat_patterns/constants.h"  // for kChannel*
#include "audio/score.h"                    // for Score

namespace kss {
namespace audio {
namespace beats {

const Score GetMickeyScore() {
  ScoreBuilder mickey{120, 2};

  // tom h
  mickey.SetBeat(kChannelTom, 7.5);
  mickey.SetBeat(kChannelTom, 8);

  // hh closed
  mickey.SetBeat(kChannelHHClosed, 1);
  mickey.SetBeat(kChannelHHClosed, 2);
  //   mickey.SetBeat(kChannelHHClosed, 3);
  mickey.SetBeat(kChannelHHClosed, 4);
  mickey.SetBeat(kChannelHHClosed, 5);
  mickey.SetBeat(kChannelHHClosed, 6);
  //   mickey.SetBeat(kChannelHHClosed, 7);
  mickey.SetBeat(kChannelHHClosed, 8);
  mickey.SetBeat(kChannelHHClosed, 8.5);

  // crash
  //   mickey.SetBeat(kChannelCrash, 1);

  // clap
  mickey.SetBeat(kChannelClap, 8);
  mickey.SetBeat(kChannelClap, 8.5);

  // bd
  mickey.SetBeat(kChannelBassDrum, 1);
  mickey.SetBeat(kChannelBassDrum, 2.5);
  mickey.SetBeat(kChannelBassDrum, 3.5);
  mickey.SetBeat(kChannelBassDrum, 5);
  mickey.SetBeat(kChannelBassDrum, 6.5);
  mickey.SetBeat(kChannelBassDrum, 7.5);
  mickey.SetBeat(kChannelBassDrum, 8);

  // sd
  mickey.SetBeat(kChannelSnare, 2);
  mickey.SetBeat(kChannelSnare, 4);
  mickey.SetBeat(kChannelSnare, 6);
  mickey.SetBeat(kChannelSnare, 7.5);
  mickey.SetBeat(kChannelSnare, 8);

  return mickey.GetScore();
}

Score Mickey = GetMickeyScore();

}  // namespace beats
}  // namespace audio
}  // namespace kss
