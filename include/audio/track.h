#pragma once

#include <queue>  // for queue

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
  std::queue<Score*> playlist;
  Score::Iterator next_note;

 public:
  AudioTrack(size_t serial_id, Score* score)
      : synth{serial::kHwSerials[serial_id]},
        score{score},
        next_note{score->begin()} {}

  void Play() {
    Debug_here();
    start_time = time::Now();
    next_note = score->begin();

    // Go ahead and play NOW, they probably have a 0ms note on beat 1
    Update();
  }

  void Update() {
    // Looping at the end of the score
    if (next_note == score->end()) {
      // Shift start_time by the length of the last score
      start_time += score->length_millis;

      // Switch to the next score if one was requested
      if (!playlist.empty()) {
        score = playlist.front();
        playlist.pop();
      }

      // Set the score iterator to the beginning of the new score
      next_note = score->begin();
    }

    // If we haven't started the score yet, then just chill
    if (start_time > time::Now()) {
      return;
    }

    // Play notes that need to be played or until we hit the end
    const uint32_t track_time = time::Now() - start_time;
    while (next_note != score->end() && track_time >= next_note->first) {
      // Play the note(s)
      synth.StartInput(next_note->second);

      //   Debug("Playing note_t=" + next_note->first + " on ch" +
      //         next_note->second + " at track_t=" + track_time);

      ++next_note;
    }
  }

  // Switch to a new score after this one is done
  void SwitchTo(Score* new_score) { playlist.push(new_score); }

  // Switch immediately to the new score
  // jumping in at the same time we were through the old score
  void SwitchImmediatelyTo(Score* new_score) {
    // Cancel any pending score changes
    while (!playlist.empty()) {
      playlist.pop();
    }

    // Switch over to the new score
    score = new_score;
    next_note = score->begin();

    // If we haven't started the score yet, then just chill
    if (start_time > time::Now()) {
      return;
    }

    // Adjust start_time if track_time is past the end of the new score
    uint32_t track_time = time::Now() - start_time;
    while (track_time >= score->length_millis) {
      // This should never pass Now since the conditional above
      start_time += score->length_millis;
      track_time = time::Now() - start_time;  // Recalculate

      // Debug("Adjusting track time for shorter score");
    }

    // Test for the unthinkable
    while (start_time > time::Now()) {
      Debug("Time is a flat circle!");
      // loop forever
    }

    // FFWD the next_note iterator to the current track time
    // bool fasted_forward = false;
    while (next_note != score->end() && track_time >= next_note->first) {
      ++next_note;
      //   fasted_forward = true;
    }

    // if (fasted_forward) {
    //   Debug("FFW'd to note_t=" + next_note->first +
    //         " at track_t=" + track_time);
    // }
  }
};

}  // namespace audio
}  // namespace kss
