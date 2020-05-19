#pragma once

#include "action_parser.h"
#include "menu.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class MenuBuilder final {
 public:
  MenuBuilder() = delete;

  static UniquePtr<IMenu> build(ActionParser& actionParser, CZString file);
};

}  // namespace albinjohansson::wanderer
