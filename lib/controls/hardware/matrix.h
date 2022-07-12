#include <map>

#include <memory>  // For shared_ptr

#include "controls/button.h"  // For Button
#include "controls/hardware/context.h"  // For Context

namespace controls::hardware {

class Matrix : public Context {
 public:
    
  using InputChannel = std::map<uint8_t, std::shared_ptr<Button>>;
  using InputMatrix = std::map<uint8_t, InputChannel>;
  
  override std::shared_ptr<Button> CreateButton(const uint8_t channel, const uint8_t pin);

  override void PollAll();

 private:
  // Using pin 0 as a dummy null pin
  uint8_t active_pin_{0};  // TODO - is there such a thing as pin 0? or should we revisit this?

  InputMatrix inputs_;

  // Switch to the appropriate pin (if we need to, avoiding extra switching)
  void SetActiveChannel(const uint8_t channel);
}

} // namespace controls::matrix