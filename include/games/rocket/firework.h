#include "audio/rocket_audio.h"  // for RocketAudio

#include "animation/animation.h"  // for Animation
#include "animation/explosion.h"  // for Explosion

class Firework : Animation {
  // Used to randomly select the strip and explosion height when resetting the
  // firework
  int stripsHeight;
  int stripsWidth;

 public:
  // Physics for the fireworks "rocket"
  PhysicsInfo physics;

  // Fireworks explosion
  Explosion explosion;

  // color for the firework rocket
  int Hue;

  bool isPlaying;

  /**
   * Firework Constructor
   * @param stripLength - location on LED strip
   * */
  Firework(int stripLength, int numStrips)
      : Animation(), physics(), explosion(50) {
    stripsHeight = stripLength;
    stripsWidth = numStrips;

    Reset();
    isPlaying = false;
  }

  void Reset() {
    isPlaying = true;
    physics.Reset();
    physics.LocationMax = random(
        stripsHeight / 3, stripsHeight - 20);  // height the firework explodes
    physics.Velocity = random(35, 75);         // how fast do we get there

    physics.xLocation =
        random(0, stripsWidth);  // select which strip this should be on

    Hue = random(0, 255);
  }

  void Move(RocketAudio* audio) {
    bool wasExploded = physics.HasExploded;  // edge was set with LocationMax to
                                             // denote the explode height

    physics.Move();

    // Explode when we get to the designated height
    if (physics.HasExploded) {
      if (wasExploded == false) {
        audio->playFireWorkExplode();
        explosion.Hue = random(0, 255);
        explosion.ExplodeAt(physics.xLocation, physics.Location);
      }

      explosion.Move();

      if (explosion.IsBurnedOut()) {
        isPlaying = false;
      }
    }
  }

  void draw(Display* display) {
    if (physics.HasExploded) {
      explosion.draw(display);
    } else {
      int Saturation = min(255 * (physics.Location / physics.LocationMax), 255);
      CRGB color;
      color.setHSV(Hue, Saturation, 255);
      display->ditherPixel((int)physics.xLocation, (int)physics.Location,
                           &color);
    }
  }
};
