#pragma once
#include <NoiseGenerator.h>

class NoiseAnimation : Animation
{
    private:
      int brightness = 255;
      NoiseGenerator noiseGenerator;

    public:
      NoiseAnimation(int width, int height) : Animation(),
	  	noiseGenerator(width, height)
      {
      }

      void setBrightness(int bright)
      {
          brightness = bright;
      }

      void draw(Display* display)
      {
          static uint8_t ihue = 0;
          noiseGenerator.fillnoise8();
          for (int i = 0; i < display->numStrips; i++)
          {
              for (int j = 0; j < display->lengthStrips; j++)
              {
                  // We use the value at the (i,j) coordinate in the noise
                  // array for our brightness, and the flipped value from (j,i)
                  // for our pixel's hue.
                  //leds[i][j] = CHSV(noise[j][i],255,noise[i][j]);
                  display->strips[i][j] = CHSV(ihue + (noiseGenerator.noise[i][j] >> 2), brightness, noiseGenerator.noise[i][j]);
                  // You can also explore other ways to constrain the hue used, like below
                  // leds[XY(i,j)] = CHSV(ihue + (noise[j][i]>>2),255,noise[i][j]);
              }
          }

          ihue++;
      }
  };
