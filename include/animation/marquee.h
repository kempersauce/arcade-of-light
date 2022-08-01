#pragma once

#include <string>

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "engines/font.h"         // for Font
#include "engines/shapes.h"       // for Shapes

namespace kss {
namespace animation {

namespace letters = engines::letters;

// This file holds words and word functions
class Marquee : public Animation {
  int Hue = 0;
  int Saturation = 255;
  int Brightness = 255;
  int MarqueeSpeed = 1;
  int YLocation = 0;
  int Word[1][8][4];
  bool Stop = false;
  int StripX;
  int StripY;

  int LetterWidth = 4;
  int LetterHeight = 8;

  int test = 0;

  // list of words to display
  // int WordWinner[6][8][4] =
  // {{letters::W},{letters::I},{letters::N},{letters::N},{letters::E,letters::R}};
  // int WordLoser[5][8][4] =
  // {letters::L,letters::O,letters::S,letters::E,letters::R}; int
  // WordReady[5][8][4] =
  // {letters::R,letters::E,letters::A,letters::D,letters::Y}; int
  // WordStart[5][8][4] =
  // {{{letters::S},{letters::T},{letters::A},{letters::R},{letters::T}}}; int
  // WordGame[4][8][4] = {letters::G,letters::A,letters::M,letters::E}; int
  // WordOver[4][8][4] = {letters::O,letters::V,letters::E,letters::R}; int
  // WordYeet[4][8][4] = {letters::Y,letters::E,letters::E,letters::T}; int
  // WordArcade[6][8][4] =
  // {letters::A,letters::R,letters::C,letters::A,letters::D,letters::E}; int
  // WordOf[2][8][4] = {letters::O,letters::F}; int WordLight[5][8][4] =
  // {letters::L,letters::I,letters::G,letters::H,letters::T};

 public:
  // Initialize a word
  Marquee(int speed) : Animation() {
    int letter_count = 1;  // Brian!! idk how to do lookup tables

    // lookup characters from font file
    //  for (int i = 0; i < letter_count; i++)
    //  {
    //    for (int j = 0; j < LetterHeight; j++)
    //    {
    //      for (int k = 0; k < LetterWidth; k++)
    //      {
    //        //if (word == "START")
    //        //{
    //          Word[i][j][k] = letters::A[j][k];//Brian!! idk how to do lookup
    //          tables
    //        //}
    //      }
    //    }
    //  }
    // lookup number of letters based on entered word

    // Hue = hue;
    // MarqueeSpeed = speed;
    // YLocation = 120 + (letter_count * LetterHeight) ;
  }

  // Need to add spaces somehow
  void draw(display::Display* display) {
    // for (int i = 0; i < display->numStrips; i++)
    //   {
    //     for (int j = YLocation; j < display->lengthStrips; j++)
    //     {

    // int testX = 0;
    // int testY = 0;
    // if(test == 0){
    //   test = 1;
    //   display->Pixel(testX, testY) = CRGB::Brown;
    // }else{
    //   test = 0;
    //   display->Pixel(testX, testY) = CRGB::BlueViolet;
    // }

    YLocation -= MarqueeSpeed;
    if (YLocation < 0) {
      YLocation = display->lengthStrips;
    }

    std::string text = "KEMPER SAUCE";
    drawString(text, display);
    // int lowerX = 0;
    // drawLetter(lowerX, (10 + YLocation) % display->lengthStrips, 3, display,
    // letters::E, beatsin8(2), 255, 255);

    // drawLetter(lowerX, (30 + YLocation) % display->lengthStrips, 3, display,
    // letters::C, beatsin8(8), 255, 255);

    // drawLetter(lowerX, (50 + YLocation) % display->lengthStrips, 3, display,
    // letters::U, beatsin8(30), 255, 255);

    // drawLetter(lowerX, (10 + YLocation) % display->lengthStrips, 3, display,
    // letters::A, beatsin8(2), 255, 255);

    // drawLetter(lowerX, (30 + YLocation) % display->lengthStrips, 3, display,
    // letters::S, beatsin8(8), 255, 255);

    // drawLetter(lowerX, (50 + YLocation) % display->lengthStrips, 3, display,
    // letters::R, beatsin8(30), 255, 255);

    // drawLetter(lowerX, (70 + YLocation) % display->lengthStrips, 3, display,
    // letters::E, beatsin8(45), 255, 255);

    // drawLetter(lowerX, (10 + YLocation) % display->lengthStrips, 3, display,
    // letters::P, beatsin8(2), 255, 255);

    // drawLetter(lowerX, (30 + YLocation) % display->lengthStrips, 3, display,
    // letters::M, beatsin8(8), 255, 255);

    // drawLetter(lowerX, (50 + YLocation) % display->lengthStrips, 3, display,
    // letters::E, beatsin8(30), 255, 255);

    // drawLetter(lowerX, (70 + YLocation) % display->lengthStrips, 3, display,
    // letters::K, beatsin8(45), 255, 255);
  }

