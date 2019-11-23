#include "input.h"
#include "objects.h"
#include <utility>

namespace albinjohansson::wanderer {

Input::Input(KeyStateManager_sptr keyStateManager, MouseStateManager_sptr mouseStateManager) {
  this->keyStateManager = Objects::RequireNonNull(std::move(keyStateManager));
  this->mouseStateManager = Objects::RequireNonNull(std::move(mouseStateManager));
}

Input::~Input() = default;

}
