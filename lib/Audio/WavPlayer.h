#pragma once

#include <Arduino.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Button.h>

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

class WavPlayer
{
    public:

    HardwareSerial serial = Serial4;

    WavPlayer()
    {
        Serial4.begin(9600);
    }

    void setup()
    {
        
        
    }

    void playWav(const char* fileName)
    {
        String finalString = "<" + (String)fileName + ">";
        serial.println(finalString);
    }

    void playWavWhileHeld(Button* button, const char* fileName)
    {
        while(button->isDepressing)
        {
            playWav(fileName);
        }
    }


};