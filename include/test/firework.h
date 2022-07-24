// #define NUM_FIREWORKS 3

// #include <FancyFirework.h>
// #include "games/game.h"  // for Game
// #include "display/display.h"  // for Display
// #include "games/rocket/starscape.h"  // for Starscape
// #include "games/rocket/sky_fade.h"  // for SkyFade

// class FireworkGame : Game
// {
//     // Backgrounds
//     Starscape* starBackground; // just drawing black empty space for now. we
//     are alone in the universe SkyFade* skyFade;

//     FancyFirework firework[NUM_FIREWORKS]; // win animation fireworks

// public:
//     FireworkGame(Display* display)
//         : Game(display)
//     {
//         starBackground = new Starscape(display->numStrips,
//         display->lengthStrips, 175); skyFade = new SkyFade(new CRGB(0, 0,
//         255));
//     }

//     void setup()
//     {
//         for (int i = 0; i < NUM_FIREWORKS; i++)
//         {
//             firework[i] = FancyFirework();
//         };
//     }

//     //Game Loop
//     void loop()
//     {
//         starBackground->draw(display);

//         //draw blue sky fade over the stars
//         skyFade->draw(display);
//         for (int i = 0; i < NUM_FIREWORKS; i++)
//         {
//             firework[i].Move();
//             firework[i].draw(display);
//         }
//     }
// };
