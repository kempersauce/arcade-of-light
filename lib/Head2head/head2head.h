#include <Game.h>
#include <Constants.h>
#include <Button.h>
#include <Dot.h>
#include <H2HDisplay.h>
#include <H2HControls.h>
#include <SingleColorBG.h>

class H2HDot : public Dot
{
    public:
        int velocity;

        H2HDot(CRGB startColor, int startX, int startY, int xMaximum, int yMaximum)
        :Dot(startColor, startX, startY, xMaximum, yMaximum)
        {
            velocity = 1;
        }
        
        void vMove()
        {
            move(0, velocity);
        }

        void flip()
        {
            velocity *= -1;
        }
};

class H2HZone : public Animation
{
    public:
        CRGB color;
        int yMin;
        int yMax;
        int xLoc;

        H2HZone(CRGB startColor, int xLocation, int yMinimum, int yMaximum)
        {
            color = startColor;
            xLoc = xLocation;
            yMin = yMinimum;
            yMax = yMaximum;
        }

        bool checkZone(int x, int y)
        {
            bool result = false;
            if(x == xLoc)
            {
                if(y<=yMax && y>=yMin)
                {
                    result = true;
                }
            }
            return result;
        }
        
        void draw(Display* display)
        {
            for(int y=yMin; y<yMax; y++)
            {
                display->strips[xLoc][y] = color;
            }    
        }
};

class Head2Head : Game
{
    public:
        
        H2HDot** dots;
        H2HControls* controls;
        H2HZone** zoneA;
        H2HZone** zoneB;

        Head2Head(Display* gameDisplay)
            : Game(gameDisplay)
        {
        }

        void setup()
        {
            controls = (H2HControls*)new H2HControls();
            background = (Animation*)new SingleColorBG(25,25,0);
            dots = new H2HDot*[8] {
                new H2HDot(CRGB::Purple, 0, 15, 8, 120),
                new H2HDot(CRGB::Purple, 1, 15, 8, 120),
                new H2HDot(CRGB::Purple, 2, 15, 8, 120),
                new H2HDot(CRGB::Purple, 3, 15, 8, 120),
                new H2HDot(CRGB::Purple, 4, 15, 8, 120),
                new H2HDot(CRGB::Purple, 5, 15, 8, 120),
                new H2HDot(CRGB::Purple, 6, 15, 8, 120),
                new H2HDot(CRGB::Purple, 7, 15, 8, 120),
            };
            zoneA = new H2HZone*[8] {
                new H2HZone(CRGB::Blue, 0, 5, 15),
                new H2HZone(CRGB::Blue, 1, 5, 15),
                new H2HZone(CRGB::Blue, 2, 5, 15),
                new H2HZone(CRGB::Blue, 3, 5, 15),
                new H2HZone(CRGB::Blue, 4, 5, 15),
                new H2HZone(CRGB::Blue, 5, 5, 15),
                new H2HZone(CRGB::Blue, 6, 5, 15),
                new H2HZone(CRGB::Blue, 7, 5, 15)
            };

            zoneB = new H2HZone*[8] {
                new H2HZone(CRGB::Red, 0, 105, 115),
                new H2HZone(CRGB::Red, 1, 105, 115),
                new H2HZone(CRGB::Red, 2, 105, 115),
                new H2HZone(CRGB::Red, 3, 105, 115),
                new H2HZone(CRGB::Red, 4, 105, 115),
                new H2HZone(CRGB::Red, 5, 105, 115),
                new H2HZone(CRGB::Red, 6, 105, 115),
                new H2HZone(CRGB::Red, 7, 105, 115)
            };

        }

        void loop()
        {
            controls->pollAll();
            background->draw(display);
            checkTeam(controls->teamA, CRGB::Green, CRGB::Blue, true);
            checkTeam(controls->teamB, CRGB::Yellow, CRGB::Red, false);
            allMove();
            drawZones();
            drawDots();
            FastLED.setBrightness(50);
            FastLED.show();
        }

        void allMove()
        {
            for (int i = 0; i < 8; i++)
            {
                dots[i]->vMove();
            }
        }

