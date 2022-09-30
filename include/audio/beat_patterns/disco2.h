#pragma once

#include "audio/beat_patterns/constants.h"  // for kChannel*
#include "audio/score.h"                    // for Score

namespace kss {
namespace audio {
namespace beats {

const Score GetDisco2Score() {
  ScoreBuilder disco2{120, 1};

  // tom h
  disco2.SetBeat(kChannelTom, 2);
  disco2.SetBeat(kChannelTom, 4);

  // hh closed
  disco2.SetBeat(kChannelHHClosed, 1);
  disco2.SetBeat(kChannelHHClosed, 1.25);
  disco2.SetBeat(kChannelHHClosed, 1.5);
  disco2.SetBeat(kChannelHHClosed, 1.75);
  disco2.SetBeat(kChannelHHClosed, 2);
  disco2.SetBeat(kChannelHHClosed, 2.25);
  disco2.SetBeat(kChannelHHClosed, 2.5);
  disco2.SetBeat(kChannelHHClosed, 2.75);
  disco2.SetBeat(kChannelHHClosed, 3);
  disco2.SetBeat(kChannelHHClosed, 3.25);
  disco2.SetBeat(kChannelHHClosed, 3.5);
  disco2.SetBeat(kChannelHHClosed, 3.75);
  disco2.SetBeat(kChannelHHClosed, 4);
  disco2.SetBeat(kChannelHHClosed, 4.25);
  disco2.SetBeat(kChannelHHClosed, 4.5);
  disco2.SetBeat(kChannelHHClosed, 4.75);

  // crash
  disco2.SetBeat(kChannelCrash, 1);

  // clap
  disco2.SetBeat(kChannelClap, 1);
  disco2.SetBeat(kChannelClap, 4);
  disco2.SetBeat(kChannelClap, 4.5);

  // bd
  disco2.SetBeat(kChannelBassDrum, 1);
  disco2.SetBeat(kChannelBassDrum, 2);
  disco2.SetBeat(kChannelBassDrum, 2.25);
  disco2.SetBeat(kChannelBassDrum, 3);
  disco2.SetBeat(kChannelBassDrum, 3.75);
  disco2.SetBeat(kChannelBassDrum, 4);

  // sd
  disco2.SetBeat(kChannelSnare, 2);
  disco2.SetBeat(kChannelSnare, 4);
  disco2.SetBeat(kChannelSnare, 4.5);
  disco2.SetBeat(kChannelSnare, 4.75);

  return disco2.GetScore();
}

Score Disco2 = GetDisco2Score();

}  // namespace beats
}  // namespace audio
}  // namespace kss
