#pragma once

#include <rect.h>

#include <vector>

#include "wanderer_stdinc.h"

namespace wanderer {

struct Hitbox final {
  using entity = fluent::NamedType<entt::entity, struct HitboxEntityTag>;
  ctn::FRect bounds;
  std::vector<ctn::FRect> boxes;
};

}  // namespace wanderer