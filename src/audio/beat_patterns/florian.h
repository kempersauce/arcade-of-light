#pragma once

#include "audio/beat_patterns/constants.h"  // for kChannel*
#include "audio/score.h"                    // for Score

namespace kss {
namespace audio {
namespace beats {

const Score GetFlorianScore() {
  ScoreBuilder florian{120, 2};

  // tom h
  //   florian.SetBeat(kChannelTom, 7.5);
  //   florian.SetBeat(kChannelTom, 8);

  // hh closed
  florian.SetBeat(kChannelHHClosed, 1);
  florian.SetBeat(kChannelHHClosed, 1.5);
  florian.SetBeat(kChannelHHClosed, 1.75);
  florian.SetBeat(kChannelHHClosed, 2);
  florian.SetBeat(kChannelHHClosed, 2.5);
  florian.SetBeat(kChannelHHClosed, 2.75);
  florian.SetBeat(kChannelHHClosed, 3.5);
  florian.SetBeat(kChannelHHClosed, 3.75);
  florian.SetBeat(kChannelHHClosed, 4);
  florian.SetBeat(kChannelHHClosed, 4.5);
  florian.SetBeat(kChannelHHClosed, 4.75);
  florian.SetBeat(kChannelHHClosed, 5);
  florian.SetBeat(kChannelHHClosed, 5.5);
  florian.SetBeat(kChannelHHClosed, 5.75);
  florian.SetBeat(kChannelHHClosed, 6);
  florian.SetBeat(kChannelHHClosed, 6.5);
  florian.SetBeat(kChannelHHClosed, 6.75);
  florian.SetBeat(kChannelHHClosed, 7.5);
  florian.SetBeat(kChannelHHClosed, 7.75);
  florian.SetBeat(kChannelHHClosed, 8);
  florian.SetBeat(kChannelHHClosed, 8.5);
  florian.SetBeat(kChannelHHClosed, 8.75);

  // crash
  //   florian.SetBeat(kChannelCrash, 1);

  // clap
  florian.SetBeat(kChannelClap, 4);
  florian.SetBeat(kChannelClap, 8);

  // bd
  florian.SetBeat(kChannelBassDrum, 1);
  florian.SetBeat(kChannelBassDrum, 5);
  florian.SetBeat(kChannelBassDrum, 8.5);

  // sd
  florian.SetBeat(kChannelSnare, 2);
  florian.SetBeat(kChannelSnare, 4);
  florian.SetBeat(kChannelSnare, 6);
  florian.SetBeat(kChannelSnare, 8);

  return florian.GetScore();
}

Score Florian = GetFlorianScore();

}  // namespace beats
}  // namespace audio
}  // namespace kss
