#pragma once
#include "action_parser.h"
#include "key_bind.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class KeyBindParser final {
 public:
  KeyBindParser() = delete;

  static UniquePtr<KeyBind> parse(ActionParser& actionParser,
                                  const JSONValue& json);
};

}  // namespace albinjohansson::wanderer
