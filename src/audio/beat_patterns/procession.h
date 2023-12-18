#pragma once

#include "audio/beat_patterns/constants.h"  // for kChannel*
#include "audio/score.h"                    // for Score

namespace kss {
namespace audio {
namespace beats {

const Score GetProcessionScore() {
  ScoreBuilder procession{120, 2};

  // tom h
  procession.SetBeat(kChannelTom, 8);
  procession.SetBeat(kChannelTom, 8.33);
  procession.SetBeat(kChannelTom, 8.67);

  // hh closed
  procession.SetBeat(kChannelHHClosed, 1);
  procession.SetBeat(kChannelHHClosed, 2.5);
  procession.SetBeat(kChannelHHClosed, 2.75);
  procession.SetBeat(kChannelHHClosed, 3);
  procession.SetBeat(kChannelHHClosed, 3.5);
  procession.SetBeat(kChannelHHClosed, 4.5);
  procession.SetBeat(kChannelHHClosed, 5);
  procession.SetBeat(kChannelHHClosed, 7);
  procession.SetBeat(kChannelHHClosed, 7.15);
  procession.SetBeat(kChannelHHClosed, 7.25);
  procession.SetBeat(kChannelHHClosed, 7.35);
  procession.SetBeat(kChannelHHClosed, 7.45);
  procession.SetBeat(kChannelHHClosed, 7.55);
  procession.SetBeat(kChannelHHClosed, 7.65);
  procession.SetBeat(kChannelHHClosed, 7.75);
  procession.SetBeat(kChannelHHClosed, 7.85);
  procession.SetBeat(kChannelHHClosed, 7.95);
  procession.SetBeat(kChannelHHClosed, 8);
  procession.SetBeat(kChannelHHClosed, 8.5);
  procession.SetBeat(kChannelHHClosed, 8.75);

  // crash
  procession.SetBeat(kChannelCrash, 2);

  // clap
  procession.SetBeat(kChannelClap, 1);
  procession.SetBeat(kChannelClap, 2.5);
  procession.SetBeat(kChannelClap, 2.75);
  procession.SetBeat(kChannelClap, 3);
  procession.SetBeat(kChannelClap, 3.5);
  procession.SetBeat(kChannelClap, 4.5);
  procession.SetBeat(kChannelClap, 5);
  procession.SetBeat(kChannelClap, 7);
  procession.SetBeat(kChannelClap, 7.25);
  procession.SetBeat(kChannelClap, 7.5);
  procession.SetBeat(kChannelClap, 7.75);
  procession.SetBeat(kChannelClap, 8);
  procession.SetBeat(kChannelClap, 8.5);

  // bd
  procession.SetBeat(kChannelBassDrum, 1);
  procession.SetBeat(kChannelBassDrum, 3);
  procession.SetBeat(kChannelBassDrum, 5);

  // sd
  procession.SetBeat(kChannelSnare, 2.12);
  procession.SetBeat(kChannelSnare, 2.43);
  procession.SetBeat(kChannelSnare, 2.74);
  procession.SetBeat(kChannelSnare, 3);
  procession.SetBeat(kChannelSnare, 3.5);
  procession.SetBeat(kChannelSnare, 8);
  procession.SetBeat(kChannelSnare, 8.3);
  procession.SetBeat(kChannelSnare, 8.6);

  return procession.GetScore();
}

Score Procession = GetProcessionScore();

}  // namespace beats
}  // namespace audio
}  // namespace kss
