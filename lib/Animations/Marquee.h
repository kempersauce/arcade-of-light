#pragma once
#include <Animation.h>
#include <fonts.h>

//This file holds words and word functions
class Marquee : Animation
{
    private:
      int Hue = 0;
      int Saturation = 255;
      int Brightness = 255;
      int MarqueeSpeed = 5;
      int YLocation = 0;
      int Word[null][null][null];
      int Letters;

      //list of words to display
      int WordWinner[6][4][8] = {_W,_I,_N,_N,_E,_R};
      int WordLoser[5][4][8] = {_L,_O,_S,_E,_R};
      int WordReady[5][4][8] = {_R,_E,_A,_D,_Y};
      int WordStart[5][4][8] = {_S,_T,_A,_R,_T};
      int WordGame[4][4][8] = {_G,_A,_M,_E};
      int WordOver[4][4][8] = {_O,_V,_E,_R};
      int WordYeet[4][4][8] = {_Y,_E,_E,_T};
      int WordArcade[6][4][8] = {_A,_R,_C,_A,_D,_E};
      int WordOf[2][4][8] = {_O,_F};
      int WordLight[5][4][8] = {_L,_I,_G,_H,_T};

      const struct map
      {
        char *str;
        int num[4][8];
      } myMap[] = {
        {"winner",WordWinner},
        {"loser",WordLoser},
        {"yeet",WordYeet},
      }

    public:
      //Initialize a word
      Marquee(string word, int hue, int speed, int location) : Animation()
      {
          //lookup characters from font file
          Word = ;//Brian!! idk how to do lookup tables
          //lookup number of letters based on entered word
          Letters = ;//Brian!! idk how to do lookup tables
          Hue = hue;
          MarqueeSpeed = speed;
          YLocation = location;
      }

      //Need to add spaces somehow
      void draw(Display* display)
      {
        for (int i = 0; i < display->numStrips; i++)
          {
            for (int j = YLocation; j < display->lengthStrips; j++)
            {
              if(Word[Letters][i][j] == 1)
              {
              display->strips[i][j] = CHSV(Hue, Saturation, Brightness);
              }
            }
          }
          YLocation += MarqueeSpeed;
        }
  };
