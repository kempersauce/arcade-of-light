#pragma once
#include <AudioSender.h>
#include <HardwareSerial.h>
class LifeAudio : public AudioSender
{

    public:
    // File names for single effects
    char* shuffle =     "<11GYCYCHIP.WAV>";
    char* stop =        "WARUDO";
    char* speedUp =     "<11DIO.WAV>";
    char* speedDown =   "<11TGTHIT1.WAV>";
    char* colorShift =  "<21AFRICA.WAV>";

    // File names for Background
    char* stdBG =       "MAMBO5";
    char* idleBG =      "CDL";

    // File names and controls for start/stop channels
    


    // CONSTRUCTOR - starts Serial (inhereted from AudioSender)
    LifeAudio()
        : AudioSender(){}

    // SINGLE EFFECT METHODS
    void playStop()
    {
        playWav(stop);
    }
    void startRandom()
    {
        sendMsg(shuffle);
    }
    void startSpeedUp()
    {
        sendMsg(speedUp);
    }
    void startSpeedDown()
    {
        sendMsg(speedDown);
    }
    void playColorShift()
    {
        sendMsg(colorShift);
    }



    // START/STOP METHODS
    void stopChannels()
    {
        sendMsg("<10>");
        sendMsg("<20>");
    }
    void stopPlayRandom()
    {
        sendMsg("<10>");
    }
    void stopColorShift()
    {
        sendMsg("<20>");
    }

    //CHANNEL 1: FireworkLaunch

    //BACKGROUND METHODS
    void playStdBG()
    {
        setBackground(stdBG);
    }
    void playH2HIdleBG()
    {
        setBackground(idleBG);
    }
};