#pragma once

#include <vector>  // vector

#include <entt.hpp>  // entity

#include "common/ints.hpp"

namespace wanderer::comp {

struct Inventory final
{
  std::vector<entt::entity> items;  ///< List of items in the inventory.
  uint64 capacity{};                ///< Maximum capacity of inventory.
};

struct ActiveInventory final
{};

}  // namespace wanderer::comp
