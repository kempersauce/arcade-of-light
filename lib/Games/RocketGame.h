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
#include <Sounds.h>

AudioPlaySdWav boostChannel;
AudioConnection audioConnection1(boostChannel, i2s1);

class RocketGame : Game
{
    // Button time
    Button Up;
    Button resetButton;

    // Backgrounds
    Starscape* starBackground;// just drawing black empty space for now. we are alone in the universe
    SkyFade* skyFade;

    // Sprites
    Rocket player; //the player
    RocketBoost* rocketBoost;
    Target target; //the target
    Firework firework[NUM_FIREWORKS]; //win animation fireworks


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
            Up(BUTTON_PIN_1),
            resetButton(BUTTON_PIN_0),
            player(0, new CRGB(255, 255, 255)),
            target(100, 15, new CRGB(55, 0, 0))
        {
            starBackground = new Starscape(display->numStrips, display->lengthStrips, 160);
            skyFade = new SkyFade();
            rocketBoost = new RocketBoost(5);
        }

    void setup()
    {
        // for (int i = 0; i < NUM_FIREWORKS; i++)
        // {
        //     firework[i] = Firework();
        // }

        target.Loc = random(100,250);
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
            player.Location = (float)random(0, display->lengthStrips);
            target.Loc = random(0, display->lengthStrips);

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
                target.Loc = random(0,180)+100;
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
                target.Loc = random(0,100)+100;
                target.Height = random(0,15)+5;
                target.Step = target.Height/6;
                player.Location = 0;
            }
            player.Velocity = 0;
            player.Acceleration = 0;
            gameState = 0;
        }
    }

    void handleExplosion()
    {
        // Draw explosion accross all strips
        for (int j = 0; j < display->numStrips; j++)
        {
            // sets the top 15 pixels in a fade from red to black
            for (int i = display->lengthStrips; i > display->lengthStrips - 15; i--)
            {
                redColor = 255;
                display->strips[j][i].setRGB( 0, redColor, 0);
                FastLED.show();
                redColor = redColor - 17;
                delay(animationDelay);
            }

            // fade those same top 15 pixels the rest of the way to black over 10 iterations
            for (int j = 10; j > 0; j--)
            {
                for (int i = display->lengthStrips; i > display->lengthStrips - 15; i--)
                {
                    display->strips[j][i].fadeToBlackBy( 64 );
                    FastLED.show();
                    delay(animationDelay-5);
                }
            }

            // hard set the top 15 pixels to black
            for (int i = display->lengthStrips; i > display->lengthStrips - 15; i--)
            {
                display->strips[j][i].setRGB( 0, 0, 0);
            }
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
    void loop() {
        time = millis();

        // Poll button states
        Up.poll();
        resetButton.poll();

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

        if (player.Exploded == true)
        {
            handleExplosion();
            player.Exploded = false;
        }

        checkTarget();



        // Draw everything

        //draw stars in the very back
        starBackground->draw(display);

        //draw blue sky fade over the stars
        skyFade->draw(display);

        // draw targets on top of the background
        target.draw(display); //displays target

        // draw the rocket boost
        rocketBoost->loc = (int)player.Location;
        rocketBoost->boostFactor = (float)Up.getMillisHeld() / (float)500; // .5 second total ramp-up time

        rocketBoost->draw(display);

        // draw the rocket ship on the very front
        player.draw(display);

        checkWin();

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
