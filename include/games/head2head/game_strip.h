#pragma once

#include "animation/animation.h"    // for Animation
#include "animation/explosion.h"    // for Explosion
#include "controls/button.h"        // for Button
#include "engines/noise.h"          // for NoiseGenerator
#include "games/head2head/audio.h"  // for H2HAudio
#include "games/head2head/dot.h"    // for H2HDot
#include "games/head2head/zone.h"   // for H2HZone
#include "math/random.h"            // for random::*
#include "time/now.h"               // for Now

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

class H2HGameStrip : public animation::Animation {
  H2HDot dot;

  // explode when dot hits wall (boom)
  animation::Explosion explosion;

  // Explode the ball out of the gate
  //   animation::Explosion dropExplosion;

  // nearside team
  H2HZone zoneA;
  static int zoneAStart;
  // static const int zoneAHue = 138; // cyan
  static const int zoneAHue = 120;  // green

  // farside team
  H2HZone zoneB;
  static int zoneBStart;
  // static const int zoneBHue = 0; // red
  static const int zoneBHue = 33;  // orange - this is wrong

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

  engines::NoiseGenerator*
      noise_generator;  // this is maintained by the game class so we
                        // just need to hold onto the reference here

  H2HGameStrip(size_t stripIndex, size_t stripHeight, controls::Button* a,
               controls::Button* b, engines::NoiseGenerator* noise)
      : Animation(),
        dot(CRGB::White, stripIndex),
        zoneA(CRGB::Green, stripIndex, 0, 22, false),
        zoneB(CRGB::Yellow, stripIndex, stripHeight - 23, stripHeight - 1,
              true),
        buttonA{a},
        buttonB{b},
        noise_generator{noise},
        dropExplosion{8, 150, 200, 50, 20, 2, 0, 0, 0, NULL},
        explosion{50, 1000, 1500, 20, 10, 3, 0, 255, 0, NULL},
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
    dot.physics.Reset();
    dot.physics.location = {stripIndex, midBar};

    // randomly start in different directions
    if (math::random::Bool()) {
      dot.setVelocity(20);
    } else {
      dot.setVelocity(-20);
    }

