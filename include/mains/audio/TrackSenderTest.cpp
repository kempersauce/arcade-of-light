#include <utility>  // for std::pair

#include "audio/beat_patterns/all.h"  // for beats::*
#include "audio/score.h"              // for Score
#include "audio/track.h"              // for AudioTrack
#include "math/random.h"              // for random::*
#include "pins/pin_setup.h"           // for pins::Init()
#include "serial/debug.h"             // for Debug

using namespace kss;
using namespace kss::audio;
using namespace kss::audio::beats;

// Set this true to randomly switch beat tracks
constexpr bool should_switch_randomly{true};

AudioTrack tracks[]{{0, &Twist}};

constexpr size_t beats_count{13};
Score *scores[beats_count]{
    // clang-format off
	&Chachacha,
	&Closer,
	&Conga,
	&Disco1,
	&Disco2,
	&Fiddy,
	&Florian,
	&Hiphop1,
	&Mickey,
	&Procession,
	&Reggae,
	&Shuffle,
	&Twist
    // clang-format on
};

const char *score_names[beats_count]{
    // clang-format off
	NameOf(Chachacha),
	NameOf(Closer),
	NameOf(Conga),
	NameOf(Disco1),
	NameOf(Disco2),
	NameOf(Fiddy),
	NameOf(Florian),
	NameOf(Hiphop1),
	NameOf(Mickey),
	NameOf(Procession),
	NameOf(Reggae),
	NameOf(Shuffle),
	NameOf(Twist)
    // clang-format on
};

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
  if (should_switch_randomly && math::random::Bool(0.002)) {
    const size_t which = math::random::Int8(beats_count);
    Debug("Switching beat to " + score_names[which]);
    tracks[0].SwitchImmediatelyTo(scores[which]);
  }

  // Update the tracks
  for (auto &track : tracks) {
    track.Update();
  }
  delay(5);
}
