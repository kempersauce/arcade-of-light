#pragma once

#include <Arduino.h>

#include <map>  // for multimap

#include "audio/synth_sender_raw.h"  // for SynthSenderRaw
#include "serial/debug.h"            // for Debug
#include "serial/hw_serials.h"       // for kHwSerials

namespace kss {
namespace audio {

struct ScoreFloat {
  std::multimap<uint32_t, uint8_t> notes;  // stored by timestamp->channel
  const size_t channel_cnt{6};
  const uint32_t note_offset_millis;

  ScoreFloat(float bpm) : note_offset_millis{1000 * 60 / bpm} {}

  // using float for the beat allows us to do things
  // like beat 2.25 for 16th notes
  // or 3.0, 3.333, 3.666 for a triplet (I think?)
  // maybe 1.05 for double bass?
  void SetNote(uint8_t channel, float beat) {
    // Subtrack 1 offset to make this 1-based
    const uint32_t note_ts = (beat * note_offset_millis) - note_offset_millis;
    notes.emplace(note_ts, channel);
  }

  void SetBeatEveryMeasure(size_t channel, float beat, size_t measures) {
    for (size_t measure = 0; measure < measures; ++measure) {
      const float beat_ts = beat + measure * 4;
      if (beat_ts >= 0) {
        SetNote(channel, beat_ts);
      }
    }
  }
};

class AudioTrack {
  SynthSenderRaw synth;

  uint32_t start_time{0};
  ScoreFloat score{110};
  std::multimap<uint32_t, uint8_t>::const_iterator it;
  bool is_playing{false};

 public:
  AudioTrack(size_t serial_id) : synth{serial::kHwSerials[serial_id]} {
    score.SetBeatEveryMeasure(4, 1, 32);
    score.SetBeatEveryMeasure(3, 2, 32);
    score.SetBeatEveryMeasure(3, 2.333, 32);
    score.SetBeatEveryMeasure(3, 2.666, 32);
    score.SetBeatEveryMeasure(5, 3, 32);
    score.SetBeatEveryMeasure(3, 4, 32);
  }

  void Play() {
    Debug_here();
    start_time = millis();
    score.notes.cbegin();
    it = score.notes.cbegin();
    is_playing = true;
    Update();
  }

  void Update() {
    if (!is_playing) {
      return;
    }

    if (it == score.notes.cend()) {
      is_playing = false;
      Debug("End of score reached. Done playing.");
      return;
    }

    const uint32_t track_time = millis() - start_time;
    while (it != score.notes.cend() && track_time >= it->first) {
      // Play the note(s)
      synth.StartInput(it->second);

      Debug("Playing note_t=" + it->first + " on ch" + it->second +
            " at actual_t=" + track_time);

      ++it;
    }
  }
};

}  // namespace audio
}  // namespace kss
