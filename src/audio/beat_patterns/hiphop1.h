#pragma once

#include "audio/beat_patterns/constants.h"  // for kChannel*
#include "audio/score.h"                    // for Score

namespace kss {
namespace audio {
namespace beats {

const Score GetHiphop1Score() {
  ScoreBuilder hiphop1{120, 2};

  // tom h
  hiphop1.SetBeat(kChannelTom, 2);
  hiphop1.SetBeat(kChannelTom, 6);

  // hh closed
  hiphop1.SetBeat(kChannelHHClosed, 1);
  hiphop1.SetBeat(kChannelHHClosed, 1.5);
  hiphop1.SetBeat(kChannelHHClosed, 2);
  hiphop1.SetBeat(kChannelHHClosed, 2.5);
  hiphop1.SetBeat(kChannelHHClosed, 3);
  hiphop1.SetBeat(kChannelHHClosed, 3.5);
  hiphop1.SetBeat(kChannelHHClosed, 4);
  hiphop1.SetBeat(kChannelHHClosed, 4.5);
  hiphop1.SetBeat(kChannelHHClosed, 5);
  hiphop1.SetBeat(kChannelHHClosed, 5.5);
  hiphop1.SetBeat(kChannelHHClosed, 6);
  hiphop1.SetBeat(kChannelHHClosed, 6.5);
  hiphop1.SetBeat(kChannelHHClosed, 7);
  hiphop1.SetBeat(kChannelHHClosed, 7.5);
  hiphop1.SetBeat(kChannelHHClosed, 8);
  hiphop1.SetBeat(kChannelHHClosed, 8.5);

  // crash
  //   hiphop1.SetBeat(kChannelCrash, 1);

  // clap
  hiphop1.SetBeat(kChannelClap, 8);
  hiphop1.SetBeat(kChannelClap, 8.5);

  // bd
  hiphop1.SetBeat(kChannelBassDrum, 1);
  hiphop1.SetBeat(kChannelBassDrum, 2.75);
  hiphop1.SetBeat(kChannelBassDrum, 3.25);
  hiphop1.SetBeat(kChannelBassDrum, 3.5);
  hiphop1.SetBeat(kChannelBassDrum, 4.5);
  hiphop1.SetBeat(kChannelBassDrum, 5);
  hiphop1.SetBeat(kChannelBassDrum, 6.75);
  hiphop1.SetBeat(kChannelBassDrum, 7.25);
  hiphop1.SetBeat(kChannelBassDrum, 7.5);

  // sd
  hiphop1.SetBeat(kChannelSnare, 2);
  hiphop1.SetBeat(kChannelSnare, 4);
  hiphop1.SetBeat(kChannelSnare, 6);
  hiphop1.SetBeat(kChannelSnare, 8);

  return hiphop1.GetScore();
}

Score Hiphop1 = GetHiphop1Score();

}  // namespace beats
}  // namespace audio
}  // namespace kss
