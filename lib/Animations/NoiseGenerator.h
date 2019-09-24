#pragma once

class NoiseGenerator
{
    public:
      NoiseGenerator(int widt, int heigt)
      {
          width = widt;
          height = heigt;

          noise = new uint8_t*[width];
          for (int i = 0; i < height; i++)
          {
            noise[i] = new uint8_t[width];
          }

          // Initialize our coordinates to some random values
          x = random16();
          y = random16();
          z = random16();
      }

      int width;
      int height;

      // uint16_t speed = 1; // almost looks like a painting, moves very slowly
      uint16_t speed = 20; // a nice starting speed, mixes well with a scale of 100
      // uint16_t speed = 33;
      // uint16_t speed = 100; // wicked fast!

      // Scale determines how far apart the pixels in our noise matrix are.  Try
      // changing these values around to see how it affects the motion of the display.  The
      // higher the value of scale, the more "zoomed out" the noise iwll be.  A value
      // of 1 will be so zoomed in, you'll mostly see solid colors.

      // uint16_t scale = 1; // mostly just solid colors
      // uint16_t scale = 4011; // very zoomed out and shimmery
      uint16_t scale = 1024;

      // This is the array that we keep our computed noise values in
      uint8_t** noise;

      // Fill the x/y array of 8-bit noise values using the inoise8 function.
      void fillnoise8()
      {
          for (int i = 0; i < width; i++)
          {
              int ioffset = scale * i;
              for (int j = 0; j < height; j++)
              {
                  int joffset = scale * j;
                  noise[i][j] = inoise8(x + ioffset, y + joffset, z);
              }
          }
          z += speed;
      }

      // We're using the x/y dimensions to map to the x/y pixels on the matrix.  We'll
      // use the z-axis for "time".  speed determines how fast time moves forward.  Try
      // 1 for a very slow moving effect, or 60 for something that ends up looking like
      // water.
      // Set these to the middle of their ranges so we can shift the noise window around seamlessly
      uint16_t x = UINT16_MAX / 2;
      uint16_t y = UINT16_MAX / 2;
      uint16_t z = UINT16_MAX / 2;
  };
