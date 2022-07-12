#include <memory>  // For shared_ptr

#include "controls/Button.h"

namespace controls::hardware {

class Context {
  public:
    virtual bool PollAll() = 0;
    virtual std::shared_ptr<Button> CreateButon(uint8_t pin1, uint8_t pin2 = 0) = 0;
};

}  // namespace controls::hardware
