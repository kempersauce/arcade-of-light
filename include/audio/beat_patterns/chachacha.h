#pragma once

#include "audio/beat_patterns/constants.h"  // for kChannel*
#include "audio/score.h"                    // for Score

namespace kss {
namespace audio {
namespace beats {

const Score GetChachachaScore() {
  ScoreBuilder chachacha{120, 2};

  // tom h
  chachacha.SetBeat(kChannelTom, 2.5);
  chachacha.SetBeat(kChannelTom, 4);
  chachacha.SetBeat(kChannelTom, 6);
  chachacha.SetBeat(kChannelTom, 7);
  chachacha.SetBeat(kChannelTom, 7.5);
  chachacha.SetBeat(kChannelTom, 8);

  // hh closed
  chachacha.SetBeat(kChannelHHClosed, 1);
  chachacha.SetBeat(kChannelHHClosed, 1.5);
  chachacha.SetBeat(kChannelHHClosed, 2);
  chachacha.SetBeat(kChannelHHClosed, 3);
  chachacha.SetBeat(kChannelHHClosed, 3.5);
  chachacha.SetBeat(kChannelHHClosed, 4);
  chachacha.SetBeat(kChannelHHClosed, 5);
  chachacha.SetBeat(kChannelHHClosed, 5.5);
  chachacha.SetBeat(kChannelHHClosed, 6);
  chachacha.SetBeat(kChannelHHClosed, 7);
  chachacha.SetBeat(kChannelHHClosed, 7.5);
  chachacha.SetBeat(kChannelHHClosed, 8);

  // crash
  chachacha.SetBeat(kChannelCrash, 2);
  chachacha.SetBeat(kChannelCrash, 4);
  chachacha.SetBeat(kChannelCrash, 6);
  chachacha.SetBeat(kChannelCrash, 8);

  // clap
  chachacha.SetBeat(kChannelClap, 7);
  chachacha.SetBeat(kChannelClap, 7.5);
  chachacha.SetBeat(kChannelClap, 8);

  // bd
  chachacha.SetBeat(kChannelBassDrum, 1);
  chachacha.SetBeat(kChannelBassDrum, 2);
  chachacha.SetBeat(kChannelBassDrum, 3);
  chachacha.SetBeat(kChannelBassDrum, 4);
  chachacha.SetBeat(kChannelBassDrum, 4.5);
  chachacha.SetBeat(kChannelBassDrum, 5);
  chachacha.SetBeat(kChannelBassDrum, 6);
  chachacha.SetBeat(kChannelBassDrum, 7);
  chachacha.SetBeat(kChannelBassDrum, 8);

  // sd
  chachacha.SetBeat(kChannelSnare, 1);
  chachacha.SetBeat(kChannelSnare, 1.5);
  chachacha.SetBeat(kChannelSnare, 1.75);
  chachacha.SetBeat(kChannelSnare, 2);
  chachacha.SetBeat(kChannelSnare, 3);
  chachacha.SetBeat(kChannelSnare, 3.5);
  chachacha.SetBeat(kChannelSnare, 4.5);
  chachacha.SetBeat(kChannelSnare, 5);
  chachacha.SetBeat(kChannelSnare, 5.5);
  chachacha.SetBeat(kChannelSnare, 6.5);

  return chachacha.GetScore();
}

Score Chachacha = GetChachachaScore();

}  // namespace beats
}  // namespace audio
}  // namespace kss
