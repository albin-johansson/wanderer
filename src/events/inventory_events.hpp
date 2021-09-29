#pragma once

#include <entt.hpp>  // entity, null

namespace wanderer {

/// \brief Emitted when the inventory should be shown.
/// \ingroup events
struct show_inventory_event final
{
  entt::entity inventory_entity{entt::null};
};

/// \brief Emitted when the inventory is closed.
/// \ingroup events
struct close_inventory_event final
{};

}  // namespace wanderer
