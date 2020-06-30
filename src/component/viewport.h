#pragma once

#include <area.h>
#include <rect.h>

#include <named_type.hpp>

#include "wanderer_stdinc.h"

namespace wanderer {

using ViewportEntity = fluent::
    NamedType<entt::entity, struct ViewportEntityTag, fluent::Comparable>;

struct Viewport final {
  ctn::FRect bounds{};
  ctn::FArea levelSize{};
};

}  // namespace wanderer
