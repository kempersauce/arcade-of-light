#pragma once

#include <vector>  // for vector

#include "audio/beat_patterns/constants.h"  // for kChannel*
#include "animation/animation.h"     // for Animation
#include "animation/exploder.h"      // for Exploder
#include "animation/explosion.h"     // for Explosion
#include "animation/prompt.h"        // for Prompt
#include "animation/starscape.h"     // for Starscape
#include "audio/score.h"             // for Score
#include "audio/synth_sender_raw.h"  // for SynthSenderRaw
#include "controls/dir_pad.h"        // for DirPad
#include "games/game.h"              // for Game
#include "serial/debug.h"            // for Debug
#include "serial/hw_serials.h"       // for kHwSerials
#include "time/now.h"                // for Now

namespace kss {
namespace games {
namespace rhythm {

namespace _rhythm_single {

const animation::Explosion kExploderPrototype{2, 350, 150, 25, 0,
                                              0, 0,   128, 160};

}  // namespace _rhythm_single
using namespace _rhythm_single;

class RhythmGameSingle : public Game {
  static constexpr uint16_t hit_line_height{35};
  const uint32_t prompt_lead_time{6000};

  // Music score
  audio::Score score;

  // Prompt tracking
  uint32_t prompt_start_time{0};
  audio::Score::Iterator next_prompt;

  // Note tracking
  uint32_t note_start_time{0};
  audio::Score::Iterator next_note;

  // Sticks
  // controls::DirPad controller;

  // Sounds
  //   audio::SynthSenderRaw synth;

  // Animations
  animation::Starscape background;
  std::vector<animation::Prompt*> prompts;
  animation::Exploder exploder;

 public:
  RhythmGameSingle(display::Display* display, uint8_t player_no = 0)
      : Game(display),
        // synth{serial::kHwSerials[player_no]},
        background{display->size},
        exploder{
            kExploderPrototype, {display->size.x / 2, hit_line_height}, 50} {}

  ~RhythmGameSingle() {
    for (auto prompt : prompts) {
      delete prompt;
    }
  }

  void setup() override {
    audio::ScoreBuilder main_score{240, 16};
    main_score.SetBeatEveryMeasure(audio::beats::kChannelBassDrum, 1);
    main_score.SetBeat(audio::beats::kChannelBassDrum, 1.1);
    main_score.SetBeat(audio::beats::kChannelBassDrum, 1.2);
    main_score.SetBeatEveryMeasure(audio::beats::kChannelHHClosed, 2);
    main_score.SetBeatEveryMeasure(audio::beats::kChannelHHClosed, 6.5, 2);
    main_score.SetBeatEveryMeasure(audio::beats::kChannelSnare, 3);
    main_score.SetBeatEveryMeasure(audio::beats::kChannelHHClosed, 4);
    score = main_score.GetScore();

    // THIS should be setup - create track outside of here
    Debug_here();

    // Start creating prompts
    prompt_start_time = time::Now();
    next_prompt = score.begin();

    // Start playing notes after prompts have had time to catch up
    note_start_time = prompt_start_time + prompt_lead_time;
    next_note = score.begin();
  }

  void AddNewPrompts() {
    const uint32_t now = time::Now();
    const uint32_t track_time = now - prompt_start_time;

    if (next_prompt == score.end()) {
      next_prompt = score.begin();
      prompt_start_time += score.length_millis;
    }

    // Don't make prompts if we're ahead of time
    // DO this here to catch track_time underflow
    if (prompt_start_time > now) {
      return;
    }

    while (next_prompt != score.end() && track_time >= next_prompt->first) {
      // Target a time that's prompt_lead_time past the note time,
      // adjusted to system time by prompt_start_time
      const uint32_t prompt_target_time =
          prompt_start_time + next_prompt->first + prompt_lead_time;

      prompts.push_back(new animation::Prompt(
          (animation::Prompt::Direction)(next_prompt->second % 4),
          display->size.y, hit_line_height, prompt_target_time));

      ++next_prompt;
    }
  }

  void MovePrompts() {
    for (auto prompt : prompts) {
      prompt->Move();
      if (prompt->GetY() <= hit_line_height) {
        exploder.Move();
      }
    }
  }

  void CleanDeadPrompts() {
    // Remove dead Prompts
    for (auto it = prompts.begin(); it < prompts.end();) {
      if ((*it)->IsDone()) {
        Debug("Deleting prompt...");
        delete *it;
        it = prompts.erase(it);
      } else {
        ++it;
      }
    }
  }

  void PlayNotes() {
    const uint32_t now = time::Now();
    const uint32_t track_time = now - note_start_time;

    // Repeat if we're at the end
    if (next_note == score.end()) {
      next_note = score.begin();
      note_start_time += score.length_millis;
    }

    // Don't play if we're ahead of time
    // DO this here to catch track_time underflow
    if (note_start_time > now) {
      return;
    }

    while (next_note != score.end() && track_time >= next_note->first) {
      //   synth.StartInput(next_note->second);

      ++next_note;
    }
  }

  void loop() override {
    AddNewPrompts();
    MovePrompts();
    CleanDeadPrompts();

    PlayNotes();

    background.Draw(display);

    // Draw hit-line
    for (size_t x = 0; x < display->size.x; ++x) {
      display->Pixel(x, hit_line_height) = CRGB::White;
    }

    exploder.Draw(display);
    for (auto prompt : prompts) {
      prompt->Draw(display);
    }
  }
};

}  // namespace rhythm
}  // namespace games
}  // namespace kss
