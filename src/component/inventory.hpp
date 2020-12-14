#pragma once

#include <vector>  // vector

#include "entity_type.hpp"

namespace wanderer::comp {
namespace detail {
struct inventory_entity_t;
}

struct inventory final
{
  using entity = entity_type<detail::inventory_entity_t>;
  std::vector<entt::entity> items;  ///< List of items in the inventory.
  int capacity;                     ///< Maximum capacity of inventory.
};

}  // namespace wanderer::comp
