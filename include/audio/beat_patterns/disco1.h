#pragma once

#include "audio/beat_patterns/constants.h"  // for kChannel*
#include "audio/score.h"                    // for Score

namespace kss {
namespace audio {
namespace beats {

const Score GetDisco1Score() {
  ScoreBuilder disco1{120, 1};

  // tom h
  disco1.SetBeat(kChannelTom, 1);
  disco1.SetBeat(kChannelTom, 4.5);
  disco1.SetBeat(kChannelTom, 4.75);

  // hh closed
  disco1.SetBeat(kChannelHHClosed, 1);
  disco1.SetBeat(kChannelHHClosed, 1.25);
  disco1.SetBeat(kChannelHHClosed, 1.5);
  disco1.SetBeat(kChannelHHClosed, 1.75);
  disco1.SetBeat(kChannelHHClosed, 2);
  disco1.SetBeat(kChannelHHClosed, 2.25);
  disco1.SetBeat(kChannelHHClosed, 2.5);
  disco1.SetBeat(kChannelHHClosed, 2.75);
  disco1.SetBeat(kChannelHHClosed, 3);
  disco1.SetBeat(kChannelHHClosed, 3.25);
  disco1.SetBeat(kChannelHHClosed, 3.5);
  disco1.SetBeat(kChannelHHClosed, 3.75);
  disco1.SetBeat(kChannelHHClosed, 4);
  disco1.SetBeat(kChannelHHClosed, 4.25);
  disco1.SetBeat(kChannelHHClosed, 4.5);
  disco1.SetBeat(kChannelHHClosed, 4.75);

  // crash
  disco1.SetBeat(kChannelCrash, 1);
  disco1.SetBeat(kChannelCrash, 2);
  disco1.SetBeat(kChannelCrash, 3);
  disco1.SetBeat(kChannelCrash, 4);

  // clap
  disco1.SetBeat(kChannelClap, 2.5);
  disco1.SetBeat(kChannelClap, 2.75);
  disco1.SetBeat(kChannelClap, 3);

  // bd
  disco1.SetBeat(kChannelBassDrum, 1);
  disco1.SetBeat(kChannelBassDrum, 1.75);
  disco1.SetBeat(kChannelBassDrum, 2);
  disco1.SetBeat(kChannelBassDrum, 2.5);
  disco1.SetBeat(kChannelBassDrum, 3);
  disco1.SetBeat(kChannelBassDrum, 3.75);
  disco1.SetBeat(kChannelBassDrum, 4);
  disco1.SetBeat(kChannelBassDrum, 4.5);

  // sd
  disco1.SetBeat(kChannelSnare, 2);
  disco1.SetBeat(kChannelSnare, 4);

  return disco1.GetScore();
}

Score Disco1 = GetDisco1Score();

}  // namespace beats
}  // namespace audio
}  // namespace kss
