// hopefully this makes sound work
//#define FASTLED_ALLOW_INTERRUPTS 0

#include <H2HDisplay.h>
#include <FiveDisplay.h>
#include <Head2Head.h>
#include <RocketDisplay.h>
#include <RocketGame.h>
//#include <WavPlayer.h>
#include <LifeGame.h>
#include <SingleColorTest.h>
//#include <Sounds.h>
//#include <FireworkTest.h>
#include <RainbowGame.h>
#include <DirPadTest.h>
#include <MarqueeGame.h>
#include <H2HLifeGame.h>
#include <SerialTest.h>
#include <FiveStripTest.h>
#include <SnakeGame.h>
#include <ShooterGame.h>
#include <FallingGame.h>
#include <LaneRunner.h>
#include <AnimationTest.h>
#include <LifeGameSinglePLayer.h>

long _lastFrameMillis;
void printFrameRate()
{
	long timeDiff = millis() - _lastFrameMillis;
	_lastFrameMillis = millis();

	Serial.print("framerate: ");
	Serial.print((float)timeDiff / 1000.0);
	Serial.print(" (");
	Serial.print(timeDiff);
	Serial.println("ms)");
}


Game* game;
Display* gameDisplay;

void setup()
{
    FastLED.setBrightness(100);

    // init audio stuff
    //initAudio();

    //delay(15 * 1000);
    Serial.begin(115200);
    Serial.println("Begin setup()");

    // Choose your Display type
    //gameDisplay = (Display*)new FiveDisplay();
    gameDisplay = (Display*)new H2HDisplay();
    //gameDisplay = (Display*)new RocketDisplay();

    // debug set strip0 red
    // for (int i = 0; i < gameDisplay->lengthStrips; i++)
    // {
    //     gameDisplay->strips[0][i] = CRGB::Red;
    // }
    Serial.println("gameDisplay created");
    FastLED.show();

    // debug set strip0 yellow
    for (int i = 0; i < gameDisplay->lengthStrips; i++)
    {
        gameDisplay->strips[0][i] = CRGB::Yellow;
    }
    Serial.println("game created");
    FastLED.show();

	// Choose your Game type
	//game = (Game*)new Head2Head(gameDisplay);
	//game = (Game*)new LifeGame(gameDisplay);
	//game = (Game*)new RocketGame(gameDisplay);
	//game = (Game*)new RainbowGame(gameDisplay);
	//game = (Game*)new MarqueeGame(gameDisplay);
	//game = (Game*)new SnakeGame(gameDisplay);
	//game = (Game*)new ShooterGame(gameDisplay);
	//game = (Game*)new FallingGame(gameDisplay);
	//game = (Game*)new LaneRunnerGame(gameDisplay);
	game = (Game*)new LifeGameSinglePlayer(gameDisplay);


	// Test Games
	//game = (Game*)new DirPadTest(gameDisplay);
	//game = (Game*)new FiveStripTest(gameDisplay);
	//game = (Game*)new H2HLifeGame(gameDisplay);
    //game = (Game*)new AnimationTest(gameDisplay);

	// debug set strip0 yellow
	// for (int i = 0; i < gameDisplay->lengthStrips; i++)
	// {
	//     gameDisplay->strips[0][i] = CRGB::Yellow;
	// }
	Serial.println("game created");
	FastLED.show();

	game->setup();

	// debug set strip0 green
	// for (int i = 0; i < gameDisplay->lengthStrips; i++)
	// {
	//     gameDisplay->strips[0][i] = CRGB::Green;
	// }
	Serial.println("game setup complete");
	FastLED.show();

	Serial.println("End setup()");
	FastLED.show();
}

void loop()
{
	//printFrameRate();

    // debug set strip0 blue
    //for (int i = 0; i < gameDisplay->lengthStrips; i++)
    //{
    //    gameDisplay->strips[0][i] = CRGB::Blue;
    //}
    //Serial.println("loop() entered");

    game->loop();
    FastLED.show();


    //Serial.println("loops brother");
    //delay(10);
    //Serial.println("loop() finished");
}
