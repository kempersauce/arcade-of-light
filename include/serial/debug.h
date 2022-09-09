#pragma once

// This enables/disables building debug-type stuff into the project
#define DEBUG 1337

#ifdef DEBUG
#include <HardwareSerial.h>  // for HardwareSerial
#define Debug(msg)                                                            \
  (debug::println((String)__FILE__ + ": " + __func__ + " (line " + __LINE__ + \
                  "): " + msg))
#endif

namespace debug {

constexpr uint32_t kBaudRate{115200};

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

// Start serial if we're in debug mode (idk this doesnt work for some reason)
inline void Init() {
#ifdef DEBUG
  Serial.begin(kBaudRate);
  println((String) "Beginning serial debug, baud rate=" + kBaudRate);
#endif
}

}  // namespace debug
