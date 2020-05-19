#pragma once
#include "action_parser.h"
#include "menu_button.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class MenuButtonParser final {
 public:
  MenuButtonParser() = delete;

  static UniquePtr<MenuButton> parse(ActionParser& actionParser,
                                     const JsonValue& json,
                                     int row);
};

}  // namespace albinjohansson::wanderer
