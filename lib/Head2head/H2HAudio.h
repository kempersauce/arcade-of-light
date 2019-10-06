#pragma once
#include <AudioSender.h>
#include <HardwareSerial.h>
class H2HAudio : public AudioSender
{

    public:
    // File names for single effects
    char* aHit =        "TRGTHIT2";
    char* aMiss =       "TRGTHIT5";
    char* aWinLane =    "<11DIO.WAV>";
    char* aWinGame =    "TOBECON";

    char* bHit =        "TRGTHIT1";
    char* bMiss =       "TRGTHIT6";
    char* bWinLane =    "<21CHEWY.WAV>";
    char* bWinGame =    "CANTINA";

    // File names for Background
    char* winBG =       "CDL";
    char* stdBG =       "GYCYCHIP";
    char* idleBG =      "CDL";

    // File names and controls for start/stop channels
    


    // CONSTRUCTOR - starts Serial (inhereted from AudioSender)
    H2HAudio()
        : AudioSender(){}

    // SINGLE EFFECT METHODS
    void playTeamAHit()
    {
        playWav(aHit);
    }
    void playTeamAMiss()
    {
        playWav(aMiss);
    }
    void playTeamAWinLane()
    {
        //hard coded this to channel so not to interfere with dot sounds
        sendMsg(aWinLane);
    }
    void playTeamAWinGame()
    {
        setBackground(aWinGame);
    }

    void playTeamBHit()
    {
        playWav(bHit);
    }
    void playTeamBMiss()
    {
        playWav(bMiss);
    }
    void playTeamBWinLane()
    {
        //hard coded this to channel so not to interfere with dot sounds
        sendMsg(bWinLane);
    }
    void playTeamBWinGame()
    {
        //hard coded this to channel so not to interfere with dot sounds
        setBackground(bWinGame);
    }


    // START/STOP METHODS
    void stopWinMusic()
    {
        sendMsg("<10>");
        sendMsg("<20>");
    }

    //CHANNEL 1: FireworkLaunch

    //BACKGROUND METHODS
    void playStdBG()
    {
        setBackground(stdBG);
    }
    void playWinBG()
    {
        setBackground(winBG);
    }
    void playH2HIdleBG()
    {
        setBackground(idleBG);
    }
};