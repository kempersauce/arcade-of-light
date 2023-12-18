#pragma once

#include "audio/beat_patterns/constants.h"  // for kChannel*
#include "audio/score.h"                    // for Score

namespace kss {
namespace audio {
namespace beats {

const Score GetCongaScore() {
  ScoreBuilder conga{120, 2};

  // tom h
  conga.SetBeat(kChannelTom, 5);
  conga.SetBeat(kChannelTom, 5.5);
  conga.SetBeat(kChannelTom, 6);
  conga.SetBeat(kChannelTom, 6.5);

  // hh closed
  conga.SetBeat(kChannelHHClosed, 2);
  conga.SetBeat(kChannelHHClosed, 4);
  conga.SetBeat(kChannelHHClosed, 5);
  conga.SetBeat(kChannelHHClosed, 5.5);
  conga.SetBeat(kChannelHHClosed, 6);
  conga.SetBeat(kChannelHHClosed, 6.5);
  conga.SetBeat(kChannelHHClosed, 7);

  // crash
  conga.SetBeat(kChannelCrash, 7.75);

  // clap
  conga.SetBeat(kChannelClap, 1);
  conga.SetBeat(kChannelClap, 2);
  conga.SetBeat(kChannelClap, 3);
  conga.SetBeat(kChannelClap, 4);
  conga.SetBeat(kChannelClap, 5);
  conga.SetBeat(kChannelClap, 6);
  conga.SetBeat(kChannelClap, 7);
  conga.SetBeat(kChannelClap, 7.75);

  // bd
  conga.SetBeat(kChannelBassDrum, 1);
  conga.SetBeat(kChannelBassDrum, 2);
  conga.SetBeat(kChannelBassDrum, 3);
  conga.SetBeat(kChannelBassDrum, 3.75);
  conga.SetBeat(kChannelBassDrum, 4);
  conga.SetBeat(kChannelBassDrum, 5);
  conga.SetBeat(kChannelBassDrum, 5.75);
  conga.SetBeat(kChannelBassDrum, 6);
  conga.SetBeat(kChannelBassDrum, 6.75);
  conga.SetBeat(kChannelBassDrum, 7);
  conga.SetBeat(kChannelBassDrum, 7.75);

  // sd
  conga.SetBeat(kChannelSnare, 1);
  conga.SetBeat(kChannelSnare, 2);
  conga.SetBeat(kChannelSnare, 3);
  conga.SetBeat(kChannelSnare, 4.75);
  conga.SetBeat(kChannelSnare, 5);
  conga.SetBeat(kChannelSnare, 6);
  conga.SetBeat(kChannelSnare, 7);
  conga.SetBeat(kChannelSnare, 7.75);
  conga.SetBeat(kChannelSnare, 8.75);

  return conga.GetScore();
}

Score Conga = GetCongaScore();

}  // namespace beats
}  // namespace audio
}  // namespace kss
