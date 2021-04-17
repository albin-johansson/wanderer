#pragma once

#include <vector>  // vector

#include "core/aliases/entity_type.hpp"
#include "core/aliases/ints.hpp"
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

void serialize(auto& archive, inventory& i, u32 version)
{
  archive(i.items, i.capacity);
}

void serialize(auto&, active_inventory&, u32 version)
{}

}  // namespace wanderer::comp
