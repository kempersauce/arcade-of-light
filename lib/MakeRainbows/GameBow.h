#include <Game.h>
#include <Rainbow.h>
#include <Arduino.h>
#include <FastLED.h>
#include <PinSetup.h>

#define delayVal 25

//Rainbow Class
class GameBow : Game{

public:
    GameBow(Display* gameDisplay):Game(gameDisplay){}
    void setup(){
        background = new RainbowAni();
    }
    void loop(){
        background.draw(display);
        FastLED.show();
    }
}


//Rainbow Animation
class RainbowAni: Animation{

public:
    //override rainbow draw function
    void draw(Display* display){
        for (int i=1; i < display.lengthSrips ; i++)
        {
            for(int j=0; j < display.numStrips; j++){
                display.strips[j][i] = rainbows[(i%7)+iterator];
            }
        }
        if (iterator < 6)
        {
            iterator++;
        }
        else
        {
            iterator = 0;
        }
    }

private:
    CRGB rainbows[14] = {
      CRGB::Red,
      CRGB::Orange,
      CRGB::Yellow,
      CRGB::Green,
      CRGB::Blue,
      CRGB::Indigo,
      CRGB::Violet,
      CRGB::Red,
      CRGB::Orange,
      CRGB::Yellow,
      CRGB::Green,
      CRGB::Blue,
      CRGB::Indigo,
      CRGB::Violet
    };
    int iterator = 0;
}
