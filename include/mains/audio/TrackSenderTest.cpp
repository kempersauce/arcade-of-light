#include "audio/beat_patterns/conga.h"   // for Conga
#include "audio/beat_patterns/reggae.h"  // for Reggae
#include "audio/beat_patterns/twist.h"   // for Twist
#include "audio/score.h"                 // for Score
#include "audio/track.h"                 // for AudioTrack
#include "math/random.h"                 // for random::*
#include "pins/pin_setup.h"              // for pins::Init()
#include "serial/debug.h"                // for Debug

using namespace kss;

audio::Score *scores[3]{&audio::Conga, &audio::Twist, &audio::Reggae};
audio::AudioTrack tracks[]{{0, &audio::Conga}};

void setup() {
  Debug_init();
  pins::Init();

  time::SetLoopTime();
  for (auto &track : tracks) {
    track.Play();
  }

  Debug("starting the loop");
}

void loop() {
  time::SetLoopTime();
  if (math::random::Bool(0.002)) {
    const size_t which = math::random::Int8(3);
    Debug("Switching beat to scores[" + which + "]");
    tracks[0].SwitchImmediatelyTo(scores[which]);
  }
  for (auto &track : tracks) {
    track.Update();
  }
  delay(5);
}
