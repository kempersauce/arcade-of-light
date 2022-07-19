#pragma once

#include <memory>  // For shared_ptr

#include <button.h>  // For Button

namespace kss {
namespace controls {
namespace hardware {

class Context {
  public:
    virtual void PollAll();
};

}  // namespace kss::controls::hardware
}  // namespace kss::controls
}  // namesapce kss
