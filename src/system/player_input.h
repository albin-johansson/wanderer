#pragma once

#include <input.h>

#include "types.h"

namespace wanderer {

class PlayerInput final {
 public:
  void update(Registry& registry, const Input& input);

 private:
};

}  // namespace wanderer
