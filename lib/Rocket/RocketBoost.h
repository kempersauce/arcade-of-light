#include <Animation.h>
#include <NoiseGenerator.h>

class RocketBoost : Animation {
 private:
  NoiseGenerator* noiseGenerator;

 public:
  int loc;
  int height;
  float boostFactor;

  RocketBoost(int heightMax) {
    height = heightMax;
    loc = 0;
    boostFactor = 0;
    noiseGenerator = new NoiseGenerator(1, heightMax);  // 1-d noise generator
    noiseGenerator->speed = 100;                        // make it fast whoosh
  }

  // override rainbow draw function
  void draw(Display* display) {
    noiseGenerator->fillnoise8();

    // normalize boostFactor to 0-1 range
    if (boostFactor > 1) {
      boostFactor = 1;
    }

    // Draw as much boost as we needs
    int boostHeight = boostFactor * height;

    // At least keep it to 1 pixel minimum when we're actually boosting
    if (boostFactor > 0 && boostHeight < 1) {
      boostHeight = 1;
    }

    int middleStrip = display->numStrips / 2;
    for (int i = max(loc - boostHeight, 0); i < min(loc, display->lengthStrips);
         i++) {
      display->strips[middleStrip][i].setRGB(
          255, noiseGenerator->noise[0][loc - i], 0);
    }
  }
};
