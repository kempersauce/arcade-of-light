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
#include <GliderWars.h>
#include <SerialTest.h>
#include <FiveStripTest.h>
#include <SnakeGame.h>
// #include <ShooterGame.h>
#include <FallingGame.h>
#include <LaneRunner.h>
#include <AnimationTest.h>
#include <LifeGameSinglePLayer.h>

uint32_t _lastFrameMillis{millis()};
void printFrameRate()
{
	uint32_t timeDiff = millis() - _lastFrameMillis;
	_lastFrameMillis = millis();
    float fps = (float)timeDiff / 1000.0;

	Serial.println((String)"FPS: " + fps + " | " + timeDiff + "ms");
}

Game* game;
Display* gameDisplay;

void setup()
{
    //FastLED.setBrightness(100);

    // init audio stuff
    //initAudio();

    Serial.begin(9600);
    Serial.println("Begin setup()");

    // Choose your Display type
    //gameDisplay = (Display*)new FiveDisplay();
    gameDisplay = (Display*)new H2HDisplay();
    //gameDisplay = (Display*)new RocketDisplay();

    Serial.println("gameDisplay created");

	// Choose your Game type
	//game = (Game*)new Head2Head(gameDisplay);
	//game = (Game*)new LifeGame(gameDisplay);
	//game = (Game*)new RocketGame(gameDisplay);
	game = (Game*)new RainbowGame(gameDisplay);
	//game = (Game*)new MarqueeGame(gameDisplay);
	//game = (Game*)new SnakeGame(gameDisplay);
	//game = (Game*)new ShooterGame(gameDisplay);
	//game = (Game*)new FallingGame(gameDisplay);
	//game = (Game*)new LaneRunnerGame(gameDisplay);
	//game = (Game*)new LifeGameSinglePlayer(gameDisplay);

	// Test Games
	//game = (Game*)new DirPadTest(gameDisplay);
	//game = (Game*)new FiveStripTest(gameDisplay);
	//game = (Game*)new GliderWarsGame(gameDisplay);
    //game = (Game*)new AnimationTest(gameDisplay);

    Serial.println("game created");

	game->setup();
	Serial.println("game setup complete");

	Serial.println("End setup()");

    pinMode(9, OUTPUT);
	FastLED.show();
}

void loop()
{
    //Serial.println("loop() entered");
    
    game->loop();
    FastLED.show();

    //Serial.println("loops brother");
	//printFrameRate();
}
