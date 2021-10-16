#include "label_system.hpp"

#include <utility>  // move

namespace wanderer::sys {

void set_text(comp::Label& label, std::string text)
{
  label.text = std::move(text);
  label.texture.reset();
}

}  // namespace wanderer::sys
