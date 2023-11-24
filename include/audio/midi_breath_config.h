#pragma once
#include <string.h>
#include <stdio.h>
#include "serial/debug.h"        // for Debug

namespace kss {
namespace audio {

    // 3 Clusters - 1 per MIDI channel
    // 6 Chimes per Cluster - MIDI notes 48, 50, 52, 53, 55, 57 
    //                        (C major scale starting on middile C)
    // 2 Events per Chime - MIDI velocity > or < 75

    //CLUSTER 1
    constexpr char kChimeStrike01[13] = "HIT01.WAV";
    constexpr char kChimeStrike02[13] = "HIT02.WAV";
    constexpr char kChimeStrike03[13] = "HIT03.WAV";
    constexpr char kChimeStrike04[13] = "HIT04.WAV";
    constexpr char kChimeStrike05[13] = "HIT05.WAV";
    constexpr char kChimeStrike06[13] = "HIT06.WAV";

    constexpr char kChimeSway01[13] = "SWAY01.WAV";
    constexpr char kChimeSway02[13] = "SWAY02.WAV";
    constexpr char kChimeSway03[13] = "SWAY03.WAV";
    constexpr char kChimeSway04[13] = "SWAY04.WAV";
    constexpr char kChimeSway05[13] = "SWAY09.WAV";
    constexpr char kChimeSway06[13] = "SWAY08.WAV";

    const char *clusterStrike1[6] {kChimeStrike01, kChimeStrike02, kChimeStrike03, kChimeStrike04, kChimeStrike05, kChimeStrike06 };
    const char *clusterSway1[6] {kChimeSway01, kChimeSway02, kChimeSway03, kChimeSway04, kChimeSway05, kChimeSway06};

    //CLUSTER 2
    constexpr char kChimeStrike07[13] = "HIT07.WAV";
    constexpr char kChimeStrike08[13] = "HIT08.WAV";
    constexpr char kChimeStrike09[13] = "HIT09.WAV";
    constexpr char kChimeStrike10[13] = "HIT10.WAV";
    constexpr char kChimeStrike11[13] = "HIT11.WAV";
    constexpr char kChimeStrike12[13] = "HIT12.WAV";

    constexpr char kChimeSway07[13] = "SWAY07.WAV";
    constexpr char kChimeSway08[13] = "SWAY08.WAV";
    constexpr char kChimeSway09[13] = "SWAY09.WAV";
    constexpr char kChimeSway10[13] = "SWAY10.WAV";
    constexpr char kChimeSway11[13] = "SWAY11.WAV";
    constexpr char kChimeSway12[13] = "SWAY12.WAV";

    const char *clusterStrike2[6] {kChimeStrike07, kChimeStrike08, kChimeStrike09, kChimeStrike10, kChimeStrike11, kChimeStrike12 };
    const char *clusterSway2[6] {kChimeSway07, kChimeSway08, kChimeSway09, kChimeSway10, kChimeSway11, kChimeSway12};

    //CLUSTER 3
    constexpr char kChimeStrike13[13] = "HIT13.WAV";
    constexpr char kChimeStrike14[13] = "HIT14.WAV";
    constexpr char kChimeStrike15[13] = "HIT15.WAV";
    constexpr char kChimeStrike16[13] = "HIT16.WAV";
    constexpr char kChimeStrike17[13] = "HIT17.WAV";
    constexpr char kChimeStrike18[13] = "HIT18.WAV";

    constexpr char kChimeSway13[13] = "SWAY13.WAV";
    constexpr char kChimeSway14[13] = "SWAY14.WAV";
    constexpr char kChimeSway15[13] = "SWAY15.WAV";
    constexpr char kChimeSway16[13] = "SWAY16.WAV";
    constexpr char kChimeSway17[13] = "SWAY17.WAV";
    constexpr char kChimeSway18[13] = "SWAY18.WAV";

    const char *clusterStrike3[6] {kChimeStrike13, kChimeStrike14, kChimeStrike15, kChimeStrike16, kChimeStrike17, kChimeStrike18 };
    const char *clusterSway3[6] {kChimeSway13, kChimeSway14, kChimeSway15, kChimeSway16, kChimeSway17, kChimeSway18};

    const char **motherClusterStrike[3] {clusterStrike1, clusterStrike2, clusterStrike3};
    const char **motherClusterSway[3] {clusterSway1, clusterSway2, clusterSway3};

    //FUNCTIONS
    static const char* getChimeAudioName(int channel, int chimeIndex, bool isStrike) {
        const char* fileName;
        if(isStrike) {
            const char* fileName = motherClusterStrike[channel - 1][chimeIndex];         
            Debug("FILENAME GOT: " + fileName);
            return fileName;
        } else {
            const char* fileName = motherClusterSway[channel - 1][chimeIndex];
            // return "MOONJAZZ.WAV";
            return fileName;
        }
        return fileName;
    }

    static bool strikeFilter(int velocity){
        bool isStrike = true;
        if (velocity < 75) {
            isStrike = false;
        }
        return isStrike;
    }

    static int noteSampleMapping(int note) {
        switch(note) {
            case 48:
                return 0;

            case 50:
                return 1;
            
            case 52:
                return 2;
            
            case 53:
                return 3;
            
            case 55:
                return 4;
            
            case 57:
                return 5;

            default:
                Debug("Error: Unrecognized MIDI Note");
                break;
        }

    }

}
}