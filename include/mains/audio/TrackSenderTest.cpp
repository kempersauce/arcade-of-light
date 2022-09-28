#include "audio/beat_patterns.h"  // for Twist
#include "audio/track.h"          // for AudioTrack
#include "pins/pin_setup.h"       // for pins::Init()
#include "serial/debug.h"         // for Debug

using namespace kss;

audio::AudioTrack tracks[]{{0, &audio::Twist},
                           {1, &audio::Twist},
                           {2, &audio::Twist},
                           {3, &audio::Twist}};

void setup() {
  Debug_init();
  pins::Init();

  for (auto& track : tracks) {
    track.Play();
  }

  Debug("starting the loop");
}

void loop() {
  for (auto& track : tracks) {
    track.Update();
  }
}
