// Rocket flying game
// Game input: 1 Button
// Concept: Press the button to apply upward force to a dot
// Hover the dot in target zone and land to win
// Graph of expected outputs can be found here
// https://docs.google.com/spreadsheets/d/1KmZhmGb0J_XdEv5SdoHkTPB8KuGs9kxIDECwj5WWMT0/edit#gid=1271681145
// Version 0.1

#define LED_PIN 1   // OUTPUT pin WS2812B LED Strip is attached to input is GRB not RGB

#define delayval 25 //controls the "speed" of the rocket dot
#define animationDelay 50 //controls the speed of the win animation
#define NUM_FIREWORKS 5  //maximum of 30 on UNO
#define BRIGHTNESS 50

#include <Rocket.h>
#include <Button.h>
#include <Target.h>
#include <Firework.h>
#include <Game.h>
#include <Display.h>
#include <Starscape.h>
#include <SkyFade.h>
//#include <Sounds.h>
#include <ExplosionsInTheSky.h>
#include <LifeGame.h>

// Game states
enum RocketGameState {
    RocketGameIdle,
    RocketGameStart,
    RocketGamePlaying,
    RocketGameLose,
    RocketGameLevelAdvance,
    RocketGameWin
};

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
    Rocket rocket; //the player
    Target target; //the target
    Firework firework[NUM_FIREWORKS]; //win animation fireworks
    ExplosionsInTheSky explosionsInTheSky;

    // Game State tracker
    // This only tracks the current game state and does not detect game state changes
    // Any code that changes this is expected to update the other objects' state as necessary
    RocketGameState gameState;

    // Idle Game, plays after no buttons have been pressed before idle timeout
    RainbowGame idleGame; // TODO change LifeGame to not use buttons if we're going to use it as an idle game
    const long idleTimeoutMillis = 1000 * 30; // 30 seconds


    // Other variables
    int targetsWon = 0;
    int targetsPerLevel = 3;

public:
    RocketGame(Display* display)
        : Game(display),
        Up(BUTTON_PIN_2),
        resetButton(BUTTON_PIN_3),
        rocket(display->lengthStrips, new CRGB(255, 255, 255)),
        target(new CRGB(55, 0, 0)),
        explosionsInTheSky(),
        idleGame(display)
    {
        starBackground = new Starscape(display->numStrips, display->lengthStrips, 160);
        skyFade = new SkyFade(skyFadeColors[0]);
    }

    // Reset Game
    void setup()
    {
        level = 0;
        setLevelStart();
    }

    // Reset level
    void setLevelStart()
    {
        gameState = RocketGameStart;
        skyFade->setFadeColor(skyFadeColors[level]);
        target.randomize(display->lengthStrips);
        targetsWon = 0;
        rocket.SetGravity(gravityLevels[level]);
        rocket.Reset();
    }

    void checkTarget()
    {
        bool wasInTarget = target.isInTarget;
        target.isInTarget = rocket.Location > target.Loc && rocket.Location < target.Loc + target.Height;
        if (target.isInTarget)
        {
            // Check if we're just entering the target
            if (wasInTarget == false)
            {
                target.Time = millis();
            }

            // Check if we've closed out this target
            else if (millis() - target.Time > 3000)
            {
                //Win state

                targetsWon++;

                // Still more targets - make a new random target
                if (targetsWon < targetsPerLevel)
                {
                    target.randomize(display->lengthStrips);
                }

                // Last target is on the ground
                else if (targetsWon == targetsPerLevel)
                {
                    target.setToGround();
                }

                // We beat the level
                else if (targetsWon > targetsPerLevel)
                {
                    gameState = RocketGameLevelAdvance;
                    //full win animation goes here

                    //fully restart game
                    targetsWon = 0;
                    target.randomize(display->lengthStrips);
                    rocket.Location = 0;
                }

                //gameState = 0;
            }
        }
    }

    //Game Loop
    void loop()
    {
        // Poll button states
        Up.poll();
        resetButton.poll();

        // IDLE CHECK: This enters idle after idleTimeoutMillis, and falls out of idle if a buttons been pressed
        if (Up.getMillisReleased() > idleTimeoutMillis
            && resetButton.getMillisReleased() > idleTimeoutMillis)
        {
            // Reset the game state if we're just entering idle
            if (gameState != RocketGameIdle)
            {
                gameState = RocketGameIdle;
                idleGame.setup();
            }
        }

        // Reset this game if we're just coming out of idle
        else if (gameState == RocketGameIdle)
        {
            this->setup(); // this sets game state to RocketGameStart
        }

        // Reset this game if they hold the reset button longer than a second
        else if (resetButton.getMillisHeld() > 1000)
        {
            // TODO - send this into the RocketGameLose state instead
            setup();
        }

        switch (gameState)
        {
            case RocketGameIdle:
                // play the idle game, not this one
                idleGame.loop();
                return; // break out, we're not playing this game
            break;

            case RocketGameStart:
                // TODO fill this in, right now we just jump into playing state
                gameState = RocketGamePlaying;
            //break; // uncomment this once we have something here, right now we just fall through

            case RocketGamePlaying:
                rocket.SetBoost(Up.getMillisHeld()); // direct correlation between millis held and thrust (rocket caps it at ThrustMax=200)
                rocket.Move();

                if (rocket.Exploded)
                {
                    gameState = RocketGameLose;
                    explosionsInTheSky.startAnimation();
                }
                else
                {
                    checkTarget();
                }
            break;

            case RocketGameLevelAdvance:
                // Boost way way up the screen
                if (rocket.Location < display->lengthStrips * 2)
                {
                    rocket.SetBoost(rocket.Thrust + 20); // just keep boosting up
                    rocket.Move(false); // let it boost off the screen

                    // shift stars and target down according to Rocket Thrust up to 10 px/frame
                    int backgroundShift = 10 * rocket.Thrust / rocket.ThrustMax;
                    starBackground->noiseGenerator->y -= backgroundShift;
                    target.Loc -= backgroundShift;
                }

                // Rocket reached top of level, time to start a new one
                else
                {
                    level++;
                    if (level == levelMax)
                    {
                        // TODO set up whatever state we need for the Win state to start
                        gameState = RocketGameWin;
                    }
                    else
                    {
                        setLevelStart();
                    }
                }
            break;

            case RocketGameWin:
                // TODO fill this in right now we just jump straight into the start state of a new game
                setup();
            break;

            case RocketGameLose:
                if (explosionsInTheSky.isPlaying() == false)
                {
                    setup(); // reset to new game
                }
            break;
        }

        // Draw everything

        //draw stars in the very back
        starBackground->draw(display);

        //draw blue sky fade over the stars
        skyFade->draw(display);

        // draw targets on top of the background
        target.draw(display); //displays target

        // Draw the explosion if we're blowing up
        // TODO change this to check game state?
        if (rocket.Exploded)
        {
            explosionsInTheSky.draw(display);
        }

        // draw the rocket if we're not blowing up
        else
        {
            // draw the rocket ship on the very front
            rocket.draw(display);
        }



        //Serial prints for debugging


        /* Serial.print(rocket.Loc);  // prints a label
        Serial.print("\t");         // prints a tab

        Serial.print(rocket.oldLoc);  // prints a label
        Serial.print("\t");         // prints a tab

        Serial.print(rocket.Location);
        Serial.print("\t");

        Serial.print(rocket.Acceleration);
        Serial.print("\t");

        Serial.print(rocket.Velocity);
        Serial.print("\t");

        Serial.print(rocket.Thrust);
        Serial.print("\t");

        Serial.print(rocket.Time-rocket.oldTime);
        Serial.println();
     */

    }
};
