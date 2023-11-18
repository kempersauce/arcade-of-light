#pragma once

namespace kss {
namespace audio {

    // 3 Clusters - 1 per MIDI channel
    // 6 Chimes per Cluster - MIDI notes 48, 50, 52, 53, 55, 57 
    //                        (C major scale starting on middile C)
    // 2 Events per Chime - MIDI velocity > or < 75

    //CLUSTER 1
    constexpr char kChimeStrike1[12] = "NATPAD.WAV";
    constexpr char kChimeStrike2[12] = "NATPAD.WAV";
    const char kChimeStrike3[12] = "NATPAD.WAV";
    constexpr char kChimeStrike4[12] = "NATPAD.WAV";
    constexpr char kChimeStrike5[12] = "NATPAD.WAV";
    constexpr char kChimeStrike6[12] = "NATPAD.WAV";

    constexpr char kChimeSway1[12] = "NATPAD.WAV";
    constexpr char kChimeSway2[12] = "NATPAD.WAV";
    constexpr char kChimeSway3[12] = "NATPAD.WAV";
    constexpr char kChimeSway4[12] = "NATPAD.WAV";
    constexpr char kChimeSway5[12] = "NATPAD.WAV";
    constexpr char kChimeSway6[12] = "NATPAD.WAV";

    const char clusterStrike1[6][12] {*kChimeStrike1, *kChimeStrike2, *kChimeStrike3, *kChimeStrike4, *kChimeStrike5, *kChimeStrike6 };
    const char clusterSway1[6][12] {*kchimeSway1, *kchimeSway2, *kchimeSway3, *kchimeSway4, *kchimeSway5, *kchimeSway6};


    static void getChimeAudioName(int channel, int note, int velocity) {

    }

}
}