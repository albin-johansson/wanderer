#pragma once

#include <vector>  // vector

#include "common/entity_type.hpp"
#include "common/ints.hpp"
#include "item.hpp"

namespace wanderer::comp {

namespace tags {
struct inventory_tag;
}  // namespace tags

struct inventory final
{
  using entity = entity_type<tags::inventory_tag>;

  std::vector<item::entity> items;  ///< List of items in the inventory.
  int capacity{};                   ///< Maximum capacity of inventory.
};

struct active_inventory final
{};

void serialize(auto& archive, inventory& i, uint32 version)
{
  archive(i.items, i.capacity);
}

void serialize(auto&, active_inventory&, uint32 version)
{}

}  // namespace wanderer::comp
