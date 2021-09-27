#pragma once

#include "core/aliases/entity_type.hpp"
#include "core/ecs/null_entity.hpp"
#include "inventory.hpp"

namespace wanderer::comp {

namespace tags {
struct container_trigger_tag;
}  // namespace tags

struct [[deprecated]] container_ref final
{
  using entity = entity_type<tags::container_trigger_tag>;

  inventory::entity inventory_entity{null<inventory>()};
  [[deprecated]] int inventory_id{};
};

void serialize(auto& archive, container_ref& ref)
{
  archive(ref.inventory_entity, ref.inventory_id);
}

}  // namespace wanderer::comp
