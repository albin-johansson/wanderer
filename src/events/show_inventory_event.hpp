#pragma once

#include "components/inventory/inventory.hpp"
#include "core/null_entity.hpp"

namespace wanderer::event {

struct show_inventory final
{
  comp::inventory::entity inventoryEntity{null<comp::inventory>()};
};

}  // namespace wanderer::event
