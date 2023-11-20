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
    constexpr char kChimeStrike1[13] = "A01.WAV";
    constexpr char kChimeStrike2[13] = "808CLAV.WAV";
    constexpr char kChimeStrike3[13] = "808BD01.WAV";
    constexpr char kChimeStrike4[13] = "808BD02.WAV";
    constexpr char kChimeStrike5[13] = "808CRSH1.WAV";
    constexpr char kChimeStrike6[13] = "808CRSH2.WAV";

    constexpr char kChimeSway1[13] = "G01.WAV";
    constexpr char kChimeSway2[13] = "JUPITER.WAV";
    constexpr char kChimeSway3[13] = "EARTH.WAV";
    constexpr char kChimeSway4[13] = "MARS.WAV";
    constexpr char kChimeSway5[13] = "PLUTO.WAV";
    constexpr char kChimeSway6[13] = "THRUST1.WAV";

    const char *clusterStrike1[6] {kChimeStrike1, kChimeStrike2, kChimeStrike3, kChimeStrike4, kChimeStrike5, kChimeStrike6 };
    const char *clusterSway1[6] {kChimeSway1, kChimeSway2, kChimeSway3, kChimeSway4, kChimeSway5, kChimeSway6};

    static const char* getChimeAudioName(int channel, int chimeIndex, int velocity) {
        bool isStrike = true;
        const char* fileName;
        if (velocity < 75 ) {
            isStrike = false;
        }
        if(isStrike) {
            const char* fileName = clusterStrike1[chimeIndex];         
            Debug("FILENAME GOT: " + fileName);
            return fileName;
        } else {
            const char* fileName = clusterSway1[chimeIndex];
            // return "MOONJAZZ.WAV";
            return fileName;
        }
        Debug("FILENAME GOT: " + fileName);
        return fileName;
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