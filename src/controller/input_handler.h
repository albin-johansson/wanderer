#pragma once
#include "ctn_key_listener.h"

namespace wanderer::controller {

class InputHandler : public centurion::input::IKeyListener {
 public:
  void KeyStateUpdated(const centurion::input::KeyState& state) override;

};

} // namespace wanderer::controller