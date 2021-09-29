#pragma once

#include <entt.hpp>  // entity
#include <vector>    // vector

#include "common/ints.hpp"

namespace wanderer::comp {

struct inventory final
{
  std::vector<entt::entity> items;  ///< List of items in the inventory.
  uint64 capacity{};                ///< Maximum capacity of inventory.
};

struct active_inventory final
{};

}  // namespace wanderer::comp
