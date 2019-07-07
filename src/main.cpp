#include <Arduino.h>
// Bouncy Dot Game
// Game input: 1 Button
// Concept: Press the button to reverse direction within the target zone
// as you hit targets, speed increases and target size shrinks
#include <FastLED.h>
#define LED_PIN 35   // OUTPUT pin WS2812B LED Strip is attached to input is GRB not RGB
#define NUM_LEDS 300 // number of LEDs per strip
#define debounceTime 200 // keep those button inputs clean
#define delayval 25 //controls the "speed" of the player dot
#define animationDelay 10 //controls the speed of the win animation

#include <Dot.h>
#include <Button.h>
#include <Target.h>
#include <Background.h>

//Making Objects
Button Up(26); //Buttons go here
// Button A(24);
// Button B(23);
Dot player(0,0,0,255); //the player
Target target(100,15,55,0,0); //the target
Background background(0,NUM_LEDS,15,0,10);

//Rainbow Animation
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

// Other variables
int redColor = 0;
int blueColor = 0;
int greenColor = 0;
int buttonUpState = LOW;
int buttonUpStateOld = LOW;

bool gameOver = false;
bool newGame = true;
bool newButtonPress = false;

//LED strip
CRGB leds[NUM_LEDS]; // This is an array of leds.  One item for each led in your strip.

void checkWin() {
    if(gameOver)
    {
        // Lose state
        //change this to a fill
        for (int i = 0; i < NUM_LEDS; i++){
            leds[i].setRGB( 255, 0, 0);
            FastLED.show();
            delay(animationDelay);
        }
        delay(2000);
        //Restart game
        player.Loc = 0;
        target.Height = 15;
        target.Loc = 250;

        gameOver = false;
        newGame = true;
    }
}


void checkButton()
{


    if(buttonUpState==HIGH && buttonUpStateOld==LOW)
    {
        newButtonPress=true;
    }
    else
    {
        newButtonPress=false;
    }

}

void writeBackground()
{
    for(int i=background.Loc; i<=background.Height; i++)
    {
        leds[i].setRGB(background.Red, background.Green, background.Blue);
    }
}

void moveTarget(){
    int oldLoc = target.Loc;
    int roll = random(0,100);
    if(roll<15)
    {
        target.Height--;
    }
    if(player.Velocity > 0)
    {
        target.Loc = random(oldLoc+(oldLoc/4), (NUM_LEDS - target.Height));
    } else {
        target.Loc = random(0, oldLoc-(oldLoc/4));
    }
}

void writeTarget() // Target fill
    {
    for (int i = target.Loc+1; i < target.Loc + target.Height; i++){

        //Increase Color intensity on hit
        if (target.inTarget == true)
        {
            leds[i].setRGB(target.Green,target.Red, target.Blue);
        }else
        {
        leds[i].setRGB(10, 0, 0);
        }
    }
    // Target bookends
    leds[target.Loc].setRGB(target.Green, target.Red, target.Blue);
    leds[target.Loc+target.Height].setRGB(target.Green,target.Red, target.Blue);
}

void writePlayerAway()
{
    leds[player.oldLoc].setRGB(0,0,0);// Remove old player dots
}

void writePlayer()
{
    leds[player.Loc].setRGB(player.Green, player.Red, player.Blue); // Player.

    // int flame1 = player.Loc - 1;
    // int flame2 = player.Loc - 2;
    // int flame3 = player.Loc - 3;
    // int flame4 = player.Loc - 4;
    // //if velocity is negative, put flames on other side
    // if (player.Velocity<0) {
    //     flame1 = player.Loc + 1;
    //     flame2 = player.Loc + 2;
    //     flame3 = player.Loc + 3;
    //     flame4 = player.Loc + 4;
    // }

    // leds[flame1].setRGB(255,255,0);
    // leds[flame2].setRGB(191,255,0);
    // leds[flame3].setRGB(128,255,0);
    // leds[flame4].setRGB(0,100,0);
}

void checkExplosion()
{
    if (player.Loc >= NUM_LEDS+1 || player.Loc <= -1){
        //Move this somewhere else or make player reset method
        player.Loc=0;
        player.Velocity=0;
        target.Height = 15;
        target.Loc = 185;

        //red
        int j=0;
        while(j<70)
        {
            for (int i=1; i < NUM_LEDS ; i++)
            {
                leds[i] = rainbows[(i%7)+iterator];
            }
            if (iterator < 6)
            {
                iterator++;
            }
            else
            {
                iterator = 0;
            }
            FastLED.show();
            delay(delayval);
            j++;
        }
        gameOver = true;
    }
}

void checkTarget()
{
    if (player.Loc > target.Loc && player.Loc < (target.Loc + target.Height))
    {
        target.inTarget = true;
    }

    if (player.Loc < target.Loc || player.Loc > target.Loc + target.Height)
    {
        target.inTarget = false;
    }
}

void setup() {
    //Serial.begin(9600);
    //while (!Serial) {
    //    ; // wait for serial port to connect. Needed for native USB
    //}
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
    delay(2000);
    //initialize LED Strip
    FastLED.addLeds<WS2812B, LED_PIN, RGB>(leds, NUM_LEDS);
    //set player on strip
    writeBackground();
    leds[player.Loc].setRGB( player.Green, player.Red, player.Blue); // Player.
    writeTarget();
    FastLED.show();
}

//Game Loop
void loop() {
    // read if there is a new button press
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    buttonUpStateOld = buttonUpState;
    buttonUpState = Up.read();
    checkButton();
    if(player.Velocity==0 && newButtonPress)
    {
        player.Start();
        newGame = false;
    }else if (newButtonPress)
    {
        //writeBackground();
        checkTarget();
        if(target.inTarget)
        {
            player.Flip();
            moveTarget();
        }else{
            gameOver = true;
        }
    }

    player.Move();

    checkExplosion();

    writePlayerAway();
    writeBackground();
    writeTarget(); //displays target
    writePlayer();
    FastLED.show();
    checkWin();
    delay(10);
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

    };
