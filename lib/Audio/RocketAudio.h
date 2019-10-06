#pragma once
#include <AudioSender.h>
#include <HardwareSerial.h>
class RocketAudio : public AudioSender
{

    public:
    // File names for single effects
    char* explosion =   "HUMANITY";
    char* win =         "BOOM";
    char* targetWin =   "TRGTHIT5";
    char* levelWin =    "WHOOSH";

    // File names for Background
    char* winBG =       "MAMBO5";
    char* stdBG =       "GYCYCHIP";

    // File names and controls for start/stop channels
    char* boost = "THRUST2";
    bool boostIsPlaying = false;
    char* targetHover = "TRGTSEQ";
    char* targetHoverFull = "<21TRGTSEQ.WAV>";
    bool targetHoverIsPlaying = false;
    char* fireworkLaunch = "WHOOSH";
    char* fireworkLaunchLong = "<WHOOSH.WAV>";
    bool fireworkLaunchIsPlaying = false;
    char* fireworkExplode = "EXPLODE1";
    char* fireworkExplodeLong = "<EXPLODE1.WAV>";


    // CONSTRUCTOR - starts Serial (inhereted from AudioSender)
    RocketAudio()
        : AudioSender(){}

    // SINGLE EFFECT METHODS
    void playExplosion()
    {
        playWav(explosion);
    }
    void playWin()
    {
        playWav(win);
    }
    void playTargetWin()
    {
        playWav(targetWin);
    }
    void playLevelWin()
    {
        playWav(levelWin);
    }
    void playLevelIntro()
    {
        //playWav()
    }
    void playFireWorkLaunch()
    {
        sendMsg(fireworkLaunchLong);
    }
    void playFireWorkExplode()
    {
        sendMsg(fireworkExplodeLong);
    }


    // START/STOP METHODS

    // CHANNEL 1: BOOST
    void startPlayBoost()
    {
        if(!boostIsPlaying)
        {
            startWavOnChannel(boost, 1);
            boostIsPlaying = true;
        }
    }
    void stopPlayBoost()
    {
        stopWavOnChannel(1);
        boostIsPlaying = false;
    }

    // CHANNEL 2: TARGET
    void startPlayTargetHover()
    {
        if(!targetHoverIsPlaying)
        {
            sendMsg(targetHoverFull);
            targetHoverIsPlaying = true;
        }
    }
    void stopPlayTargetHover()
    {
        sendMsg("<20>");
        targetHoverIsPlaying = false;
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
};