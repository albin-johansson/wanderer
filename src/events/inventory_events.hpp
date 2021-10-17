#pragma once

#include <entt.hpp>  // entity, null

namespace wanderer {

/// \brief Emitted when the inventory should be shown.
/// \ingroup events
struct ShowInventoryEvent final
{
  entt::entity inventory_entity{entt::null};
};

/// \brief Emitted when the inventory is closed.
/// \ingroup events
struct CloseInventoryEvent final
{};

}  // namespace wanderer
