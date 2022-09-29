#include "audio/beat_patterns/conga.h"   // for Conga
#include "audio/beat_patterns/reggae.h"  // for Reggae
#include "audio/beat_patterns/twist.h"   // for Twist
#include "audio/track.h"                 // for AudioTrack
#include "pins/pin_setup.h"              // for pins::Init()
#include "serial/debug.h"                // for Debug

using namespace kss;

audio::AudioTrack tracks[]{{0, &audio::Conga}};

void setup() {
  Debug_init();
  pins::Init();

  for (auto &track : tracks) {
    track.Play();
  }

  Debug("starting the loop");
}

void loop() {
  time::SetLoopTime();
  for (auto &track : tracks) {
    track.Update();
  }
}
