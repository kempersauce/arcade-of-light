// Rocket flying game
// Game input: 1 Button
// Concept: Press the button to apply upward force to a dot
// Hover the dot in target zone and land to win
// Graph of expected outputs can be found here
// https://docs.google.com/spreadsheets/d/1KmZhmGb0J_XdEv5SdoHkTPB8KuGs9kxIDECwj5WWMT0/edit#gid=1271681145
// Version 0.1

#define LED_PIN 1   // OUTPUT pin WS2812B LED Strip is attached to input is GRB not RGB

#define delayval 25 //controls the "speed" of the player dot
#define animationDelay 50 //controls the speed of the win animation
#define NUM_FIREWORKS 5  //maximum of 30 on UNO
#define BRIGHTNESS 50

#include <Rocket.h>
#include <Button.h>
#include <Target.h>
#include <Firework.h>
#include <Game.h>
#include <Display.h>
#include <RocketBoost.h>
#include <Starscape.h>
#include <SkyFade.h>
//#include <Sounds.h>
#include <ExplosionsInTheSky.h>
#include <LifeGame.h>

class RocketGame : Game
{
    // Button time
    Button Up;
    Button resetButton;

    // Backgrounds
    Starscape* starBackground;// just drawing black empty space for now. we are alone in the universe
    SkyFade* skyFade;

    int level;
    static const int levelMax = 3;

    // level colors for SkyFade
    CRGB* skyFadeColors[levelMax] =
    {
        new CRGB(0, 0, 255), // Blue earth
        new CRGB(32, 96, 255), // Orange mars
        new CRGB(128, 0, 128), // Purple Pluto
    };

    // Level values for gravity
    int gravityLevels[levelMax] =
    {
        15, // Earth has so much gravities
        12, // Mars is not as stronk, only has this many gravities
        7, // poor little old Pluto barely has any gravities, be careful with that button
    };

    // Sprites
    Rocket player; //the player
    RocketBoost* rocketBoost;
    Target target; //the target
    Firework firework[NUM_FIREWORKS]; //win animation fireworks
    ExplosionsInTheSky explosionsInTheSky;

    // Idle Game, plays after no buttons have been pressed before idle timeout
    RainbowGame idleGame; // TODO change LifeGame to not use buttons if we're going to use it as an idle game
    bool isIdle;
    const long idleTimeoutMillis = 1000 * 30; // 30 seconds


    // Other variables
    int redColor = 0;
    int blueColor = 0;
    int greenColor = 0;
    int gameState = 0;
    int wins = 0;
    long time = millis();

public:
    RocketGame(Display* display)
        : Game(display),
        Up(BUTTON_PIN_2),
        resetButton(BUTTON_PIN_3),
        player(0, new CRGB(255, 255, 255)),
        target(100, 15, new CRGB(55, 0, 0)),
        explosionsInTheSky(),
        idleGame(display)
    {
        starBackground = new Starscape(display->numStrips, display->lengthStrips, 160);
        skyFade = new SkyFade(skyFadeColors[0]);
        rocketBoost = new RocketBoost(5);
    }

    void setup()
    {
        // for (int i = 0; i < NUM_FIREWORKS; i++)
        // {
        //     firework[i] = Firework();
        // }

        level = 0;
        player.SetGravity(gravityLevels[level]);
        skyFade->setFadeColor(skyFadeColors[level]);
        target.Loc = random(display->lengthStrips / 4, display->lengthStrips - 20);
        gameState = 0;
        wins = 0;
        isIdle = false;
        player.Reset();
    }