        void checkTeam(Button** team, CRGB color1, CRGB color2, bool moveUp)
        {
            for (int i = 0; i < 8; i++)
            {
                if (team[i]->isPressed())
                {
                    for (int j = 0; j < display->lengthStrips; j++)
                    {
                        if(i==0||i==2||i==5||i==7){
                            display->strips[i][j] = color1;
                        }else{
                            display->strips[i][j] = color2;
                        }
                    }
                    if(zoneA[i]->checkZone((dots[i]->xLoc),(dots[i]->yLoc)))
                    {
                        dots[i]->velocity = 3;
                    }else if(zoneB[i]->checkZone((dots[i]->xLoc),(dots[i]->yLoc))){
                        dots[i]->velocity = -3;
                    }
                    for (int j = 0; j < display->lengthStrips; j++)
                    {
                        if(j<dots[i]->yLoc)
                        {
                            display->strips[i][j] = CRGB::Blue;
                        }
                        if(j>dots[i]->yLoc)
                        {
                            display->strips[i][j] = CRGB::Red;
                        }
                    }

                }

            }
        }
        void drawDots()
        {
            for(int i=0; i<8; i++)
            {
                dots[i]->draw(display);
            }
        }
        void drawZones()
        {
            for(int i=0; i<8; i++)
            {
                zoneA[i]->draw(display);
                zoneB[i]->draw(display);
            }
        }
};


