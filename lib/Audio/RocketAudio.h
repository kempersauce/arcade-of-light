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

    // File names for gamestate changed

    // File names and controls for start/stop channels
    char* boost = "THRUST2";
    bool boostIsPlaying = false;
    char* targetHover = "TRGTSEQ";
    bool targetHoverIsPlaying = false;

    //Constructor Starts Serial (inhereted from AudioSender)
    RocketAudio()
        : AudioSender(){}

    // Single Effect Methods
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

    // Start/Stop Methods

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
        
        //playTargetWin();
    }


};