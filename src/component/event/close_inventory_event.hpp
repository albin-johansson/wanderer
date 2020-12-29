#pragma once

#include "inventory.hpp"

namespace wanderer::comp {

struct close_inventory_event final
{
  comp::inventory::entity inventoryEntity{null<comp::inventory>()};
};

}  // namespace wanderer::comp