// Target target(100,15,55,0,0); //the target
// Background background(0,NUM_LEDS,15,0,10);
//
// //Rainbow Animation
// CRGB rainbows[14] = {
//   CRGB::Red,
//   CRGB::Orange,
//   CRGB::Yellow,
//   CRGB::Green,
//   CRGB::Blue,
//   CRGB::Indigo,
//   CRGB::Violet,
//   CRGB::Red,
//   CRGB::Orange,
//   CRGB::Yellow,
//   CRGB::Green,
//   CRGB::Blue,
//   CRGB::Indigo,
//   CRGB::Violet
// };
// int iterator = 0;
//
// // Other variables
// int redColor = 0;
// int blueColor = 0;
// int greenColor = 0;
// int buttonUpState = LOW;
// int buttonUpStateOld = LOW;
//
// bool gameOver = false;
// bool newGame = true;
// bool newButtonPress = false;
//
// //LED strip
// CRGB leds[NUM_LEDS]; // This is an array of leds.  One item for each led in your strip.
//
// void checkWin() {
//     if(gameOver)
//     {
//         // Lose state
//         //change this to a fill
//         for (int i = 0; i < NUM_LEDS; i++){
//             leds[i].setRGB( 255, 0, 0);
//             FastLED.show();
//             delay(animationDelay);
//         }
//         delay(2000);
//         //Restart game
//         player.Loc = 0;
//         target.Height = 15;
//         target.Loc = 250;
//
//         gameOver = false;
//         newGame = true;
//     }
// }
//
//
// void checkButton()
// {
//
//
//     if(buttonUpState==HIGH && buttonUpStateOld==LOW)
//     {
//         newButtonPress=true;
//     }
//     else
//     {
//         newButtonPress=false;
//     }
//
// }
//
// void writeBackground()
// {
//     for(int i=background.Loc; i<=background.Height; i++)
//     {
//         leds[i].setRGB(background.Red, background.Green, background.Blue);
//     }
// }
//
// void moveTarget(){
//     int oldLoc = target.Loc;
//     int roll = random(0,100);
//     if(roll<15)
//     {
//         target.Height--;
//     }
//     if(player.Velocity > 0)
//     {
//         target.Loc = random(oldLoc+(oldLoc/4), (NUM_LEDS - target.Height));
//     } else {
//         target.Loc = random(0, oldLoc-(oldLoc/4));
//     }
// }
//
// void writeTarget() // Target fill
//     {
//     for (int i = target.Loc+1; i < target.Loc + target.Height; i++){
//
//         //Increase Color intensity on hit
//         if (target.inTarget == true)
//         {
//             leds[i].setRGB(target.Green,target.Red, target.Blue);
//         }else
//         {
//         leds[i].setRGB(10, 0, 0);
//         }
//     }
//     // Target bookends
//     leds[target.Loc].setRGB(target.Green, target.Red, target.Blue);
//     leds[target.Loc+target.Height].setRGB(target.Green,target.Red, target.Blue);
// }
//
// void writePlayerAway()
// {
//     leds[player.oldLoc].setRGB(0,0,0);// Remove old player dots
// }
//
// void writePlayer()
// {
//     leds[player.Loc].setRGB(player.Green, player.Red, player.Blue); // Player.
//
//     // int flame1 = player.Loc - 1;
//     // int flame2 = player.Loc - 2;
//     // int flame3 = player.Loc - 3;
//     // int flame4 = player.Loc - 4;
//     // //if velocity is negative, put flames on other side
//     // if (player.Velocity<0) {
//     //     flame1 = player.Loc + 1;
//     //     flame2 = player.Loc + 2;
//     //     flame3 = player.Loc + 3;
//     //     flame4 = player.Loc + 4;
//     // }
//
//     // leds[flame1].setRGB(255,255,0);
//     // leds[flame2].setRGB(191,255,0);
//     // leds[flame3].setRGB(128,255,0);
//     // leds[flame4].setRGB(0,100,0);
// }
//
// void checkExplosion()
// {
//     if (player.Loc >= NUM_LEDS+1 || player.Loc <= -1){
//         //Move this somewhere else or make player reset method
//         player.Loc=0;
//         player.Velocity=0;
//         target.Height = 15;
//         target.Loc = 185;
//
//         //red
//         int j=0;
//         while(j<70)
//         {
//             for (int i=1; i < NUM_LEDS ; i++)
//             {
//                 leds[i] = rainbows[(i%7)+iterator];
//             }
//             if (iterator < 6)
//             {
//                 iterator++;
//             }
//             else
//             {
//                 iterator = 0;
//             }
//             FastLED.show();
//             delay(delayval);
//             j++;
//         }
//         gameOver = true;
//     }
// }
//
// void checkTarget()
// {
//     if (player.Loc > target.Loc && player.Loc < (target.Loc + target.Height))
//     {
//         target.inTarget = true;
//     }
//
//     if (player.Loc < target.Loc || player.Loc > target.Loc + target.Height)
//     {
//         target.inTarget = false;
//     }
// }
//
// void setup() {
//     //Serial.begin(9600);
//     //while (!Serial) {
//     //    ; // wait for serial port to connect. Needed for native USB
//     //}
// 	// sanity check delay - allows reprogramming if accidently blowing power w/leds
//     delay(2000);
//     //initialize LED Strip
//     FastLED.addLeds<WS2812B, LED_PIN, RGB>(leds, NUM_LEDS);
//     //set player on strip
//     writeBackground();
//     leds[player.Loc].setRGB( player.Green, player.Red, player.Blue); // Player.
//     writeTarget();
//     FastLED.show();
// }
//
// //Game Loop
// void loop() {
//     // read if there is a new button press
//     // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
//     buttonUpStateOld = buttonUpState;
//     buttonUpState = Up.read();
//     checkButton();
//     if(player.Velocity==0 && newButtonPress)
//     {
//         player.Start();
//         newGame = false;
//     }else if (newButtonPress)
//     {
//         //writeBackground();
//         checkTarget();
//         if(target.inTarget)
//         {
//             player.Flip();
//             moveTarget();
//         }else{
//             gameOver = true;
//         }
//     }
//
//     player.Move();
//
//     checkExplosion();
//
//     writePlayerAway();
//     writeBackground();
//     writeTarget(); //displays target
//     writePlayer();
//     FastLED.show();
//     checkWin();
//     delay(10);
//     //Serial prints for debugging
//
//
//     /* Serial.print(player.Loc);  // prints a label
//     Serial.print("\t");         // prints a tab
//
//     Serial.print(player.oldLoc);  // prints a label
//     Serial.print("\t");         // prints a tab
//
//     Serial.print(player.Location);
//     Serial.print("\t");
//
//     Serial.print(player.Acceleration);
//     Serial.print("\t");
//
//     Serial.print(player.Velocity);
//     Serial.print("\t");
//
//     Serial.print(player.Thrust);
//     Serial.print("\t");
//
//     Serial.print(player.Time-player.oldTime);
//     Serial.println();
//  */
//
//     };
