#pragma once

#include "inventory.hpp"
#include "null_entity.hpp"

namespace wanderer::comp {

struct show_inventory_event final
{
  inventory::entity inventoryEntity{null<inventory>()};
};

}  // namespace wanderer::comp
