// hopefully this makes sound work
//#define FASTLED_ALLOW_INTERRUPTS 0

#include "display/h2h.h"  // for H2HDisplay
#include "display/five.h"  // for FiveDisplay
#include "games/head2head/head2head.h"  // for Head2Head
#include "display/rocket.h"  // for RocketDisplay
#include "games/rocket/rocket_game.h"  // for RocketGame
//#include "games/wav_player.h"  // for WavPlayer
#include "games/life/life.h"  // for LifeGame
#include <SingleColorTest.h>
// #include "audio/sounds.h"  // for Sounds
//#include <FireworkTest.h>
#include "games/rainbow.h"  // for RainbowGame
#include <DirPadTest.h>
#include "games/marquee.h"  // for MarqueeGame
#include "games/life/glider_wars.h"  // for GliderWars
#include <SerialTest.h>
#include <FiveStripTest.h>
#include "games/snake/snake_game.h"  // for SnakeGame
// #include "games/shooter/shooter_game.h"  // for ShooterGame
#include "games/falling.h"  // for FallingGame
#include "games/lane_runner/lane_runner.h"  // for LaneRunner
#include <AnimationTest.h>
#include "games/life/life_single_player.h"  // for LifeGameSinglePlayer

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
