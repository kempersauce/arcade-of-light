#pragma once

#include "audio/beat_patterns/constants.h"  // for kChannel*
#include "audio/score.h"                    // for Score

namespace kss {
namespace audio {
namespace beats {

const Score GetFiddyScore() {
  ScoreBuilder fiddy{120, 2};

  // tom h
  fiddy.SetBeat(kChannelTom, 1.5);
  fiddy.SetBeat(kChannelTom, 4.75);
  fiddy.SetBeat(kChannelTom, 5.5);
  fiddy.SetBeat(kChannelTom, 6.75);
  fiddy.SetBeat(kChannelTom, 7.5);
  fiddy.SetBeat(kChannelTom, 8.75);

  // hh closed
  fiddy.SetBeat(kChannelHHClosed, 1);
  fiddy.SetBeat(kChannelHHClosed, 1.5);
  fiddy.SetBeat(kChannelHHClosed, 2);
  fiddy.SetBeat(kChannelHHClosed, 2.5);
  fiddy.SetBeat(kChannelHHClosed, 3);
  fiddy.SetBeat(kChannelHHClosed, 3.5);
  fiddy.SetBeat(kChannelHHClosed, 4);
  fiddy.SetBeat(kChannelHHClosed, 4.5);
  fiddy.SetBeat(kChannelHHClosed, 5);
  fiddy.SetBeat(kChannelHHClosed, 5.5);
  fiddy.SetBeat(kChannelHHClosed, 6);
  fiddy.SetBeat(kChannelHHClosed, 6.5);
  fiddy.SetBeat(kChannelHHClosed, 7);
  fiddy.SetBeat(kChannelHHClosed, 7.5);
  fiddy.SetBeat(kChannelHHClosed, 8);
  fiddy.SetBeat(kChannelHHClosed, 8.5);

  // crash
  //   fiddy.SetBeat(kChannelCrash, 1);

  // clap
  fiddy.SetBeat(kChannelClap, 2);
  fiddy.SetBeat(kChannelClap, 4);
  fiddy.SetBeat(kChannelClap, 6);
  fiddy.SetBeat(kChannelClap, 8);

  // bd
  fiddy.SetBeat(kChannelBassDrum, 1.5);
  fiddy.SetBeat(kChannelBassDrum, 2.75);
  fiddy.SetBeat(kChannelBassDrum, 3.5);
  fiddy.SetBeat(kChannelBassDrum, 4.75);
  fiddy.SetBeat(kChannelBassDrum, 5.5);
  fiddy.SetBeat(kChannelBassDrum, 6.75);
  fiddy.SetBeat(kChannelBassDrum, 7.5);
  fiddy.SetBeat(kChannelBassDrum, 8.75);

  // sd
  fiddy.SetBeat(kChannelSnare, 2);
  fiddy.SetBeat(kChannelSnare, 4);
  fiddy.SetBeat(kChannelSnare, 6);
  fiddy.SetBeat(kChannelSnare, 8);

  return fiddy.GetScore();
}

Score Fiddy = GetFiddyScore();

}  // namespace beats
}  // namespace audio
}  // namespace kss
