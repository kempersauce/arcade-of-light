#pragma once
#include <Animation.h>
#include <Font.h>
#include <Shapes.h>
#include <string>

using namespace std;

//This file holds words and word functions
class Marquee : public Animation
{
    private:
      int Hue = 0;
      int Saturation = 255;
      int Brightness = 255;
      int MarqueeSpeed = 1;
      int YLocation = 0;
      int Word[1][8][4];
      int Letters = 1;
      bool Stop = false;
      int StripX;
      int StripY;

      int LetterWidth = 4;
      int LetterHeight = 8;

      int test = 0;

      //list of words to display
      //int WordWinner[6][8][4] = {{LetterW},{LetterI},{LetterN},{LetterN},{LetterE,LetterR}};
      //int WordLoser[5][8][4] = {LetterL,LetterO,LetterS,LetterE,LetterR};
      //int WordReady[5][8][4] = {LetterR,LetterE,LetterA,LetterD,LetterY};
      //int WordStart[5][8][4] = {{{LetterS},{LetterT},{LetterA},{LetterR},{LetterT}}};
      //int WordGame[4][8][4] = {LetterG,LetterA,LetterM,LetterE};
      //int WordOver[4][8][4] = {LetterO,LetterV,LetterE,LetterR};
      //int WordYeet[4][8][4] = {LetterY,LetterE,LetterE,LetterT};
      //int WordArcade[6][8][4] = {LetterA,LetterR,LetterC,LetterA,LetterD,LetterE};
      //int WordOf[2][8][4] = {LetterO,LetterF};
      //int WordLight[5][8][4] = {LetterL,LetterI,LetterG,LetterH,LetterT};

    public:
      //Initialize a word
      Marquee(int speed) : Animation()
      {
        Letters = 1;//Brian!! idk how to do lookup tables

          //lookup characters from font file
        // for (int i = 0; i < Letters; i++)
        // {
        //   for (int j = 0; j < LetterHeight; j++)
        //   {
        //     for (int k = 0; k < LetterWidth; k++)
        //     {
        //       //if (word == "START")
        //       //{
        //         Word[i][j][k] = LetterA[j][k];//Brian!! idk how to do lookup tables
        //       //}
        //     }
        //   }
        // }
          //lookup number of letters based on entered word

          //Hue = hue;
          //MarqueeSpeed = speed;
          //YLocation = 120 + (Letters * LetterHeight) ;
      }

      //Need to add spaces somehow
      void draw(Display* display)
      {
        // for (int i = 0; i < display->numStrips; i++)
        //   {
        //     for (int j = YLocation; j < display->lengthStrips; j++)
        //     {

        //int testX = 0;
        //int testY = 0;
        //if(test == 0){
        //  test = 1;
        //  display->strips[testX][testY] = CRGB::Brown;
        //}else{
        //  test = 0;
        //  display->strips[testX][testY] = CRGB::BlueViolet;
        //}

        YLocation -= MarqueeSpeed;
        if (YLocation < 0){YLocation = display->lengthStrips;}


        int lowerX = 0;
        drawLetter(lowerX, (10 + YLocation) % display->lengthStrips, 3, display, LetterE, beatsin8(2), 255, 255);

        drawLetter(lowerX, (30 + YLocation) % display->lengthStrips, 3, display, LetterC, beatsin8(8), 255, 255);

        drawLetter(lowerX, (50 + YLocation) % display->lengthStrips, 3, display, LetterU, beatsin8(30), 255, 255);

        drawLetter(lowerX, (10 + YLocation) % display->lengthStrips, 3, display, LetterA, beatsin8(2), 255, 255);

        drawLetter(lowerX, (30 + YLocation) % display->lengthStrips, 3, display, LetterS, beatsin8(8), 255, 255);

        drawLetter(lowerX, (50 + YLocation) % display->lengthStrips, 3, display, LetterR, beatsin8(30), 255, 255);

        drawLetter(lowerX, (70 + YLocation) % display->lengthStrips, 3, display, LetterE, beatsin8(45), 255, 255);

        drawLetter(lowerX, (10 + YLocation) % display->lengthStrips, 3, display, LetterP, beatsin8(2), 255, 255);

        drawLetter(lowerX, (30 + YLocation) % display->lengthStrips, 3, display, LetterM, beatsin8(8), 255, 255);

        drawLetter(lowerX, (50 + YLocation) % display->lengthStrips, 3, display, LetterE, beatsin8(30), 255, 255);

        drawLetter(lowerX, (70 + YLocation) % display->lengthStrips, 3, display, LetterK, beatsin8(45), 255, 255);
        }

