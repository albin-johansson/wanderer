#pragma once

#include "core/aliases/entity_type.hpp"
#include "core/aliases/ints.hpp"
#include "core/ecs/null_entity.hpp"
#include "inventory.hpp"

namespace wanderer::comp {
namespace detail {
struct container_trigger_entity_t;
}

struct container_trigger final
{
  using entity = entity_type<detail::container_trigger_entity_t>;
  inventory::entity inventoryEntity{null<inventory>()};
  int inventoryId{};
};

struct is_within_container_trigger final
{
  container_trigger::entity triggerEntity{null<container_trigger>()};
};

void serialize(auto& archive, container_trigger& ct, u32 version)
{
  archive(ct.inventoryEntity, ct.inventoryId);
}

void serialize(auto& archive, is_within_container_trigger& iwct, u32 version)
{
  archive(iwct.triggerEntity);
}

}  // namespace wanderer::comp
