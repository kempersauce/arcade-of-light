#pragma once

#include <vector>  // for vector

#include "animation/animation.h"  // for Animation
#include "animation/arrow.h"      // for Arrow
#include "animation/exploder.h"   // for Exploder
#include "animation/explosion.h"  // for Explosion
#include "animation/starscape.h"  // for Starscape
#include "audio/score.h"          // for Score
#include "controls/dir_pad.h"     // for DirPad
#include "games/game.h"           // for Game
#include "serial/debug.h"         // for Debug

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
  const uint32_t arrow_lead_time{4000};

  // Music score
  audio::Score score;
  uint32_t start_time{0};
  audio::Score::const_iterator next_arrow;
  bool is_playing{false};

  // Sticks
  // controls::DirPad controller;

  // Sounds

  // Animations
  animation::Starscape background;
  std::vector<animation::Arrow*> arrows;
  animation::Exploder exploder;

 public:
  RhythmGameSingle(display::Display* display)
      : Game(display),
        background{display->size},
        exploder{
            kExploderPrototype, {display->size.x / 2, hit_line_height}, 50} {}

  ~RhythmGameSingle() {
    for (auto arrow : arrows) {
      delete arrow;
    }
  }

  void setup() override {
    audio::ScoreBuilder main_score{165, 32};
    main_score.SetBeatEveryMeasure(4, 1);
    main_score.SetBeatEveryMeasure(3, 2);
    main_score.SetBeatEveryMeasure(3, 2.5);
    main_score.SetBeatEveryMeasure(5, 3);
    main_score.SetBeatEveryMeasure(3, 4);
    score = main_score.GetScore();

    // THIS should be update - create track outside of here
    Debug_here();
    start_time = millis();
    next_arrow = score.cbegin();
    is_playing = true;
  }

  void AddNewArrows() {
    if (!is_playing) {
      return;
    }

    if (next_arrow == score.cend()) {
      is_playing = false;
      Debug("End of score reached. Done playing.");
      return;
    }

    const uint32_t now = millis();
    // TODO modify track_time to give this lead time
    const uint32_t track_time = now - start_time;
    while (next_arrow != score.cend() && track_time >= next_arrow->first) {
      // Play the note(s)
      const uint32_t arrow_target_time =
          start_time + next_arrow->first + arrow_lead_time;
      arrows.push_back(new animation::Arrow(
          display->size.y + 20, hit_line_height, arrow_target_time));

      Debug("Adding Arrow for note_t=" + next_arrow->first + " on ch" +
            next_arrow->second + " at actual_t=" + track_time +
            ", target_t=" + arrow_target_time);

      ++next_arrow;
    }
  }

  void MoveArrows() {
    for (auto arrow : arrows) {
      //   Debug("Moving arrow...");
      arrow->Move();
      if (arrow->GetY() <= hit_line_height) {
        exploder.Move();
      }
    }
  }

  void CleanDeadArrows() {
    // Remove dead Arrows
    for (auto it = arrows.begin(); it < arrows.end();) {
      if ((*it)->IsDone()) {
        // Debug("Deleting arrow...");
        delete *it;
        it = arrows.erase(it);
      } else {
        ++it;
      }
    }
  }

  void loop() override {
    AddNewArrows();
    MoveArrows();
    CleanDeadArrows();

    background.draw(display);

    // Draw hit-line
    for (size_t x = 0; x < display->size.x; ++x) {
      display->Pixel(x, hit_line_height) = CRGB::White;
    }

    exploder.draw(display);
    for (auto arrow : arrows) {
      arrow->draw(display);
    }
  }
};

}  // namespace rhythm
}  // namespace games
}  // namespace kss
