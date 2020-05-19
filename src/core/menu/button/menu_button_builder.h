#pragma once
#include "action_parser.h"
#include "menu_button.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class MenuButtonBuilder final {
 public:
  MenuButtonBuilder() = delete;

  static UniquePtr<MenuButton> build(ActionParser& actionParser,
                                     const JsonValue& json,
                                     int row);
};

}  // namespace albinjohansson::wanderer
