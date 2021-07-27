#pragma once

#include "core/aliases/entity_type.hpp"
#include "core/aliases/ints.hpp"
#include "core/ecs/null_entity.hpp"
#include "inventory.hpp"

namespace wanderer::comp {

namespace tags {
struct container_trigger_tag;
}  // namespace tags

struct container_trigger final
{
  using entity = entity_type<tags::container_trigger_tag>;

  inventory::entity inventory_entity{null<inventory>()};
  int inventory_id{};
};

struct is_within_container_trigger final
{
  container_trigger::entity trigger_entity{null<container_trigger>()};
};

void serialize(auto& archive, container_trigger& ct, uint32 version)
{
  archive(ct.inventory_entity, ct.inventory_id);
}

void serialize(auto& archive, is_within_container_trigger& iwct, uint32 version)
{
  archive(iwct.trigger_entity);
}

}  // namespace wanderer::comp
