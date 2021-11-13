#pragma once

#include <vector>  // vector

#include <entt/entt.hpp>  // entity

#include "wanderer_std.hpp"

namespace wanderer {

struct Inventory final
{
  std::vector<entt::entity> items;  ///< List of items in the inventory.
  uint64 capacity{};                ///< Maximum capacity of inventory.
};

struct ActiveInventory final
{};

}  // namespace wanderer
