#include <memory>  // For shared_ptr

#include "controls/hardware/context.h"  // For Context

namespace controls::hardware {

class Simple : public Context {
  public:
  
    using InputMap = std::map<uint8_t, std::shared_ptr<Button>>;

    override std::shared_ptr<Button> CreateButton(uint8_t pin, uint8_t unused = 0);

    override void PollAll();

  private:
    InputMap inputs_;
};

}  // namespace controls::hardware
