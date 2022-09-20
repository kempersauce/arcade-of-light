#pragma once

#include <map>  // for multimap

#include "serial/debug.h"  // for Debug

namespace kss {
namespace audio {

// Stores notes by timestamp->channel
using Score = std::multimap<uint32_t, uint8_t>;

class ScoreBuilder {
  const size_t channel_cnt{6};
  const uint8_t beats_per_measure{4};
  const uint32_t note_offset_millis;
  const size_t measure_count;

  Score score;

 public:
  ScoreBuilder(float bpm, size_t measure_count)
      : note_offset_millis{1000 * 60 / bpm}, measure_count{measure_count} {}

  // using float for the beat allows us to do things
  // like beat 2.25 for 16th notes
  // 3.0, 3.333, 3.666 for a triplet (I think?)
  // 1.15 for double bass
  void SetNote(uint8_t channel, float beat) {
    // Subtrack 1 offset to make this 1-based
    const uint32_t note_ts = (beat * note_offset_millis) - note_offset_millis;
    score.emplace(note_ts, channel);
  }

  void SetBeatEveryMeasure(size_t channel, float beat,
                           size_t measure_window_size = 1) {
    for (size_t measure = 0; measure < measure_count;
         measure += measure_window_size) {
      const float beat_ts = beat + measure * beats_per_measure;
      if (beat_ts >= 0) {
        SetNote(channel, beat_ts);
      }
    }
  }

  // Add another score to this one
  void AddScore(const Score& other, float beat_offset) {
    const uint32_t note_ts_offset = beat_offset * note_offset_millis;
    for (auto it = other.cbegin(); it != other.cend(); it++) {
      score.emplace(it->first + note_ts_offset, it->second);
    }
  }

  const Score& GetScore() const { return score; }
};

}  // namespace audio
}  // namespace kss