    dropExplosion.ExplodeAt(stripIndex, midBar);
  }

  void enterWinningStateA() {
    stripState = H2HStripWinningA;

    explosion.SetHue(zoneAHue);
    explosion.ExplodeAt(stripIndex, dot.physics.location.y);
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

  void checkGameState(H2HAudio& audio) {
    // Debug("Checking game state on strip " + stripIndex);
    Debug_var(stripState);
    switch (stripState) {
      case H2HStripPlaying:

        // Did team A just win this one?
        if (dot.physics.location.y >= heightMax) {
          Debug("Team A wins strip " + stripIndex);
          audio.playTeamAWinLane();
          enterWinningStateA();
        }

        // Did team B just win this one?
        else if (dot.physics.location.y <= 0) {
          Debug("Team B wins strip " + stripIndex);
          audio.playTeamBWinLane();
          enterWinningStateB();
        }

        else {
          // Team A hits the button
          if (buttonA->IsDepressing()) {
            Debug("Team A hits button on strip" + stripIndex);
            if (zoneA.checkZone(dot.physics.location.y)) {
              audio.playTeamAHit();
              dot.setVelocity(-1 * (dot.physics.velocity.y) +
                              (zoneA.zoneDepth(dot.physics.location.y) *
                               10));  // 20 to 40 px/sec
            } else {
              audio.playTeamAMiss();
            }
          }

          // Team B hits the button
          if (buttonB->IsDepressing()) {
            Debug("Team B hits button on strip" + stripIndex);
            if (zoneB.checkZone(dot.physics.location.y)) {
              audio.playTeamBHit();
              dot.setVelocity(-1 * (dot.physics.velocity.y) -
                              (zoneB.zoneDepth(dot.physics.location.y) *
                               10));  // -20 to -40 px/sec
            } else {
              audio.playTeamBMiss();
            }
          }

          // dot moves either way
          Debug("Dot moves on strip" + stripIndex);
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
        dot.Move();
        break;

      case H2HStripTotalWinB:
        // play out residual explosions
        explosion.Move();
        dropExplosion.Move();
        dot.Move();
        break;
    }
  }

  void draw(display::Display* display) {
    // Debug("Drawing strip" + stripIndex);
    switch (stripState) {
      case H2HStripPlaying:
        drawBackgrounds(display);
        drawZones(display);
        drawMidBar(display);
        // explosion.draw(display);
        dropExplosion.draw(display);  // play out the last residual explosion
        dot.draw(display);
        break;

      case H2HStripWinningA:
      case H2HStripWinningB:
        drawBackgrounds(display);
        drawZones(display);
        drawMidBar(display);
        explosion.draw(display);
        // dropExplosion.draw(display);
        // dot.draw(display);
        break;

      case H2HStripDead:
        drawBackgrounds(display);
        drawZones(display);
        drawMidBar(display);
        // explosion.draw(display);
        // dropExplosion.draw(display);
        // dot.draw(display);
        break;

      case H2HStripDropping:
        drawBackgrounds(display);
        drawZones(display);
        drawMidBar(display);
        // explosion.draw(display);
        dropExplosion.draw(display);
        // dot.draw(display);
        break;

      case H2HStripTotalWinA:
        drawBackgrounds(display);
        // drawZones(display);
        drawMidBar(display);
        explosion.draw(display);
        dropExplosion.draw(display);
        dot.draw(display);
        drawWinA(display);
        break;

      case H2HStripTotalWinB:
        drawBackgrounds(display);
        // drawZones(display);
        drawMidBar(display);
        explosion.draw(display);
        dropExplosion.draw(display);
        dot.draw(display);
        drawWinB(display);
        break;
    }
  }

  void drawBackgrounds(display::Display* display) {
    // Team A background
    drawBackgroundA(display);

    // Team B background
    drawBackgroundB(display);
  }

  void drawBackgroundA(display::Display* display) {
    for (int y = 0; y < min(midBar, display->size.y); y++) {
      display->Pixel(stripIndex, y)
          .setHSV(zoneAHue, 255,
                  noise_generator->data[stripIndex][y]);  // blue team
    }
  }

  void drawBackgroundB(display::Display* display) {
    for (int y = max(midBar, 0); y < heightMax; y++) {
      display->Pixel(stripIndex, y)
          .setHSV(zoneBHue, 255,
                  noise_generator->data[stripIndex][y]);  // red team
    }
  }

  void drawZones(display::Display* display) {
    zoneA.draw(display);
    zoneB.draw(display);
  }

  void drawMidBar(display::Display* display) {
    // display->Pixel(stripIndex, midBar) = CRGB::White;
  }

  void drawWinA(display::Display* display) {
    CRGB teamAColor;
    teamAColor.setHSV(zoneAHue, 255, 255);
    const uint32_t timeDiff =
        (time::Now() - stateTimeoutMillis) % 2000;  // loop thrugh 2 seconds
    const float waveWidth = 10;
    drawBackgroundA(display);
    if (timeDiff < 1000) {
      float distance = (float)display->size.y * (float)timeDiff / 1000;
      for (int i = waveWidth / -2; i < waveWidth / 2; i++) {
        float presence = (waveWidth / 2 - abs(i)) / (waveWidth / 2);
        display->BlendPixel(stripIndex, distance + i, &teamAColor, presence);
      }
    }
  }

  void drawWinB(display::Display* display) {
    CRGB teamBColor;
    teamBColor.setHSV(zoneBHue, 255, 255);
    const uint32_t timeDiff =
        (time::Now() - stateTimeoutMillis) % 2000;  // loop thrugh 2 seconds
    const float waveWidth = 10;
    drawBackgroundB(display);
    if (timeDiff < 1000) {
      float distance = (float)display->size.y * (float)(1000 - timeDiff) / 1000;
      for (int i = waveWidth / -2; i < waveWidth / 2; i++) {
        float presence = (waveWidth / 2 - abs(i)) / (waveWidth / 2);
        display->BlendPixel(stripIndex, distance + i, &teamBColor, presence);
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
