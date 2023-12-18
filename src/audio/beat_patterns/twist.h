#pragma once

#include "audio/beat_patterns/constants.h"  // for kChannel*
#include "audio/score.h"                    // for Score

namespace kss {
namespace audio {
namespace beats {

const Score GetTwistScore() {
  ScoreBuilder twist{120, 1};

  // tom h
  twist.SetBeat(kChannelTom, 4);
  twist.SetBeat(kChannelTom, 4.5);

  // hh closed
  twist.SetBeat(kChannelHHClosed, 1);
  twist.SetBeat(kChannelHHClosed, 1.5);
  twist.SetBeat(kChannelHHClosed, 2);
  twist.SetBeat(kChannelHHClosed, 2.5);
  twist.SetBeat(kChannelHHClosed, 3);
  twist.SetBeat(kChannelHHClosed, 3.5);
  twist.SetBeat(kChannelHHClosed, 4);
  twist.SetBeat(kChannelHHClosed, 4.5);

  // crash
  twist.SetBeat(kChannelCrash, 1);
  twist.SetBeat(kChannelCrash, 2);
  twist.SetBeat(kChannelCrash, 3);
  twist.SetBeat(kChannelCrash, 4);

  // clap
  twist.SetBeat(kChannelClap, 2);
  twist.SetBeat(kChannelClap, 4);

  // bd
  twist.SetBeat(kChannelBassDrum, 1);
  twist.SetBeat(kChannelBassDrum, 2);
  twist.SetBeat(kChannelBassDrum, 3);
  twist.SetBeat(kChannelBassDrum, 4);

  // sd
  twist.SetBeat(kChannelSnare, 2);

  return twist.GetScore();
}

Score Twist = GetTwistScore();

}  // namespace beats
}  // namespace audio
}  // namespace kss
