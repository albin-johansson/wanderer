#pragma once

#include "entity_type.hpp"
#include "inventory.hpp"
#include "null_entity.hpp"

namespace wanderer::comp {
namespace detail {
struct container_trigger_entity_t;
}

struct container_trigger final
{
  using entity = entity_type<detail::container_trigger_entity_t>;
  inventory::entity inventoryEntity{null<inventory>()};
  int inventoryId;
};

struct is_within_container_trigger final
{
  container_trigger::entity triggerEntity{null<container_trigger>()};
};

}  // namespace wanderer::comp
