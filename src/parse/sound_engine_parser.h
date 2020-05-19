#pragma once

#include "sound_engine.h"
#include "wanderer_stdinc.h"

namespace wanderer {

class SoundEngineParser final {
 public:
  SoundEngineParser() = delete;

  static UniquePtr<SoundEngine> parse(CZString file);
};

}  // namespace wanderer