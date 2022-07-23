#pragma once
#include <AudioSender.h>
#include <HardwareSerial.h>
class H2HAudio : public AudioSender {
 public:
  // File names for single effects
  char* aHit = "TRGTHIT2";
  char* aMiss = "TRGTMIS1";            // CHEWY VS DIO VERSION:
  char* aWinLane = "<11THRUST1.WAV>";  //"<11THRUST1.WAV>"; //"<11DIO.WAV>";
  char* aWinGame = "PONGWINA";  //"PONGWINA";                      //"TOBECON";

  char* bHit = "TRGTHIT5";
  char* bMiss = "TRGTHIT4";
  char* bWinLane = "<11THRUST2.WAV>";  //"<21THRUST2.WAV>"; //"<21CHEWY.WAV>";
  char* bWinGame = "PONGWINA";         //"CANTINA";

  // File names for Background
  char* winBG = "CDL";
  char* stdBG = "GYCYCHIP";
  char* idleBG = "PLUTO";

  // File names and controls for start/stop channels

  // CONSTRUCTOR - starts Serial (inhereted from AudioSender)
  H2HAudio() : AudioSender() {}

  // SINGLE EFFECT METHODS
  void playTeamAHit() { playWav(aHit); }
  void playTeamAMiss() { playWav(aMiss); }
  void playTeamAWinLane() {
    // hard coded this to channel so not to interfere with dot sounds
    sendMsg(aWinLane);
  }
  void playTeamAWinGame() { setBackground(aWinGame); }

  void playTeamBHit() { playWav(bHit); }
  void playTeamBMiss() { playWav(bMiss); }
  void playTeamBWinLane() {
    // hard coded this to channel so not to interfere with dot sounds
    sendMsg(bWinLane);
  }
  void playTeamBWinGame() {
    // hard coded this to channel so not to interfere with dot sounds
    setBackground(bWinGame);
  }

  void itsTimeToDuel() {
    // playWav("DUEL");
    sendMsg("<CHALL.WAV>");  //"<CHALL.WAV>"
  }

  // START/STOP METHODS
  void stopWinMusic() {
    sendMsg("<10>");
    sendMsg("<20>");
  }

  // CHANNEL 1: FireworkLaunch

  // BACKGROUND METHODS
  void playStdBG() { setBackground(stdBG); }
  void playWinBG() { setBackground(winBG); }
  void playH2HIdleBG() { setBackground(idleBG); }
  void playIdleBG() { setBackground(idleBG); }
};