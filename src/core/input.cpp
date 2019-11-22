#include "input.h"
#include "objects.h"
#include <utility>

using namespace wanderer::controller;

namespace wanderer::core {

Input::Input(KeyStateManager_sptr keyStateManager, MouseStateManager_sptr mouseStateManager) {
  this->keyStateManager = Objects::RequireNonNull(std::move(keyStateManager));
  this->mouseStateManager = Objects::RequireNonNull(std::move(mouseStateManager));
}

Input::~Input() = default;

}
