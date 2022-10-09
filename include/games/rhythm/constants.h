#pragma once

namespace kss {
namespace games {
namespace rhythm {

uint8_t kPlayerHues[4]{
    0,    // red
    45,   // yellow
    130,  // teal
    200,  // lavendar
};

uint8_t kPlayerOffhues[4]{
    128 + 0,    // not red
    128 + 45,   // not yellow
    128 + 130,  // not teal
    128 + 200,  // not lavendar
};

}  // namespace rhythm
}  // namespace games
}  // namespace kss
