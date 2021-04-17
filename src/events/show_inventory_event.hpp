#pragma once

#include "components/inventory/inventory.hpp"
#include "core/null_entity.hpp"

namespace wanderer {

struct show_inventory_event final
{
  comp::inventory::entity inventoryEntity{null<comp::inventory>()};
};

}  // namespace wanderer
