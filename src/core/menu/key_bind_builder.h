#pragma once
#include "action_parser.h"
#include "key_bind.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class KeyBindBuilder final {
 public:
  KeyBindBuilder() = delete;

  static UniquePtr<KeyBind> build(ActionParser& actionParser,
                                  const JsonValue& json);
};

}  // namespace albinjohansson::wanderer
