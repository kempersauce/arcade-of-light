#pragma once

#include "audio/beat_patterns/constants.h"  // for kChannel*
#include "audio/score.h"                    // for Score

namespace kss {
namespace audio {
namespace beats {

const Score GetBootsAndCatsScore() {
  ScoreBuilder bootsAndCats{240, 2};

  // tom h
  //   bootsAndCats.SetBeat(kChannelTom, 5);
  //   bootsAndCats.SetBeat(kChannelTom, 5.5);
  //   bootsAndCats.SetBeat(kChannelTom, 6);
  //   bootsAndCats.SetBeat(kChannelTom, 6.5);

  // hh closed
  bootsAndCats.SetBeatEveryMeasure(kChannelHHClosed, 1);
  bootsAndCats.SetBeatEveryMeasure(kChannelHHClosed, 2);
  bootsAndCats.SetBeatEveryMeasure(kChannelHHClosed, 3);
  bootsAndCats.SetBeatEveryMeasure(kChannelHHClosed, 4);


  // crash
  // bootsAndCats.SetBeatEveryMeasure(kChannelCrash, 3);
  // bootsAndCats.SetBeat(kChannelCrash, 4);


  // clap
  // bootsAndCats.SetBeat(kChannelClap, 2);
  // bootsAndCats.SetBeat(kChannelClap, 2.69);
  // bootsAndCats.SetBeat(kChannelClap, 4);

  // bd
  bootsAndCats.SetBeat(kChannelBassDrum, 1);
  bootsAndCats.SetBeat(kChannelBassDrum, 5);


  // bootsAndCats.SetBeat(kChannelBassDrum, 2);
  // bootsAndCats.SetBeat(kChannelBassDrum, 2.75);
  // bootsAndCats.SetBeat(kChannelBassDrum, 3);
  // bootsAndCats.SetBeat(kChannelBassDrum, 4);
  // bootsAndCats.SetBeat(kChannelBassDrum, 4.75);

  // sd
  bootsAndCats.SetBeatEveryMeasure(kChannelSnare, 3);
  // bootsAndCats.SetBeat(kChannelSnare, 4);

  return bootsAndCats.GetScore();
}

Score BootsAndCats = GetBootsAndCatsScore();

}
}
}
