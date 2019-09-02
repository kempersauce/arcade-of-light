#pragma once
#include <Animation.h>
#include <Font.h>

//This file holds words and word functions
class Marquee : public Animation
{
    private:
      int Hue = 0;
      int Saturation = 255;
      int Brightness = 255;
      int MarqueeSpeed = 5;
      int YLocation = 0;
      int Word[5][8][4];
      int Letters;

      int LetterWidth = 4;
      int LetterHeight = 8;

      //list of words to display
      //int WordWinner[6][8][4] = {{LetterW},{LetterI},{LetterN},{LetterN},{LetterE,LetterR}};
      //int WordLoser[5][8][4] = {LetterL,LetterO,LetterS,LetterE,LetterR};
      //int WordReady[5][8][4] = {LetterR,LetterE,LetterA,LetterD,LetterY};
      int WordStart[5][8][4] = {{{LetterS},{LetterT},{LetterA},{LetterR},{LetterT}}};
      //int WordGame[4][8][4] = {LetterG,LetterA,LetterM,LetterE};
      //int WordOver[4][8][4] = {LetterO,LetterV,LetterE,LetterR};
      //int WordYeet[4][8][4] = {LetterY,LetterE,LetterE,LetterT};
      //int WordArcade[6][8][4] = {LetterA,LetterR,LetterC,LetterA,LetterD,LetterE};
      //int WordOf[2][8][4] = {LetterO,LetterF};
      //int WordLight[5][8][4] = {LetterL,LetterI,LetterG,LetterH,LetterT};

    public:
      //Initialize a word
      Marquee(int word, int hue, int speed, int location) : Animation()
      {
          //lookup characters from font file
        for (int i = 0; i < Letters; i++)
        {
          for (int j = 0; j < LetterHeight; j++)
          {
            for (int k = 0; k < LetterWidth; k++)
            {
              Word[i][j][k] = WordStart[i][j][k];//Brian!! idk how to do lookup tables
            }
          }
        }
          //lookup number of letters based on entered word
          Letters = 5;//Brian!! idk how to do lookup tables
          Hue = hue;
          MarqueeSpeed = speed;
          YLocation = location;
      }

      //Need to add spaces somehow
      void draw(Display* display)
      {
        // for (int i = 0; i < display->numStrips; i++)
        //   {
        //     for (int j = YLocation; j < display->lengthStrips; j++)
        //     {
        int StripX;
        int StripY;
        for (int i = 0; i < Letters; i++)
          {
            for (int j = 0; j < LetterHeight; j++)
            {
              for (int k = 0; k < LetterWidth; k++)
              {
                if(Word[i][j][k] == 1)
                {
                  StripX = j + 1;
                  StripY = YLocation * 8;
                    if (StripX < display->numStrips || StripX > 0 || StripY < display->numStrips || StripY > 0);
                    display->strips[StripX][StripY] = CHSV(Hue, Saturation, Brightness);
                }
              }
            }
          }
          YLocation += MarqueeSpeed;
        }
  };
