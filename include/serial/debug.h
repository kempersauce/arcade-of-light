#pragma once

#ifdef KSS_DEBUG

#include <SerialFlash.h>  // for Serial

#include "serial/constants.h"  // for kBaudRate
#include "time/now.h"          // for Now

#define __DEBUG_INFO \
  ((String)__FILE__ + ": " + __func__ + " (line " + __LINE__ + "): ")

#define Debug(msg) (debug::println(__DEBUG_INFO + msg))
#define Debug_print(msg) (debug::print((String)msg))
#define Debug_endl() (debug::println())
#define Debug_init() (debug::Init())

#else
#define Debug(whateveridgaf)
#define Debug_print(whateveridgaf)
#define Debug_endl()
#define Debug_init()
#endif

#define Debug_here() Debug("Here I am! time=" + kss::time::Now())
#define Debug_print_info() Debug_print(__DEBUG_INFO)
#define Debug_var(var) (Debug(#var + "=" + (var)))
#define Debunny() Debug("\n(\\_/)\n(0.@)\n(\")(\")")

namespace debug {

inline void println() {
#ifdef KSS_DEBUG
  Serial.println();
#endif
}

inline void println(const char* msg) {
#ifdef KSS_DEBUG
  Serial.println(msg);
#endif
}

inline void print(const char* msg) {
#ifdef KSS_DEBUG
  Serial.print(msg);
#endif
}

inline void println(const String& msg) {
#ifdef KSS_DEBUG
  Serial.println(msg);
#endif
}

inline void print(const String& msg) {
#ifdef KSS_DEBUG
  Serial.print(msg);
#endif
}

// Start serial if we're in debug mode (idk this doesnt work for some reason)
inline void Init() {
#ifdef KSS_DEBUG
  Serial.begin(kss::serial::kBaudRate);
  delay(5000);  // Wait for serial to actually start
  Debug("Beginning serial debug, baud rate=" + kss::serial::kBaudRate);
  Debunny();
  Debug_here();
#endif
}

}  // namespace debug