  void drawString(const std::string& text, display::Display* display) {
    int spacer = 10 * text.length();  // measure the words out
    for (size_t i = 0; i < text.length(); i++) {
      int(*letter)[8][4];  // default is empty
      char c = text[i];
      switch (c) {
        case 'a':
        case 'A':
          letter = &letters::A;
          break;

        case 'b':
        case 'B':
          // letter = &letters::B;
          continue;
          break;

        case 'c':
        case 'C':
          letter = &letters::C;
          break;

        case 'd':
        case 'D':
          letter = &letters::D;
          break;

        case 'e':
        case 'E':
          letter = &letters::E;
          break;

        case 'f':
        case 'F':
          // letter = &letters::F;
          continue;
          break;

        case 'g':
        case 'G':
          // letter = &letters::G;
          continue;
          break;

        case 'h':
        case 'H':
          // letter = &letters::H;
          continue;
          break;

        case 'i':
        case 'I':
          letter = &letters::I;
          break;

        case 'j':
        case 'J':
          letter = &letters::J;
          break;

        case 'k':
        case 'K':
          letter = &letters::K;
          break;

        case 'l':
        case 'L':
          // letter = &letters::L;
          continue;
          break;

        case 'm':
        case 'M':
          letter = &letters::M;
          break;

        case 'n':
        case 'N':
          letter = &letters::N;
          break;

        case 'o':
        case 'O':
          letter = &letters::O;
          break;

        case 'p':
        case 'P':
          letter = &letters::P;
          break;

        case 'q':
        case 'Q':
          // letter = &letters::Q;
          continue;
          break;

        case 'r':
        case 'R':
          letter = &letters::R;
          break;

        case 's':
        case 'S':
          letter = &letters::S;
          break;

        case 't':
        case 'T':
          letter = &letters::T;
          break;

        case 'u':
        case 'U':
          letter = &letters::U;
          break;

        case 'v':
        case 'V':
          // letter = &letters::V;
          continue;
          break;

        case 'w':
        case 'W':
          letter = &letters::W;
          break;

        case 'x':
        case 'X':
          // letter = &letters::X;
          continue;
          break;

        case 'y':
        case 'Y':
          // letter = &letters::Y;
          continue;
          break;

        case 'z':
        case 'Z':
          // letter = &letters::Z;
          continue;
          break;

        case ' ':
          spacer -= 10;
          continue;
          break;
      }

      // becomes 2-54 based on the character (assuming capitals)
      int bpm = ((int)c - 63) * 2;
      drawLetter(0, (spacer + YLocation) % display->lengthStrips, 3, display,
                 *letter, beatsin8(bpm), 255, 255);
      spacer -= 20;  // space for the next letter
    }
  }

  void drawLetter(int lowerLeftX, int lowerLeftY, int orientation,
                  display::Display* display, const int (&letter)[8][4], int hue,
                  int sat, int bright) {
    for (int j = 0; j < LetterHeight; j++) {
      for (int k = 0; k < LetterWidth; k++) {
        if (letter[j][k] == 1) {
          int pixelX;
          int pixelY;
          if (orientation == 1) {
            pixelX = lowerLeftX + LetterWidth - k - 1;
            pixelY = lowerLeftY + LetterHeight - j - 1;
          } else if (orientation == 2) {
            pixelX = lowerLeftX + j;
            pixelY = lowerLeftY + k;
          } else if (orientation == 3) {
            pixelX = lowerLeftX + k;
            pixelY = lowerLeftY + j;
          } else {
            pixelX = lowerLeftX + LetterHeight - j - 1;
            pixelY = lowerLeftY + LetterWidth - k - 1;
          }

          if (pixelX >= 0 && pixelX < display->numStrips && pixelY >= 0 &&
              pixelY < display->lengthStrips) {
            display->Pixel(pixelX, pixelY) = CHSV(hue, sat, bright);
          }
        }
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
