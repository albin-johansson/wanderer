#include "label_system.hpp"

#include <utility>  // move

namespace wanderer::sys {

void SetText(Label& label, std::string text)
{
  label.text = std::move(text);
  label.texture.reset();
}

}  // namespace wanderer::sys
