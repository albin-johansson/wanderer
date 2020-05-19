#pragma once

#include "action_parser.h"
#include "menu.h"
#include "wanderer_stdinc.h"

namespace wanderer {

class MenuParser final {
 public:
  MenuParser() = delete;

  static UniquePtr<IMenu> parse(ActionParser& actionParser, CZString file);
};

}  // namespace wanderer
