#pragma once

#include <Arduino.h>

class AudioSender
{

    public:
    const char* startSymbol = "<";
    const char* endSymbol = ".WAV>";
    const char* startChar = "1";
    const char* stopChar = "0";
    const char* one = "1";
    const char* two = "2";
    unsigned long delayStartMillis;
    bool delayHasStarted = false;
    bool delaySoundPlayed = false;

    // Constructor: starts serial connection to audioSlave
    AudioSender()
    {
        Serial5.begin(9600);
    }

    //send message over serial to audioslave
    void sendMsg(const char* msg)
    {
        Serial5.println(msg);
    }

    //prepare message for audioslave to play audio file
    void playWav(char* fileName)
    {
        char finalMsg[12];
        strcpy(finalMsg, startSymbol);
        strcat(finalMsg, fileName);
        strcat(finalMsg, endSymbol);
        Serial.println(finalMsg);
        Serial5.println(finalMsg);
    }

    // Methods for starting/stopping wav on specific channel
    // currently, only channels 1 & 2 support this function
    void startWavOnChannel(char* fileName, int channelNum)
    {
        char msg[12];
        strcpy(msg, getChannelChar(channelNum));
        strcat(msg, startChar);
        strcat(msg, fileName);
        playWav(msg);
    }

    void stopWavOnChannel(int channelNum)
    {
        char msg[12];
        strcpy(msg, getChannelChar(channelNum));
        strcat(msg, stopChar);
        playWav(msg);
    }

    //helper function because I'm bad at C++ and char array concatination
    const char* getChannelChar(int channelNum)
    {
        char msg[12];
        if(channelNum == 1)
        {
            return one;
        }
        else if(channelNum ==2)
        {
            return two;
        }
        else
        {
            Serial.println("BAD CHANNEL NUMBER: " + (String)channelNum);
            return;
        }
    }

    // play sound after x milliseconds 
    // this method must be continuously called until end of delay
    // p.s. also, only ONE instance of this can be running at once, sorry :( -Jon
    // p.p.s. the more I think about it, this method kind of sucks, so try not to use it...
    void playAfterDelay(char* fileName, int delayMillis)
    {
        if(!delayHasStarted && !delaySoundPlayed)
        {
            delayStartMillis = millis();
            delayHasStarted = true;
        }
        else if(!delaySoundPlayed)
        {
            unsigned long currentMillis = millis();
            if(currentMillis - delayStartMillis)
            {
                playWav(fileName);
                delayHasStarted = false;
                delaySoundPlayed = true;
            }
        }        
    }
    

};