#pragma once

#include <Arduino.h>

#include <vector>  // for vector

#include "audio/synth_note.h"  // for SynthNote
#include "serial/debug.h"      // for Debug

namespace kss {
namespace audio {

constexpr uint32_t kBpm110OffsetMillis{1000 * 60 / 110};

struct NoteInfo {
  const uint32_t start_time;
  const uint32_t note_length;
  const float frequency;

  NoteInfo(uint32_t start_time, uint32_t note_length, float frequency)
      : start_time{start_time},
        note_length{note_length},
        frequency{frequency} {}
};

class AudioTrack {
  uint32_t start_time;
  std::vector<uint32_t> note_times;
  size_t next_note_index{0};

 public:
  SynthNote synth;

  AudioTrack() {
    for (uint8_t i = 0; i < 110; i++) {
      note_times.push_back(i * kBpm110OffsetMillis);
    }
  }

  void Play() {
    Debug_here();
    start_time = millis();
    next_note_index = 0;
    next_stop = 0;
    Update();
  }

  bool IsPlaying() const { return next_note_index < note_times.size(); }

  uint32_t next_stop{0};
  void Update() {
    const uint32_t now = millis();
    const uint32_t track_time = now - start_time;

    while (IsPlaying() && track_time >= note_times[next_note_index]) {
      // Play the note
      synth.envelope.noteOn();
      Debug("Playing note " + note_times[next_note_index] +
            " at t=" + track_time);
      next_stop = note_times[next_note_index] + 5;
      next_note_index++;
    }

    if (next_stop != 0 && track_time >= next_stop) {
      Debug("Stopping note at " + next_stop + " at t=" + track_time);
      synth.envelope.noteOff();
      next_stop = 0;
    }
  }
};

}  // namespace audio
}  // namespace kss
