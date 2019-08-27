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
          noiseGenerator->speed = 200; // make it fast whoosh
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

          // At least keep it to 1 pixel minimum when we're actually boosting
          if (boostFactor > 0 && boostHeight < 1)
          {
              boostHeight = 1;
          }

          int middleStrip = display->numStrips / 2;
          for (int i = 0; i < boostHeight; i++)
          {
              int boostLoc = (loc - boostHeight) + i;

              // Dont paint outside the canvas
              if (boostLoc >= 0 && boostLoc < display->lengthStrips)
              {
                  display->strips[middleStrip][boostLoc].setRGB(255, noiseGenerator->noise[0][i], 0);
              }
          }
      }
};
