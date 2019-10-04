#pragma once

#include <Arduino.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

class WavPlayer
{
    public:

    AudioControlSGTL5000 sgtl5000_1;
    AudioOutputI2S i2s1;
    
    AudioConnection audioConnection;

    AudioPlaySdWav      playSdWavBG;
    AudioPlaySdWav      testChannel;


    AudioPlaySdWav sound1;

    //AudioConnection patchCord1(sound1, 0, i2s1, 0);

    WavPlayer()
    {
        Serial.print("WavPlayer go!");
    }

    void setup()
    {
        
        Serial.begin(115200);
        AudioMemory(16);
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
        testChannel.play("HUMANITY.WAV");
        delay(5000);
        Serial.println("starting the loop");
    }

    void playBackgroundMusic(char* fileName)
    {
        if(!playSdWavBG.isPlaying())
        {
            playSdWavBG.play(fileName);
        }
    }

    void playWav(char* fileName)
    {
        for(int i=0; i< 6; i++)
        if(!sounds[i].isPlaying())
        {
            sounds[i].play(fileName);
        }

    }


};