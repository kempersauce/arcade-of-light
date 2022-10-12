#pragma once

#include "audio/beat_patterns/constants.h"  // for kChannel*
#include "audio/score.h"                    // for Score

namespace kss {
namespace audio {
namespace beats {

const Score GetTrapScore() {
  ScoreBuilder trap{120, 2};

  // tom h
  // trap.SetBeat(kChannelTom, 7.5);
  // trap.SetBeat(kChannelTom, 8);

  // hh closed
  trap.SetBeat(kChannelHHClosed, 1);        //1
  trap.SetBeat(kChannelHHClosed, 1.25);
  trap.SetBeat(kChannelHHClosed, 1.5);
  trap.SetBeat(kChannelHHClosed, 1.75);  
  trap.SetBeat(kChannelHHClosed, 2);        //2
  trap.SetBeat(kChannelHHClosed, 2.25);
  trap.SetBeat(kChannelHHClosed, 2.5);
  trap.SetBeat(kChannelHHClosed, 2.75);
  trap.SetBeat(kChannelHHClosed, 3);        //3
  trap.SetBeat(kChannelHHClosed, 3.25);
  trap.SetBeat(kChannelHHClosed, 3.5);
  trap.SetBeat(kChannelHHClosed, 3.75); 
  trap.SetBeat(kChannelHHClosed, 4);        //4
  trap.SetBeat(kChannelHHClosed, 4.25);
  trap.SetBeat(kChannelHHClosed, 4.5);
  trap.SetBeat(kChannelHHClosed, 4.75);
  trap.SetBeat(kChannelHHClosed, 5);        //5
  trap.SetBeat(kChannelHHClosed, 5.25);
  trap.SetBeat(kChannelHHClosed, 5.5);
  trap.SetBeat(kChannelHHClosed, 5.75);  
  trap.SetBeat(kChannelHHClosed, 6);        //6
  trap.SetBeat(kChannelHHClosed, 6.25);
  trap.SetBeat(kChannelHHClosed, 6.5);
  trap.SetBeat(kChannelHHClosed, 6.75);
  trap.SetBeat(kChannelHHClosed, 7);        //7
  trap.SetBeat(kChannelHHClosed, 7.25);
  trap.SetBeat(kChannelHHClosed, 7.5);
  trap.SetBeat(kChannelHHClosed, 7.75); 
  trap.SetBeat(kChannelHHClosed, 8);        //8
  trap.SetBeat(kChannelHHClosed, 8.25);
  trap.SetBeat(kChannelHHClosed, 8.5);
  trap.SetBeat(kChannelHHClosed, 8.75);
  trap.SetBeat(kChannelHHClosed, 8.885);



  // crash
//   trap.SetBeat(kChannelCrash, 1);

  // clap
  trap.SetBeat(kChannelClap, 2);
  trap.SetBeat(kChannelClap, 4);
  trap.SetBeat(kChannelClap, 6);
  trap.SetBeat(kChannelClap, 8);
  trap.SetBeat(kChannelClap, 8.5);
  trap.SetBeat(kChannelClap, 8.75);
  

  // bd
  trap.SetBeat(kChannelBassDrum, 1);
  trap.SetBeat(kChannelBassDrum, 5);

  // sd
  trap.SetBeat(kChannelSnare, 2.75);
  trap.SetBeat(kChannelSnare, 3.25);
  trap.SetBeat(kChannelSnare, 4.75);
  trap.SetBeat(kChannelSnare, 6.75);
  trap.SetBeat(kChannelSnare, 7.25);
  trap.SetBeat(kChannelSnare, 8.75);

  return trap.GetScore();
}

Score Trap = GetTrapScore();

}  // namespace beats
}  // namespace audio
}  // namespace kss
