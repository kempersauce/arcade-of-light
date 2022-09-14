#pragma once

// This enables/disables building debug-type stuff into the project
#define __DEBUG 1337

#ifdef __DEBUG

#include <HardwareSerial.h>  // for HardwareSerial

#define __DEBUG_INFO \
  ((String)__FILE__ + ": " + __func__ + " (line " + __LINE__ + "): ")

#define Debug(msg) (debug::println(__DEBUG_INFO + msg))
#define Debug_print(msg) (debug::print((String)msg))
#define Debug_endl() (debug::println())

#else
#define Debug(whateveridgaf)
#define Debug_print(whateveridgaf)
#define Debug_endl()
#endif

#define Debug_here() (Debug("Here I am! time=" + millis()))
#define Debug_print_info() (Debug_print(__DEBUG_INFO))
#define Debunny() (Debug("\n(\\_/\)\n(0.@\)\n(\"\)(\"\)"))

namespace debug {

constexpr uint32_t kBaudRate{9600};

inline void println() {
#ifdef __DEBUG
  Serial.println();
#endif
}

inline void println(const char* msg) {
#ifdef __DEBUG
  Serial.println(msg);
#endif
}

inline void print(const char* msg) {
#ifdef __DEBUG
  Serial.print(msg);
#endif
}

inline void println(const String& msg) {
#ifdef __DEBUG
  Serial.println(msg);
#endif
}

inline void print(const String& msg) {
#ifdef __DEBUG
  Serial.print(msg);
#endif
}

// Start serial if we're in debug mode (idk this doesnt work for some reason)
inline void Init() {
#ifdef __DEBUG
  Serial.begin(kBaudRate);
  delay(5000);  // Wait for serial to actually start
  Debug("Beginning serial debug, baud rate=" + kBaudRate);
  Debug_here();
  Debunny();
#endif
}

}  // namespace debug
