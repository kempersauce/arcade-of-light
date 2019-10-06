#pragma once
#include <AudioSender.h>

class RocketAudio : public AudioSender
{

    public:
    // File names for single effects
    char* explosion =   "EXPLODE1";
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
    bool targetHoverIsPlaying = false;

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
            startWavOnChannel(targetHover, 2);
            targetHoverIsPlaying = true;
        }
    }

    void stopPlayTargetHover()
    {
        stopWavOnChannel(2);
        targetHoverIsPlaying = false;
    }


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