#include <Animation.h>
#include <NoiseGenerator.h>

class RocketBoost : Animation
{
private:
    NoiseGenerator* noiseGenerator;

    public:
      int loc;
      int height;
      float boostFactor;

      RocketBoost(int heigt)
      {
          height = heigt;
          loc = 0;
          boostFactor = 0;
          noiseGenerator = new NoiseGenerator(1, height); // 1-d noise generator
      }

      //override rainbow draw function
      void draw(Display* display)
      {
          noiseGenerator->fillnoise8();

          // normalize boostFactor to 0-1 range
          if (boostFactor > 1)
          {
              boostFactor = 1;
          }

          // Draw as much boost as we needs
          int boostHeight = boostFactor * height;

          // At least keep it to 2 pixels minimum when we're actually boosting
          if (boostFactor > 0 && boostHeight < 1)
          {
              boostHeight = 1;
          }

          int middleStrip = display->numStrips / 2;
          for (int boostLoc = loc - boostHeight; boostLoc < loc; boostLoc++)
          {
              // Dont paint outside the canvas
              if (boostLoc >= 0 && boostLoc < display->lengthStrips)
              {
                  int noiseIndex = loc - boostLoc;
                  display->strips[middleStrip][boostLoc].setRGB(255, noiseGenerator->noise[0][noiseIndex] / 2, 0);
              }
          }
      }
};
