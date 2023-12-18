#pragma once

#include "animation/animation.h"                 // for Animation
#include "animation/explosion.h"                 // for Explosion
#include "controls/button.h"                     // for Button
#include "games/head2head/audio.h"               // for H2HAudio
#include "games/head2head/dot.h"                 // for H2HDot
#include "games/head2head/h2h_instructo_game.h"  // for H2HInstructoGame
#include "games/head2head/zone.h"                // for H2HZone
#include "math/random.h"                         // for random::*
#include "time/now.h"                            // for Now

namespace kss {
namespace games {
namespace h2h {

enum H2HStripState {
  H2HStripPlaying,
  H2HStripWinningA,
  H2HStripWinningB,
  H2HStripDead,
  H2HStripDropping,
  H2HStripTotalWinA,
  H2HStripTotalWinB
};

  float hitVelocityMultiplierBase = 10; // ajdust multiplier for hit velocity increase
  float hitVelocityMultiplierHeinz = 15; // ajdust multiplier for hit velocity increase
  const float heinzRedZone = 0.666;

class H2HGameStrip : public animation::Animation {
  H2HInstructoGame* const instructo_a;
  H2HInstructoGame* const instructo_b;

  H2HDot dot;

  // explode when dot hits wall (boom)
  animation::Explosion explosion;

  // Explode the ball out of the gate
  animation::Explosion dropExplosion;

  // nearside team
  H2HZone zoneA;
  static int zoneAStart;
  const uint8_t zoneAHue;

  // farside team
  H2HZone zoneB;
  static int zoneBStart;
  const uint8_t zoneBHue;

  const size_t stripIndex;  // Which strip is this on?
  const size_t heightMax;   // length of this strip

  uint32_t
      stateTimeoutMillis;  // state timer used to time a handful of game states
  const uint32_t deadStateTimeoutMinMillis =
      1000 * .5;  // 1/2 seconds minimum before dropping a new ball
  const uint32_t deadStateTimeoutMaxMillis =
      1000 * 5;  // 5 seconds max before dropping a new ball

  const uint32_t droppingStateTimeoutMillis =
      1000 * 3;  // 2 seconds of flashing before ball drop

  const uint32_t totalWinStateTimeoutMillis =
      1000 * 3;  // loop total win animation for 3 seconds


 public:
  H2HStripState stripState;

  // static because they all share the same mid bar
  static int midBar;

  controls::Button* buttonA;
  controls::Button* buttonB;

  H2HGameStrip(size_t stripIndex, size_t stripHeight, controls::Button* a,
               controls::Button* b, uint8_t zoneAHue, uint8_t zoneBHue, CRGB arc_color,
               H2HInstructoGame* instructo_a, H2HInstructoGame* instructo_b)
      : Animation(),
        instructo_a{instructo_a},
        instructo_b{instructo_b},
        dot(CRGB::White, arc_color),
        zoneA(CRGB::White, stripIndex, 0, 22, false),
        zoneB(CRGB::White, stripIndex, stripHeight - 23, stripHeight - 1, true),
        buttonA{a},
        buttonB{b},
        dropExplosion{8, 150, 200, 50, 20, 2, 0, 0, 0, NULL},
        explosion{40, 1000, 500, 40, 18, 2, 0, 255, 0, NULL},
        zoneAHue{zoneAHue},
        zoneBHue{zoneBHue},
        stripIndex{stripIndex},
        heightMax{stripHeight} {
    // Set some physics on the explosion shrapnel so they'll bounce off the
    // ceiling and floor
    for (auto& shrap : explosion.shrapnel) {
      shrap.LocationMax = stripHeight;
      shrap.BounceFactor = -.8;
    }

    zoneAStart = zoneA.yMax;
    zoneBStart = zoneB.yMin;

    reset();
  }

  void reset() {
    // reset the mid bar
    midBar = heightMax /
             2;  // dont reset the shared mid when an individual strip wins

    enterDeadState();
  }

  void enterPlayingState() {
    stripState = H2HStripPlaying;
    dot.DropAt({stripIndex, midBar});

    dropExplosion.ExplodeAt(stripIndex, midBar);
  }

