#pragma once
#include <HardwareSerial.h>

#include "audio/audio_sender.h"  // for AudioSender

namespace kss {
namespace games {
namespace h2h {

class H2HAudio : public audio::AudioSender {
 public:
  // File names for single effects
  const char* aHit = "TRGTHIT2.WAV";
  const char* aMiss = "TRGTMIS1.WAV";     // CHEWY VS DIO VERSION:
  const char* aWinLane = "THRUST1.WAV";   //"THRUST1.WAV"; //"DIO.WAV";
  const char* aWinGame = "PONGWINA.WAV";  //"PONGWINA.WAV"; //"TOBECON.WAV;

  const char* bHit = "TRGTHIT5.WAV";
  const char* bMiss = "TRGTHIT4.WAV";
  const char* bWinLane = "THRUST2.WAV";   //"THRUST2.WAV"; //"CHEWY.WAV";
  const char* bWinGame = "PONGWINA.WAV";  //"CANTINA.WAV";

  const char* itsTimeToDuel = "CHALL.WAV";  // "DUEL.WAV"

  // File names for Background
  const char* winBG = "CDL.WAV";
  const char* stdBG = "GYCYCHIP.WAV";
  const char* idleBG = "PLUTO.WAV";

  // File names and controls for start/stop channels

  // CONSTRUCTOR - starts Serial (inhereted from AudioSender)
  H2HAudio() : AudioSender() {}

  // SINGLE EFFECT METHODS
  void playTeamAHit() { PlayWav(aHit); }
  void playTeamAMiss() { PlayWav(aMiss); }
  void playTeamAWinLane() {
    // hard coded this to channel so not to interfere with dot sounds
    PlayWav(aWinLane, 1);
  }
  void playTeamAWinGame() { setBackground(aWinGame); }

  void playTeamBHit() { PlayWav(bHit); }
  void playTeamBMiss() { PlayWav(bMiss); }
  void playTeamBWinLane() {
    // hard coded this to channel so not to interfere with dot sounds
    PlayWav(bWinLane, 1);
  }
  void playTeamBWinGame() {
    // hard coded this to channel so not to interfere with dot sounds
    setBackground(bWinGame);
  }

  void ItsTimeToDuel() { PlayWav(itsTimeToDuel); }

  // START/STOP METHODS
  void stopWinMusic() {
    StopChannel(1);
    StopChannel(2);
  }

  // CHANNEL 1: FireworkLaunch

  // BACKGROUND METHODS
  void playStdBG() { setBackground(stdBG); }
  void playWinBG() { setBackground(winBG); }
  void playH2HIdleBG() { setBackground(idleBG); }
  void playIdleBG() { setBackground(idleBG); }
};

}  // namespace h2h
}  // namespace games
}  // namespace kss
