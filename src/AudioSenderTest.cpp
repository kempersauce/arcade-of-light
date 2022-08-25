// #include <Arduino.h>
// #include <SPI.h>

// #include <memory>  // for std::shared_ptr

// #include "audio/audio_sender.h"          // for AudioSender
// #include "audio/background_music.h"      // for BackgroundMusic
// #include "audio/manager.h"               // for audio::Manager
// #include "audio/sound_effect.h"          // for SoundEffect
// #include "audio/sound_effect_bespoke.h"  // for SoundEffectBespoke
// #include "serial/debug.h"

// using namespace kss::audio;

// // Sub-manager handles level-specific sounds
// class SubManager : public Manager {
//  public:
//   SoundEffect effect;
//   SoundEffectBespoke bespoke;
//   BackgroundMusic background;

//   SubManager(std::shared_ptr<AudioSender> sender, const char* effect,
//              const char* bespoke, const char* background)
//       : Manager(sender),
//         effect{sender, effect},
//         bespoke{sender, 1, bespoke},
//         background{sender, background} {}
// };

// class Tester : Manager {
//  public:
//   SoundEffect effect{sender, "EXPLODE1.WAV"};
//   SoundEffectBespoke bespoke{sender, 1, "EARTHVOX.WAV"};
//   BackgroundMusic background{sender, "EARTH.WAV"};

//   SubManager sub{sender, "BOOM.WAV", "MOONVOX.WAV", "MOONJAZZ.WAV"};
// };

// Tester tester;

// uint32_t start_time;

// void setup() {
//   Serial.begin(115200);
//   delay(5000);  // we need to wait for Serial to initialize or whatever
//   start_time = millis();
//   debug::println("::::SETUP Achieved::::");
// }

// void loop() {
//   if (millis() - start_time <= 30000) {
//     if (!tester.background.is_playing) {
//       tester.background.Play();
//       tester.background.Play();
//     }
//     tester.bespoke.Play();
//     tester.bespoke.Play();
//     tester.effect.Play();
//     tester.effect.Play();
//   } else {
//     if (!tester.sub.background.is_playing) {
//       tester.sub.background.Play();
//       tester.sub.background.Play();
//     }
//     tester.sub.bespoke.Play();
//     tester.sub.bespoke.Play();
//     tester.sub.effect.Play();
//     tester.sub.effect.Play();
//   }
//   delay(1000);

//   debug::println("-=- Loops, Brother -=-");
// }