		// TODO uncomment this once we have a better way to pass character rendering arrays
		//void drawString(string text, int hue, Display* display)
		//{
		//	int spacer = 20 * text.length(); //measure the words out
		//	for (int i = 0; i < text.length(); i++)
		//	{
		//		int letter[8][8];
		//		char c = text[i];
		//		switch (c)
		//		{
		//			case 'A':
		//				letter = &LetterA;
		//			break;

		//			case 'B':
		//				//letter = LetterB;
		//				continue;
		//			break;

		//			case 'C':
		//				letter = LetterC;
		//			break;

		//			case 'D':
		//				letter = LetterD;
		//			break;

		//			case 'E':
		//				letter = LetterE;
		//			break;

		//			case 'F':
		//				//letter = LetterF;
		//				continue;
		//			break;

		//			case 'G':
		//				//letter = LetterG;
		//				continue;
		//			break;

		//			case 'H':
		//				//letter = LetterH;
		//				continue;
		//			break;

		//			case 'I':
		//				letter = LetterI;
		//			break;

		//			case 'J':
		//				letter = LetterJ;
		//			break;

		//			case 'K':
		//				letter = LetterK;
		//			break;

		//			case 'L':
		//				//letter = LetterL;
		//				continue;
		//			break;

		//			case 'M':
		//				letter = LetterM;
		//			break;

		//			case 'N':
		//				letter = LetterN;
		//			break;

		//			case 'O':
		//				letter = LetterO;
		//			break;

		//			case 'P':
		//				letter = LetterP;
		//			break;

		//			case 'Q':
		//				//letter = LetterQ;
		//				continue;
		//			break;

		//			case 'R':
		//				letter = LetterR;
		//			break;

		//			case 'S':
		//				letter = LetterS;
		//			break;

		//			case 'T':
		//				letter = LetterT;
		//			break;

		//			case 'U':
		//				letter = LetterU;
		//			break;

		//			case 'V':
		//				//letter = LetterV;
		//				continue;
		//			break;

		//			case 'W':
		//				letter = LetterW;
		//			break;

		//			case 'X':
		//				//letter = LetterX;
		//				continue;
		//			break;

		//			case 'Y':
		//				//letter = LetterY;
		//				continue;
		//			break;

		//			case 'Z':
		//				//letter = LetterZ;
		//				continue;
		//			break;

		//			case ' ':
		//				spacer -= 20;
		//				continue;
		//			break;
		//		}

		//		// becomes 2-54 based on the character (assuming capitals)
		//		int bpm = ((int)c - 63) * 2;
		//		drawLetter(0, (spacer + YLocation) % display->lengthStrips, 3, display, letter, beatsin8(bpm), 255, 255);
		//		spacer -= 20; // space for the next letter
		//	}
		//}

        void drawLetter(int lowerLeftX, int lowerLeftY, int orientation, Display* display, int letter[8][4], int hue, int sat, int bright){

          for (int j = 0; j < LetterHeight; j++)
          {
            for (int k = 0; k < LetterWidth; k++)
            {
              if(letter[j][k] == 1)
              {

                int pixelX;
                int pixelY;
                if(orientation == 1){
                   pixelX = lowerLeftX + LetterWidth - k -1;
                   pixelY = lowerLeftY + LetterHeight - j -1;
                } else if (orientation == 2) {
                   pixelX = lowerLeftX + j;
                   pixelY = lowerLeftY + k;
                } else if (orientation == 3) {
                   pixelX = lowerLeftX + k;
                   pixelY = lowerLeftY + j;
                }else{
                   pixelX = lowerLeftX + LetterHeight - j -1;
                   pixelY = lowerLeftY + LetterWidth - k -1;
                }

                if (pixelX >= 0 && pixelX < display->numStrips
					&& pixelY >= 0 && pixelY < display->lengthStrips)
				{
                  display->strips[pixelX][pixelY] = CHSV(hue, sat, bright);
                }
              }
            }
          }

        }
  };
