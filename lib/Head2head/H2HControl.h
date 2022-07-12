#include <memory>  // For shared_ptr

#include <button.h>

struct H2HControl {
    std::shared_ptr<Button> buttons[8];
};
