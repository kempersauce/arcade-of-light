#pragma once

#include "animation/animation.h"    // for Animation
#include "animation/explosion.h"    // for Explosion
#include "controls/button.h"        // for Button
#include "engines/noise.h"          // for NoiseGenerator
#include "engines/random.h"         // for random::*
#include "games/head2head/audio.h"  // for H2HAudio
#include "games/head2head/dot.h"    // for H2HDot
#include "games/head2head/zone.h"   // for H2HZone

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
  animation::Explosion dropExplosion;

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

  int stripIndex;  // Which strip is this on?
  int heightMax;   // length of this strip

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

  std::shared_ptr<controls::Button> buttonA;
  std::shared_ptr<controls::Button> buttonB;

  engines::NoiseGenerator*
      noise_generator;  // this is maintained by the game class so we
                        // just need to hold onto the reference here

  H2HGameStrip(int stripIndex, int stripHeight,
               std::shared_ptr<controls::Button> a,
               std::shared_ptr<controls::Button> b,
               engines::NoiseGenerator* noise)
      : Animation(),
        dot(CRGB::White, stripIndex),
        explosion(50),
        dropExplosion(8),
        zoneA(CRGB::Green, stripIndex, 0, 22, false),
        zoneB(CRGB::Yellow, stripIndex, stripHeight - 23, stripHeight - 1,
              true),
        buttonA{std::move(a)},
        buttonB{std::move(b)},
        noise_generator{noise} {
    this->stripIndex = stripIndex;
    heightMax = stripHeight;

    dropExplosion.SaturationFinal = 0;  // Gotta keep 'em desaturated
    dropExplosion.saturationPhaseMillis =
        150;  // hold saturation for a quarter second before fading away
    dropExplosion.brightnessPhaseMillis = 200;  // quick little explosion
    dropExplosion.SetFriction(20, 2);
    dropExplosion.explosionMagnitude = 50;

    // Set some physics on the explosion shrapnel so they'll bounce off the
    // ceiling and floor
    for (size_t i = 0; i < explosion.shrapnel.size(); i++) {
      explosion.shrapnel[i].LocationMax = stripHeight;
      explosion.shrapnel[i].BounceFactor = -.8;
    }
    explosion.SetFriction(10, 3);

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
    dot.physics.Location = midBar;

    // randomly start in different directions
    if (engines::random::Bool()) {
      dot.setVelocity(20);
    } else {
      dot.setVelocity(-20);
    }

    dropExplosion.ExplodeAt(stripIndex, midBar);
  }

  void enterWinningStateA() {
    stripState = H2HStripWinningA;

    explosion.Hue = zoneAHue;
    explosion.ExplodeAt(stripIndex, dot.physics.Location);
    // TODO set this elsewhere once we have an animation for it
    midBar += 12;

    if (midBar > zoneBStart) {
      enterTotalWinAState();
    }
  }

  void enterWinningStateB() {
    stripState = H2HStripWinningB;

    explosion.Hue = zoneBHue;
    explosion.ExplodeAt(stripIndex, dot.physics.Location);
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
        millis() + engines::random::Int32(deadStateTimeoutMinMillis,
                                          deadStateTimeoutMaxMillis);
  }

  void enterDroppingState() {
    stripState = H2HStripDropping;

    // Plan for when the ball actually drops
    stateTimeoutMillis = millis() + droppingStateTimeoutMillis;
  }

  void enterTotalWinAState() {
    stripState = H2HStripTotalWinA;
    stateTimeoutMillis = millis();
  }

  void enterTotalWinBState() {
    stripState = H2HStripTotalWinB;
    stateTimeoutMillis = millis();
  }

  void checkGameState(H2HAudio& audio) {
    switch (stripState) {
      case H2HStripPlaying:

        // Did team A just win this one?
        if (dot.physics.Location >= heightMax) {
          audio.playTeamAWinLane();
          enterWinningStateA();
        }

        // Did team B just win this one?
        else if (dot.physics.Location <= 0) {
          audio.playTeamBWinLane();
          enterWinningStateB();
        }

        else {
          // Team A hits the button
          if (buttonA->IsDepressing()) {
            if (zoneA.checkZone(dot.physics.Location)) {
              audio.playTeamAHit();
              dot.setVelocity(-1 * (dot.physics.Velocity) +
                              (zoneA.zoneDepth(dot.physics.Location) *
                               10));  // 20 to 40 px/sec
            } else {
              audio.playTeamAMiss();
            }
          }

          // Team B hits the button
          if (buttonB->IsDepressing()) {
            // TODO wtf is this for?
            digitalWriteFast(9, HIGH);
            delay(1);
            digitalWriteFast(9, LOW);
            if (zoneB.checkZone(dot.physics.Location)) {
              audio.playTeamBHit();
              dot.setVelocity(-1 * (dot.physics.Velocity) -
                              (zoneB.zoneDepth(dot.physics.Location) *
                               10));  // -20 to -40 px/sec
            } else {
              audio.playTeamBMiss();
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
        if (millis() > stateTimeoutMillis) {
          enterDroppingState();
        }
        break;

      case H2HStripDropping:
        if (millis() <= stateTimeoutMillis) {
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
    for (int y = 0; y < min(midBar, display->strip_length); y++) {
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
        (millis() - stateTimeoutMillis) % 2000;  // loop thrugh 2 seconds
    const float waveWidth = 10;
    drawBackgroundA(display);
    if (timeDiff < 1000) {
      float distance = (float)display->strip_length * (float)timeDiff / 1000;
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
        (millis() - stateTimeoutMillis) % 2000;  // loop thrugh 2 seconds
    const float waveWidth = 10;
    drawBackgroundB(display);
    if (timeDiff < 1000) {
      float distance =
          (float)display->strip_length * (float)(1000 - timeDiff) / 1000;
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
