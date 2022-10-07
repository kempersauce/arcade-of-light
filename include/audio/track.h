#pragma once

#include <queue>  // for queue

#include "audio/score.h"   // for Score
#include "serial/debug.h"  // for Debug
#include "time/now.h"      // for Now

namespace kss {
namespace audio {

class AudioTrack {
  std::queue<uint8_t> notes_out;
  uint32_t start_time{0};

  Score* score;
  std::queue<Score*> playlist;
  Score::Iterator next_note;

 public:
  AudioTrack(Score* score) : score{score}, next_note{score->begin()} {}

  bool HasNotes() { return !notes_out.empty(); }

  // Get next note that should be played now. Does not check availability
  uint8_t GetNextNote() {
    uint8_t next_note = notes_out.front();
    notes_out.pop();
    return next_note;
  }

  void Play() {
    Debug_here();
    start_time = time::Now();
    next_note = score->begin();

    // Go ahead and play NOW, they probably have a 0ms note on beat 1
    Update();
  }

  void Update() {
    // TODO should we clear the output queue here in case nobody's listening?
    // This also means if we call update twice then we potentially skip notes
    // while (HasNotes()) {
    //   notes_out.pop();
    // }

    // Looping at the end of the score
    if (next_note == score->end()) {
      // Debug("Looping at the end of the score");

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
      // Debug("start_time is in the future, skipping playing.");
      return;
    }

    // Play notes that need to be played or until we hit the end
    const uint32_t track_time = time::Now() - start_time;
    while (next_note != score->end() && track_time >= next_note->first) {
      // Play the note(s)
      // Debug("Adding note to output queue: " + next_note->second);
      notes_out.push(next_note->second);

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
    }

    // Test for the unthinkable
    while (start_time > time::Now()) {
      Debug("Time is a flat circle!");
      // loop forever
    }

    // FFWD the next_note iterator to the current track time
    while (next_note != score->end() && track_time >= next_note->first) {
      ++next_note;
    }
  }
};

}  // namespace audio
}  // namespace kss
