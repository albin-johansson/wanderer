#pragma once

#include <entt.hpp>

#include "entity_type.hpp"

namespace wanderer::comp {
namespace detail {
struct chase_entity_t;
}

struct chase final
{
  using entity = entity_type<detail::chase_entity_t>;

  entt::entity target;
  float range;
};

}  // namespace wanderer::comp
