#pragma once

#include "audio/score.h"             // for Score
#include "audio/synth_sender_raw.h"  // for SynthSenderRaw
#include "serial/debug.h"            // for Debug
#include "serial/hw_serials.h"       // for kHwSerials
#include "time/now.h"                // for Now

namespace kss {
namespace audio {

class AudioTrack {
  SynthSenderRaw synth;

  uint32_t start_time{0};

  Score* score;
  Score::Iterator next_note;
  bool is_playing{false};

 public:
  AudioTrack(size_t serial_id, Score* score)
      : synth{serial::kHwSerials[serial_id]}, score{score} {
    //   ScoreBuilder main_score{165, 32};
    //   main_score.SetBeatEveryMeasure(4, 1);
    //   main_score.SetBeatEveryMeasure(3, 2);
    //   main_score.SetBeatEveryMeasure(5, 3);
    //   main_score.SetBeatEveryMeasure(3, 4);

    //   ScoreBuilder flare_score{165, 28};
    //   // Double bass, starts .25 beats before measure 3, beat 1, every 4
    //   // measures
    //   flare_score.SetBeatEveryMeasure(4, 8.75, 4);

    //   // cymbal roll on beat 2 every 2nd & 4th measure
    //   flare_score.SetBeatEveryMeasure(3, 2, 2);
    //   flare_score.SetBeatEveryMeasure(3, 2.1667, 2);
    //   flare_score.SetBeatEveryMeasure(3, 2.3333, 2);

    //   // Lay the flare track over the main track after 16 beats (4 measures)
    //   main_score.AddScore(flare_score.GetScore(), 16);

    //   score = main_score.GetScore();
  }

  void Play() {
    Debug_here();
    start_time = time::Now();
    next_note = score->begin();
    is_playing = true;

    // Go ahead and play NOW, they probably have a 0ms note on beat 1
    Update();
  }

  void Update() {
    if (!is_playing) {
      return;
    }

    if (next_note == score->end()) {
      is_playing = false;
      Debug("End of score reached. Done playing.");
      return;
    }

    const uint32_t track_time = time::Now() - start_time;
    while (next_note != score->end() && track_time >= next_note->first) {
      // Play the note(s)
      synth.StartInput(next_note->second);

      Debug("Playing note_t=" + next_note->first + " on ch" +
            next_note->second + " at actual_t=" + track_time);

      ++next_note;
    }
  }
};

}  // namespace audio
}  // namespace kss
