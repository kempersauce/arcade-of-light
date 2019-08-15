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
          brightnessThreshold = brigtnessThreshold;
      }

      void draw(Display* display)
      {
          noiseGenerator->fillnoise8();
          for (int i = 0; i < display->numStrips; i++)
          {
              for (int j = 0; j < display->lengthStrips; j++)
              {
                  int brightness = noiseGenerator->noise[j][i];
                  if (brightness > brightnessThreshold)
                  {
                      // Draw the star, it's past the threshold

                      // stretch the brightness so it goes from 0-255
                      brightness = 255 * (brightness - brightnessThreshold) / (255 - brightnessThreshold);

                      // draw onto the blackness of space
                      display->strips[i][j].setRGB(brightness, brightness, brightness); // we're just doing RGB for now, but I'd rather do a HSV fade from bright blue to bright red
                  }
                  else
                  {
                      //Draw the blackness of space
                      display->strips[i][j].setRGB(0, 0, 0);
                  }
              }
          }
      }
  };