  void enterWinningStateA() {
    stripState = H2HStripWinningA;

    explosion.SetHue(zoneAHue);
    explosion.ExplodeAt(stripIndex, dot.physics.location.y);

    if (instructo_b != NULL) {
      // TODO make this be able to handle things other than 8
      uint8_t num_display_strips = 8;
      instructo_b->explosions.push_back(explosion);
      instructo_b->explosions.back().SetFriction({1, 4});
      instructo_b->ExplodeBack(num_display_strips - 1 - stripIndex);
    }

    // TODO set this elsewhere once we have an animation for it
    midBar += 12;

    if (midBar > zoneBStart) {
      enterTotalWinAState();
    }
  }

  void enterWinningStateB() {
    stripState = H2HStripWinningB;

    explosion.SetHue(zoneBHue);
    explosion.ExplodeAt(stripIndex, dot.physics.location.y);

    if (instructo_a != NULL) {
      instructo_a->explosions.push_back(explosion);
      instructo_a->explosions.back().SetFriction({1, 4});
      instructo_a->ExplodeBack(stripIndex);
    }

    // TODO set this elsewhere once we have an animation for it
    midBar -= 12;

    if (midBar < zoneAStart) {
      enterTotalWinBState();
    }
  }

  void enterDeadState() {
    stripState = H2HStripDead;
    // Plan for when to start dropping a new ball
    stateTimeoutMillis =
        time::Now() + math::random::Int16(deadStateTimeoutMinMillis,
                                          deadStateTimeoutMaxMillis);
  }

  void enterDroppingState() {
    stripState = H2HStripDropping;

    // Plan for when the ball actually drops
    stateTimeoutMillis = time::Now() + droppingStateTimeoutMillis;
  }

  void enterTotalWinAState() {
    stripState = H2HStripTotalWinA;
    stateTimeoutMillis = time::Now();
  }

  void enterTotalWinBState() {
    stripState = H2HStripTotalWinB;
    stateTimeoutMillis = time::Now();
  }

  void checkGameState(H2HAudio& audioA, H2HAudio& audioB) {
    // Debug("Checking game state on strip " + stripIndex);
    // Debug_var(stripState);
    switch (stripState) {
      case H2HStripPlaying:

        // Did team A just win this one?
        if (dot.physics.location.y >= heightMax) {
          //   Debug("Team A wins strip " + stripIndex);
          audioA.playTeamAWinLane();
          audioB.playTeamAWinLane();
          enterWinningStateA();
        }

        // Did team B just win this one?
        else if (dot.physics.location.y <= 0) {
          //   Debug("Team B wins strip " + stripIndex);
          audioA.playTeamBWinLane();
          audioB.playTeamBWinLane();
          enterWinningStateB();
        }

        else {
          // Team A hits the button
          if (buttonA->IsDepressing()) {
            Debug("Team A hits button on strip " + stripIndex);
            if (zoneA.checkZone(dot.physics.location.y)) {
              audioA.playTeamAHit();
              float depth = zoneA.zoneDepth(dot.physics.location.y);
              float sauce = hitVelocityMultiplierBase * depth;
              if(depth > heinzRedZone) {
                sauce = hitVelocityMultiplierHeinz * depth;
              }
              dot.setVelocity(-1 * (dot.physics.velocity.y) + sauce);  // 2 to 4 times multiplier px/sec
            } else {
              audioA.playTeamAMiss();
            }
          }

          // Team B hits the button
          if (buttonB->IsDepressing()) {
            Debug("Team B hits button on strip" + stripIndex);
            if (zoneB.checkZone(dot.physics.location.y)) {
              audioB.playTeamBHit();
              float depth = zoneB.zoneDepth(dot.physics.location.y);
              float sauce = hitVelocityMultiplierBase * depth;
              if(depth > heinzRedZone) {
                sauce = hitVelocityMultiplierHeinz * depth;
              }
              dot.setVelocity(-1 * (dot.physics.velocity.y) - sauce);  // -2 to -4 times multiplier px/sec
            } else {
              audioB.playTeamBMiss();
            }
          }

          // dot moves either way
          dot.Move();

          // play out the residual drop explosion
          dropExplosion.Move();
        }
        break;

      case H2HStripWinningA:
        explosion.Move();
        if (explosion.IsBurnedOut()) {
          // for now immediately go into dead state
          enterDeadState();
        }
        break;

      case H2HStripWinningB:
        explosion.Move();
        if (explosion.IsBurnedOut()) {
          // for now immediately go into dead state
          enterDeadState();
        }
        break;

      case H2HStripDead:
        if (time::Now() > stateTimeoutMillis) {
          enterDroppingState();
        }
        break;

      case H2HStripDropping:
        if (time::Now() <= stateTimeoutMillis) {
          if (dropExplosion.IsBurnedOut()) {
            dropExplosion.ExplodeAt(stripIndex, midBar);
          }
          dropExplosion.Move();
        } else {
          enterPlayingState();
        }
        break;

      case H2HStripTotalWinA:
        // play out residual explosions
        explosion.Move();
        dropExplosion.Move();
        // dot.Move();
        break;

      case H2HStripTotalWinB:
        // play out residual explosions
        explosion.Move();
        dropExplosion.Move();
        // dot.Move();
        break;
    }
  }

