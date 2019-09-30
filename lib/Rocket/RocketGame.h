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
#include <Explosion.h>
#include <ExplosionsInTheSky.h>
#include <LifeGame.h>
#include <vector>


#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

AudioControlSGTL5000 sgtl5000_1;
AudioOutputI2S i2s1;

// Use these with the Teensy Audio Shield
//This uses the audio shield's card reader
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// TODO move these into the WavPLayer class
AudioPlaySdWav           playSdWav1;
//AudioPlaySdWav           playSdWav2;
//AudioPlaySdWav           playSdWav3;
//AudioPlaySdWav           playSdWav4;

AudioConnection          patchCord1(playSdWav1, 0, i2s1, 0);
//AudioConnection          patchCord2(playSdWav2, 0, i2s1, 1);
//AudioConnection          patchCord3(playSdWav3, 0, i2s1, 2);
//AudioConnection          patchCord4(playSdWav4, 0, i2s1, 3);


using namespace std;

// Game states
enum RocketGameState {
    RocketGameStart,
    RocketGamePlaying,
    RocketGameLose,
    RocketGameLevelAdvance,
    RocketGameWin
};

class RocketGame : Game
{
	void initAudio()
	{
		AudioMemory(32);
		sgtl5000_1.enable();
		sgtl5000_1.volume(1);
		SPI.setMOSI(SDCARD_MOSI_PIN);
		SPI.setSCK(SDCARD_SCK_PIN);
		if (!(SD.begin(SDCARD_CS_PIN)))
		{
			while (1)
			{
				Serial.println("Unable to access the SD card");
				delay(500);
			}
		}

		playSdWav1.play("HUMANITY.WAV");
	}

    // Button time
    Button Up;
    Button resetButton;

    // Backgrounds
    Starscape starBackground;// just drawing black empty space for now. we are alone in the universe
    SkyFade skyFade;

    // Level progress tracking
    int targetsWon = 0;
    static const int targetsPerLevel = 3;

    int level = 0;
    static const int levelMax = 3;

    // level colors for SkyFade
    CRGB* skyFadeColors[levelMax] =
    {
        new CRGB(0, 0, 255), // Blue Earth
        new CRGB(255, 96, 0), // Orange Mars
        new CRGB(128, 0, 128), // Purple Pluto
    };

