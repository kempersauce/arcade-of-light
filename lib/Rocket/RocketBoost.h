#include <Animation.h>
#include <NoiseGenerator.h>

class RocketBoost : Animation
{
private:
    NoiseGenerator* noiseGenerator;

    public:
      int loc = 0;
      int height;
      float boostFactor = 0;

      RocketBoost(int heigt)
      {
          height = heigt;
          noiseGenerator = new NoiseGenerator(1, height); // 1-d noise generator
      }

      //override rainbow draw function
      void draw(Display* display)
      {
          noiseGenerator->fillnoise8();

          // Always draw the first pixel if we're boosting at all for instant response
          if (boostFactor > 0)
          {
              display->strips[display->numStrips/2][loc].setRGB(255, 128 + noiseGenerator->noise[0][0] / 2, 128);
          }

          // Draw as much boost as we needs
          int boostHeight = boostFactor * height;
          int middleStrip = display->numStrips / 2;
          for (int i = 0; i < boostHeight; i++)
          {
              int boostLoc = i + loc;
              
              // Dont paint outside the canvas
              if (boostLoc >= 0 && boostLoc < display->numStrips)
              {
                  display->strips[middleStrip][boostLoc].setRGB(255, 128 + noiseGenerator->noise[0][i] / 2, 128);
              }
          }
      }
};
