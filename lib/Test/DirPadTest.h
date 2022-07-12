#pragma once

#include <Game.h>
#include <Constants.h>
#include <SingleColorBG.h>
#include <Dot.h>
#include <DirPad.h>
#include <HueRainbow.h>

//Test for Directional Pad
class DirPadTest : Game
{
    public:

        DirPad controls;
        Dot* player;
        SingleColorBG* backgroundColor;
        HueRainbow rainbow;

        DirPadTest(Display* gameDisplay, DirPad controls)
            : Game(gameDisplay),
			controls{std::move(controls)},
			rainbow(2)
        {
            rainbow.setWaveShift(true);
        }

        void setup()
        {
        }

        void loop()
        {
            if (controls.up.IsPressed())
            {
                Serial.println("UP DIR BUTTON PRESSED");
                int newSpeed;
                int currentSpeed = rainbow.ShiftSpeed;
                if (currentSpeed < 20)
                {
                    newSpeed = currentSpeed + 1;
                }
                else
                {
                    newSpeed = 20;
                }


                rainbow.setSpeed(newSpeed);
            }

            if (controls.down.IsPressed())
            {
                Serial.println("DOWN DIR BUTTON PRESSED");
                int newSpeed;
                int currentSpeed = rainbow.ShiftSpeed;
                if (currentSpeed > -20)
                {
                    newSpeed = currentSpeed - 1;
                }

                rainbow.setSpeed(newSpeed);
                Serial.println("new speed:");
                //Serial.println(rainbow.ShiftSpeed);
            }

            if (controls.left.IsPressed())
            {
                Serial.println("LEFT DIR BUTTON PRESSED");
            }

            if (controls.right.IsPressed())
            {
                Serial.println("RIGHT DIR BUTTON PRESSED");
            }

            if (controls.a.IsPressed())
            {
                rainbow.setWaveShift(true);
                Serial.println("B BUTTON PRESSED");
            }

            if (controls.b.IsPressed())
            {
                rainbow.setWaveShift(false);
                Serial.println("A BUTTON PRESSED");
            }

            // if (!(//controls.a.IsPressed() &&
            // //controls.b.IsPressed() &&
            // controls.up.IsPressed() &&
            // controls.down.IsPressed() &&
            // controls.left.IsPressed() &&
            // controls.right.IsPressed()))
            // {
            //     //Serial.println("no Buttons pressed");
            // }

            rainbow.draw(display);
        }
};
