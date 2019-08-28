#define NUM_FIREWORKS 1

#include <Button.h>
#include <FancyFirework.h>
#include <Game.h>
#include <Display.h>

// #include <Starscape.h>
//#include <SkyFade.h>

class FireworkGame : Game
{
    // Button time
    // Button Up;
    // Button A;

    // Backgrounds
  //  Starscape* starBackground;// just drawing black empty space for now. we are alone in the universe
    //SkyFade* skyFade;


    FancyFirework firework[NUM_FIREWORKS]; //win animation fireworks

    public:
        FireworkGame(Display* display)
            : Game(display)
            // Up(BUTTON_PIN_1),
            // A(BUTTON_PIN_0),
        {
            // starBackground = new Starscape(display->numStrips, display->lengthStrips, 175);
            // skyFade = new SkyFade();
            // rocketBoost = new RocketBoost(5);
        }
        void setup()
        {
          for (int i = 0; i < NUM_FIREWORKS; i++)
          {
              firework[i] = FancyFirework();
          };

        // target.Loc = random(0,180)+100;
        }

        //Game Loop
    void loop() {

      for (int i = 0; i < NUM_FIREWORKS; i++)
      {
          firework[i].Move();
          firework[i].draw(display);
      }
    }
};