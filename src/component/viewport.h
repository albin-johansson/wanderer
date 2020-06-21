#pragma once

#include <area.h>
#include <rect.h>

#include <named_type.hpp>

#include "wanderer_stdinc.h"

namespace wanderer {

using ViewportEntity = fluent::
    NamedType<entt::entity, struct ViewportEntityTag, fluent::Comparable>;

struct Viewport final {
  centurion::FRect bounds{};
  centurion::FArea levelSize{};
};

}  // namespace wanderer
