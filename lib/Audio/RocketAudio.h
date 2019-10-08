#pragma once
#include <AudioSender.h>
#include <HardwareSerial.h>
class RocketAudio : public AudioSender
{

    public:
    // File names for single effects
    char* explosion =   "HUMANITY";
    char* win =         "BOOM";
    char* targetWin =   "<TRGTHIT5.WAV>";
    char* levelWin =    "<YUGI.WAV>";

    // File names for Background
    char* winBG =       "MAMBO5";
    char* stdBG =       "GYCYCHIP";

    // Level Intro Sounds
    char* level1Intro = "<WARUDO.WAV>";
    char* level2Intro = "<CHEWY.WAV>";
    char* level3Intro = "<MWATCHA.WAV>";
    char* level4Intro = "<FFWIN.WAV>";
    char* level5Intro = "<FUEL100.WAV>";

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
        sendMsg(targetWin);
    }
    void playLevelWin()
    {
        serial.println(levelWin);
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

    void playLevelIntro(int levelNum)
    {
        switch(levelNum)
        {
            case 1:
                sendMsg(level1Intro);
            break;
            case 2:
                sendMsg(level2Intro);
            break;
            case 3:
                sendMsg(level3Intro);
            break;
            case 4:
                sendMsg(level4Intro);
            break;
            case 5:
                sendMsg(level5Intro);
            break;            
        }
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