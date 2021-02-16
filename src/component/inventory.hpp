#pragma once

#include <vector>  // vector

#include "entity_type.hpp"
#include "item.hpp"

namespace wanderer::comp {
namespace detail {
struct inventory_entity_t;
}

struct inventory final
{
  using entity = entity_type<detail::inventory_entity_t>;
  std::vector<item::entity> items;  ///< List of items in the inventory.
  int capacity;                     ///< Maximum capacity of inventory.
};

struct active_inventory final
{};

}  // namespace wanderer::comp
