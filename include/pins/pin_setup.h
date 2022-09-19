#pragma once

#if defined(ARDUINO_TEENSY41)
#include "pins/pin_setup_teensy41.h"
#elif defined(ARDUINO_TEENSY40)
#include "pins/pin_setup_teensy40.h"
#elif defined(ARDUINO_TEENSY36)
#include "pins/pin_setup_teensy36.h"
#endif