    void checkWin()
    {
        if (gameState == 0)
        {
            // do nothing
        }
        else if (gameState == 2)
        {
            // Lose state
            // fill the strip with red, one frame at a time
            for (int i = 0; i < display->lengthStrips; i++)
            {
                display->strips[0][i].setRGB(255, 0, 0);
                FastLED.show();
                delay(animationDelay);
            }

            //Restart game
            player.Location = 0;
            target.Loc = random(display->lengthStrips / 4, display->lengthStrips - 20);

        }
        else if (gameState == 1)
        {
            //Win state

            wins = wins + 1;
            //shrapnelAnimate = true;
            //shrapTop.Loc = target.Loc + target.Height;
            //shrapMid.Loc = target.Loc + target.Height/2;
            //shrapBot.Loc = target.Loc;

     /*     int upDot = target.Loc + .5 * target.Height;
            int downDot = target.Loc + .5 * target.Height;
            int upFin = 0;
            int downFin = 0;
            // two way color fill across entire strip
            while (upFin + downFin != 2)
                {
                    int redColor = random(0,255);
                    int greenColor = random(0,255);
                    int blueColor = random(0,255);
                    if (upFin == 0){
                        leds[upDot].setRGB( greenColor, redColor, blueColor);
                        FastLED.show();
                        upDot = upDot + 1;
                        if (upDot > display->lengthStrips){
                            upFin = 1;
                        }
                    }
                    if (downFin == 0){
                        leds[downDot].setRGB( greenColor, redColor, blueColor);
                        FastLED.show();
                        downDot = downDot - 1;
                        if (downDot < 0){
                            downFin = 1;
                        }
                    }

                    //delay(animationDelay);
                } */

            //Restart game
            if (wins < 3)
            {
                target.Loc = random(display->lengthStrips / 4, display->lengthStrips - 20);
                target.Height = random(0,15)+5;
                target.Step = target.Height/6;
            }

            if (wins == 3)
            {
                target.Loc = 5;
                target.Height = 10;
                target.Step = target.Height/6;
            }

            if (wins > 3)
            {
                //full win animation goes here
                for (int i = 0; i < display->numStrips; i++)
                {
                    for (int j = 0; j < display->lengthStrips; j++)
                    {
                        redColor = random(0,200);
                        greenColor = random(0,200);
                        blueColor = random(0,200);
                        display->strips[i][j].setRGB(greenColor, redColor, blueColor);
                        FastLED.show();
                    }
                }

                //fully restart game
                wins = 0;
                target.Loc = random(display->lengthStrips / 4, display->lengthStrips - 20);
                target.Height = random(0,15)+5;
                target.Step = target.Height/6;
                player.Location = 0;
            }
            player.Velocity = 0;
            player.Acceleration = 0;
            gameState = 0;
        }
    }

    void checkTarget()
    {
        if (player.Location > target.Loc && player.Location < target.Loc + target.Height && target.isInTarget == false) {
            target.isInTarget = true;
            target.Time = millis();
        }

        if (player.Location < target.Loc || player.Location > target.Loc + target.Height) {
            target.isInTarget = false;
        }

        if (target.isInTarget == true && millis() - target.Time > 3000) {
            gameState = 1;
        }
    }

    //Game Loop
    void loop()
    {
        // Poll button states
        Up.poll();
        resetButton.poll();

        // Check if we're idling
        bool wasIdle = isIdle;

        // This enters idle after idleTimeoutMillis, and falls out of idle if a buttons been pressed
        isIdle = Up.getMillisReleased() > idleTimeoutMillis
            && resetButton.getMillisReleased() > idleTimeoutMillis;

        if (isIdle)
        {
            // Reset the idle game if we're just entering idle
            if (wasIdle == false)
            {
                idleGame.setup();
            }

            // play the idle game, not this one
            idleGame.loop();
            return;
        }
        // Reset this game if we're just exiting idle
        else if (wasIdle)
        {
            this->setup();
        }

        time = millis();

        // Reset this game if they hold the reset button longer than a second
        if (resetButton.getMillisHeld() > 1000)
        {
            this->setup();
        }

        // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
        if (Up.isPressed())
        {
            player.Boost();
        }
        else
        {
            player.endBoost();
        }

        player.Move(display->lengthStrips);

        checkTarget();



        // Draw everything

        //draw stars in the very back
        starBackground->draw(display);

        //draw blue sky fade over the stars
        skyFade->draw(display);



        if (player.Exploded)
        {
            if (explosionsInTheSky.isPlaying() == false)
            {
                explosionsInTheSky.startAnimation();
            }

            explosionsInTheSky.draw(display);

            if (explosionsInTheSky.isPlaying() == false)
            {
                setup();
            }
        }
        else
        {
            // draw targets on top of the background
            target.draw(display); //displays target

            // draw the rocket boost
            rocketBoost->loc = (int)player.Location;
            rocketBoost->boostFactor = (float)Up.getMillisHeld() / (float)500; // .5 second total ramp-up time

            rocketBoost->draw(display);

            // draw the rocket ship on the very front
            player.draw(display);

            checkWin();
        }
        //Serial prints for debugging


        /* Serial.print(player.Loc);  // prints a label
        Serial.print("\t");         // prints a tab

        Serial.print(player.oldLoc);  // prints a label
        Serial.print("\t");         // prints a tab

        Serial.print(player.Location);
        Serial.print("\t");

        Serial.print(player.Acceleration);
        Serial.print("\t");

        Serial.print(player.Velocity);
        Serial.print("\t");

        Serial.print(player.Thrust);
        Serial.print("\t");

        Serial.print(player.Time-player.oldTime);
        Serial.println();
     */

    }
};
