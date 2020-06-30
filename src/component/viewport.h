#pragma once

#include <area.h>
#include <rect.h>

#include <named_type.hpp>

#include "wanderer_stdinc.h"

namespace wanderer {

struct Viewport final {
  using entity = fluent::
      NamedType<entt::entity, struct ViewportEntityTag, fluent::Comparable>;
  ctn::FRect bounds{};
  ctn::FArea levelSize{};
};

}  // namespace wanderer