    // level colors for targets
    CRGB* targetColors[levelMax] =
    {
        new CRGB(255, 0, 0), // Red targets on Blue Earth
        new CRGB(0, 255, 0), // Green targets on Orange Mars
        new CRGB(255, 255, 0), // Yellow targets on Purple Pluto
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

    static const int numFireworks = 5;
    vector<Firework> fireworks; //win animation fireworks

    // Game Lose animations
    Explosion explosion;
    ExplosionsInTheSky explosionsInTheSky;

    // Game State tracker
    // This only tracks the current game state and does not detect game state changes
    // Any code that changes this is expected to update the other objects' state as necessary
    RocketGameState gameState;

    // Fireworks animation plays after no buttons have been pressed before idle timeout
    const long idleTimeoutMillis = 1000 * 30; // 30 seconds

public:
    RocketGame(Display* display)
        : Game(display),
        Up(BUTTON_PIN_0),
        resetButton(BUTTON_PIN_1),
		starBackground(display->numStrips, display->lengthStrips, 160),
		skyFade(skyFadeColors[0]),
        rocket(display->lengthStrips, new CRGB(255, 255, 255)),
        target(new CRGB(55, 0, 0)),
        explosionsInTheSky(),
		explosion(),
        fireworks()
    {
		initAudio();

		// Set explosion to red
		explosion.Hue = 0; // Red explosions
		explosion.brightnessPhaseMillis = 3000; // slower, 3 second long burnout

		// Set some physics on the explosion shrapnel so they'll bounce off the ceiling and floor
		for (int i = 0; i < explosion.shrapnel.size(); i++)
		{
			explosion.shrapnel[i].LocationMax = display->lengthStrips;
			explosion.shrapnel[i].BounceFactor = -.8;
		}

		while (fireworks.size() < numFireworks)
		{
			fireworks.push_back(Firework(display->lengthStrips, display->numStrips));
		}
    }

    // Reset Game
    void setup()
    {
        level = 0;
        enterLevelStartState();
    }

    // Reset level
    void enterLevelStartState()
    {
        gameState = RocketGameStart;
        skyFade.setFadeColor(skyFadeColors[level]);
        target.setColor(targetColors[level]);
        target.randomize(display->lengthStrips);
        targetsWon = 0;
        rocket.SetGravity(gravityLevels[level]);
        rocket.Reset();
    }

	void enterWinState()
	{
		gameState = RocketGameWin;
		for (int i = 0; i < numFireworks; i++)
		{
			fireworks[i].Reset();
			fireworks[i].explosion.SetGravity(gravityLevels[min(level, levelMax - 1)]);
		}
	}

	void enterLoseState()
	{
		gameState = RocketGameLose;
		playSdWav1.play("EXPLODE1.WAV");
		explosion.ExplodeAt(display->numStrips / 2, rocket.physics.Location);
		explosionsInTheSky.startAnimation();
	}

	void enterLevelAdvanceState()
	{
		gameState = RocketGameLevelAdvance;
		// No other changes required for this state change
	}

	void enterPlayingState()
	{
		gameState = RocketGamePlaying;
		// No other changes required for this state change
	}

    void checkTarget()
    {
        bool wasInTarget = target.isInTarget;
        target.isInTarget = rocket.physics.Location >= target.Loc && rocket.physics.Location < target.Loc + target.Height;
        if (target.isInTarget)
        {
            // Check if we're just entering the target
            if (wasInTarget == false)
            {
                target.Time = millis();
            }

            // Check if we've closed out this target
            else if (target.isTargetLocked())
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
                    enterLevelAdvanceState();
                }
            }
        }
    }

    //Game Loop
    void loop()
    {
        // Poll button states
        Up.poll();
        resetButton.poll();


		// CHECK FOR MANUALLY-INDUCED GAME STATE CHANGES

        // IDLE CHECK: This enters idle after idleTimeoutMillis, and falls out of idle if a buttons been pressed
        if (gameState != RocketGameWin
			&& Up.getMillisReleased() > idleTimeoutMillis
            && resetButton.getMillisReleased() > idleTimeoutMillis)
        {
			enterWinState(); // just play the win animation here
        }

        // Reset this game if we're just coming out of idle
        if (gameState == RocketGameWin
			&& (Up.isDepressing() || resetButton.isDepressing()))
        {
            setup(); // this sets game state to RocketGameStart
        }

        // Reset this game if they hold the reset button longer than a second (if we havent already lost)
        if (gameState != RocketGameLose && resetButton.getMillisHeld() > 1000)
        {
			enterLoseState();
        }


		// CALCULATE NEW GAME STATE

        switch (gameState)
        {
            case RocketGameStart:
                // TODO fill this in, right now we just jump into playing state
                enterPlayingState();
				//enterWinState(); // for testing fireworks
            //break; // uncomment this once we have something here, right now we just fall through

            case RocketGamePlaying:
                rocket.SetBoost(Up.getMillisHeld()); // direct correlation between millis held and thrust (rocket caps it at ThrustMax=200)

                rocket.Move();

                if (rocket.physics.HasExploded)
                {
                    enterLoseState();
                }
                else
                {
                    checkTarget();
                }
            break;

            case RocketGameLevelAdvance:
                // Boost way way up the screen
                if (rocket.physics.Location < display->lengthStrips * 2)
                {
                    rocket.SetBoost(rocket.physics.Thrust + 5); // just keep boosting up
                    rocket.Move(false); // let it boost off the screen

                    // shift stars and target down according to Rocket Thrust up to 10 px/frame
                    //int backgroundShift = min(rocket.Velocity / 32, 6);

                    // jk since scale is so high, any higher than 1*scale is too fast, and any lover than 1*cale causes tearing between pixels
                    int backgroundShift = 1;
                    starBackground.noiseGenerator->y += backgroundShift * starBackground.noiseGenerator->scale; // NOTE: Since y is actually an 8.8 bit int, this may need more than just a small push
                }

                // Rocket reached top of level, time to start a new one
                else
                {
                    level++;
                    if (level == levelMax)
                    {
                        // TODO set up whatever state we need for the Win state to start
						enterWinState();
                    }
                    else
                    {
                        enterLevelStartState();
                    }
                }
            break;

            case RocketGameWin:
                for (int i = 0; i < numFireworks; i++)
                {
                    fireworks[i].Move();
					if (fireworks[i].isPlaying == false)
					{
						fireworks[i].Reset();
					}
                }
                // TODO fill this in right now we just jump straight into the start state of a new game
                //setup();
            break;

            case RocketGameLose:
                if (explosionsInTheSky.isPlaying())
				{
					explosion.Move();
				}
				else
                {
                    setup(); // reset to new game
                }
            break;
        }


        // DRAW EVERYTHING ACCORDING TO GAME STATE

		switch (gameState)
		{
			case RocketGameStart:
				// TODO how should this look?
		        starBackground.draw(display);
		        skyFade.draw(display);
				//target.draw(display);
				//explosionsInTheSky.draw(display);
				//explosion.draw(display);
				//for (int i = 0; i < numFireworks; i++) fireworks[i].draw(display);
				rocket.draw(display);
			break;

			case RocketGamePlaying:
		        starBackground.draw(display);
		        skyFade.draw(display);
				target.draw(display);
				//explosionsInTheSky.draw(display);
				//explosion.draw(display);
				//for (int i = 0; i < numFireworks; i++) fireworks[i].draw(display);
				rocket.draw(display);
			break;

			case RocketGameLose:
		        starBackground.draw(display);
		        skyFade.draw(display);
				//target.draw(display);
				explosionsInTheSky.draw(display);
				explosion.draw(display);
				//for (int i = 0; i < numFireworks; i++) fireworks[i].draw(display);
				//rocket.draw(display);
			break;

			case RocketGameLevelAdvance:
		        starBackground.draw(display);
		        skyFade.draw(display);
				//target.draw(display);
				//explosionsInTheSky.draw(display);
				//explosion.draw(display);
				//for (int i = 0; i < numFireworks; i++) fireworks[i].draw(display);
				rocket.draw(display);
			break;

			case RocketGameWin:
		        starBackground.draw(display);
		        skyFade.draw(display);
				//target.draw(display);
				//explosionsInTheSky.draw(display);
				//explosion.draw(display);
				for (int i = 0; i < numFireworks; i++) fireworks[i].draw(display);
				//rocket.draw(display);
			break;
		}
    }
};
