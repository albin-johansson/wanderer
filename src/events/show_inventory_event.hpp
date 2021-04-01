#pragma once

#include "inventory.hpp"
#include "null_entity.hpp"

namespace wanderer::event {

struct show_inventory_event final
{
  comp::inventory::entity inventoryEntity{null<comp::inventory>()};
};

}  // namespace wanderer::event
