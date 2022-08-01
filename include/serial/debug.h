#pragma once

#ifdef DEBUG
#include <HardwareSerial.h>  // for HardwareSerial
#endif

// Start serial if we're in debug mode (idk this doesnt work for some reason)
// #ifdef DEBUG
// Serial.begin(9600);
// #endif

namespace debug {

inline void println(const char* msg) {
    #ifdef DEBUG
    Serial.println(msg);
    #endif
}

inline void print(const char* msg) {
    #ifdef DEBUG
    Serial.print(msg);
    #endif
}

inline void println(const String& msg) {
    #ifdef DEBUG
    Serial.println(msg);
    #endif
}

inline void print(const String& msg) {
    #ifdef DEBUG
    Serial.print(msg);
    #endif
}

} // namespace Debug
