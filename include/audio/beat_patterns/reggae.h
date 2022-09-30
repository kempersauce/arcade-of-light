#pragma once

#include "audio/beat_patterns/constants.h"  // for kChannel*
#include "audio/score.h"                    // for Score

namespace kss {
namespace audio {
namespace beats {

const Score GetReggaeScore() {
  ScoreBuilder reggae{120, 2};

  // tom h
  reggae.SetBeat(kChannelTom, 7.5);
  reggae.SetBeat(kChannelTom, 8);

  // hh closed
  reggae.SetBeat(kChannelHHClosed, 1);
  reggae.SetBeat(kChannelHHClosed, 2);
  reggae.SetBeat(kChannelHHClosed, 3);
  reggae.SetBeat(kChannelHHClosed, 4);
  reggae.SetBeat(kChannelHHClosed, 5);
  reggae.SetBeat(kChannelHHClosed, 6);
  reggae.SetBeat(kChannelHHClosed, 7);
  reggae.SetBeat(kChannelHHClosed, 8);

  // crash
  reggae.SetBeat(kChannelCrash, 1);

  // clap
  reggae.SetBeat(kChannelClap, 8);
  reggae.SetBeat(kChannelClap, 8.5);

  // bd
  reggae.SetBeat(kChannelBassDrum, 1);
  reggae.SetBeat(kChannelBassDrum, 3);
  reggae.SetBeat(kChannelBassDrum, 5);
  reggae.SetBeat(kChannelBassDrum, 7);

  // sd
  reggae.SetBeat(kChannelSnare, 3);
  reggae.SetBeat(kChannelSnare, 7);

  return reggae.GetScore();
}

Score Reggae = GetReggaeScore();

}  // namespace beats
}  // namespace audio
}  // namespace kss
