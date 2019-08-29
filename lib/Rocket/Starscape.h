#pragma once
#include <NoiseGenerator.h>

class Starscape : Animation
{
    private:
      NoiseGenerator* noiseGenerator;

      int brightnessThreshold;

    public:
      Starscape(int width, int height, int brigtnessThreshold) : Animation()
      {
          noiseGenerator = new NoiseGenerator(width, height);
          noiseGenerator->speed = 10; // slow down the speed here, we want slow blinking stars
          brightnessThreshold = brigtnessThreshold;
      }

      void draw(Display* display)
      {
          noiseGenerator->fillnoise8();

          for (int i = 0; i < display->numStrips; i++)
          {
              for (int j = 0; j < display->lengthStrips; j++)
              {
                  int brightness = noiseGenerator->noise[i][j];
                  if (brightness > brightnessThreshold)
                  {
                      // Draw the star, it's past the threshold

                      // stretch the brightness so it goes from 0-100 for CSV
                      int value = 255 * (brightness - brightnessThreshold) / (255 - brightnessThreshold);

                      // draw onto the blackness of space
                      display->strips[i][j] = CHSV(46, value, value); // Amber is 46, 100, 100 - we scale from black up to amber here
                  }
                  else
                  {
                      // Draw the blackness of space
                      display->strips[i][j] = CRGB(0, 0, 0);
                  }
              }
          }
      }
  };
