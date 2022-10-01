#pragma once

#include "audio/audio_sender.h"          // for AudioSender
#include "audio/background_music.h"      // for BackgroundMusic
#include "audio/manager.h"               // for audio::Manager
#include "audio/sound_effect.h"          // for SoundEffect
#include "audio/sound_effect_bespoke.h"  // for SoundEffectBespoke
#include "serial/hw_serials.h"           // for kHwSerials

namespace kss {
namespace games {
namespace h2h {

class H2HAudio : public audio::Manager {
 public:
  H2HAudio(uint8_t serial_no)
      : Manager(std::make_shared<audio::AudioSender>(
            serial::kHwSerials[serial_no])) {}

  // Single effects
  audio::SoundEffect aHit{sender, "TRGTHIT2.WAV"};
  audio::SoundEffect aMiss{sender, "TRGTMIS1.WAV"};  // CHEWY VS DIO VERSION:
  audio::SoundEffectBespoke aWinLane{sender, 1, "THRUST1.WAV"};  //"DIO.WAV"
  audio::BackgroundMusic aWinGame{sender, "PONGWINA.WAV"};       //"TOBECON.WAV

  audio::SoundEffect bHit{sender, "TRGTHIT5.WAV"};
  audio::SoundEffect bMiss{sender, "TRGTHIT4.WAV"};
  audio::SoundEffectBespoke bWinLane{sender, 1, "THRUST2.WAV"};  //"CHEWY.WAV"
  audio::BackgroundMusic bWinGame{sender, "PONGWINA.WAV"};       //"CANTINA.WAV"

  audio::SoundEffect itsTimeToDuel{sender, "TRBOTENS.WAV"};  //"DUEL.WAV"

  // Background music
  audio::BackgroundMusic winBG{sender, "CDL.WAV"};
  audio::BackgroundMusic stdBG{sender, "GYCYCHIP.WAV"};
  audio::BackgroundMusic idleBG{sender, "PLUTO.WAV"};

  // File names and controls for start/stop channels

  // SINGLE EFFECT METHODS
  void playTeamAHit() { aHit.Play(); }
  void playTeamAMiss() { aMiss.Play(); }
  void playTeamAWinLane() {
    // hard coded this to channel so not to interfere with dot sounds
    aWinLane.Play();
  }
  void playTeamAWinGame() { aWinGame.Play(); }

  void playTeamBHit() { bHit.Play(); }
  void playTeamBMiss() { bMiss.Play(); }
  void playTeamBWinLane() {
    // hard coded this to channel so not to interfere with dot sounds
    bWinLane.Play();
  }
  void playTeamBWinGame() {
    // hard coded this to channel so not to interfere with dot sounds
    bWinGame.Play();
  }

  void ItsTimeToDuel() { itsTimeToDuel.Play(); }

  // START/STOP METHODS
  void stopWinMusic() {
    sender->StopChannel(1);
    sender->StopChannel(2);
  }

  // CHANNEL 1: FireworkLaunch

  // BACKGROUND METHODS
  void playStdBG() { stdBG.Repeat(); }
  void playWinBG() { winBG.Repeat(); }
  void playH2HIdleBG() { idleBG.Repeat(); }
  void playIdleBG() { idleBG.Repeat(); }
};

}  // namespace h2h
}  // namespace games
}  // namespace kss
