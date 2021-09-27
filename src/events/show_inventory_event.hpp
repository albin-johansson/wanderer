#pragma once

#include "components/items/inventory.hpp"
#include "core/ecs/null_entity.hpp"

namespace wanderer {

/// \brief Emitted when the inventory should be shown.
/// \ingroup events
struct show_inventory_event final
{
  comp::inventory::entity inventory_entity{null<comp::inventory>()};
};

}  // namespace wanderer