  void Draw(display::Display* display) {
    // Debug("Drawing strip" + stripIndex);
    switch (stripState) {
      case H2HStripPlaying:
        drawZones(display);
        drawMidBar(display);
        // explosion.Draw(display);
        dropExplosion.Draw(display);  // play out the last residual explosion
        dot.Draw(display);
        break;

      case H2HStripWinningA:
      case H2HStripWinningB:
        drawZones(display);
        drawMidBar(display);
        explosion.Draw(display);
        // dropExplosion.Draw(display);
        // dot.Draw(display);
        break;

      case H2HStripDead:
        drawZones(display);
        drawMidBar(display);
        // explosion.Draw(display);
        // dropExplosion.Draw(display);
        // dot.Draw(display);
        break;

      case H2HStripDropping:
        drawZones(display);
        drawMidBar(display);
        // explosion.Draw(display);
        dropExplosion.Draw(display);
        // dot.Draw(display);
        break;

      case H2HStripTotalWinA:
        // drawZones(display);
        // drawMidBar(display);
        explosion.Draw(display);
        dropExplosion.Draw(display);
        // dot.Draw(display);
        drawWinA(display);
        break;

      case H2HStripTotalWinB:
        // drawZones(display);
        // drawMidBar(display);
        explosion.Draw(display);
        dropExplosion.Draw(display);
        // dot.Draw(display);
        drawWinB(display);
        break;
    }
  }

  void drawZones(display::Display* display) {
    zoneA.Draw(display);
    zoneB.Draw(display);
  }

  void drawMidBar(display::Display* display) {
    // display->Pixel(stripIndex, midBar) = CRGB::White;
  }

  void drawWinA(display::Display* display) {
    CRGB teamAColor = CHSV(zoneAHue, 255, 255);
    const uint32_t timeDiff =
        (time::Now() - stateTimeoutMillis) % 2000;  // loop thrugh 2 seconds
    const static float wave_width = 10;
    const static float half_wave_width = wave_width / 2;
    if (timeDiff < 1000) {
      float distance = (float)display->size.y * (float)timeDiff / 1000;
      for (int i = -half_wave_width; i < half_wave_width; i++) {
        float presence = (half_wave_width - abs(i)) / half_wave_width;
        display->BlendPixel(stripIndex, distance + i, teamAColor, presence);
      }
    }
  }

  void drawWinB(display::Display* display) {
    CRGB teamBColor = CHSV(zoneBHue, 255, 255);
    const uint32_t timeDiff =
        (time::Now() - stateTimeoutMillis) % 2000;  // loop thrugh 2 seconds
    const static float wave_width = 10;
    const static float half_wave_width = wave_width / 2;
    if (timeDiff < 1000) {
      float distance = (float)display->size.y * (float)(1000 - timeDiff) / 1000;
      for (int i = -half_wave_width; i < half_wave_width; i++) {
        float presence = (half_wave_width - abs(i)) / half_wave_width;
        display->BlendPixel(stripIndex, distance + i, teamBColor, presence);
      }
    }
  }
};

int H2HGameStrip::midBar;
int H2HGameStrip::zoneAStart;
int H2HGameStrip::zoneBStart;

}  // namespace h2h
}  // namespace games
}  // namespace kss
