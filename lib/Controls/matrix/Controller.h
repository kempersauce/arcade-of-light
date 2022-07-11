// Controller doesn't need to know about the context... calling PollAll on the context updates everything intelligently... I think

#include <memory>  // For std::shard_ptr
#include <vector>  // For std::vector

#include <Context.h>  // For controls::matrix::Context

namespace controls::matrix {

// Does this class do anything? Seems like it should be an implementation-specific struct of buttons
class Controller {
 public:

 private:
  std::vector<Input> buttons_;
};

}
