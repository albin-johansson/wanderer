#pragma once

#include "core/aliases/entity_type.hpp"
#include "core/ecs/null_entity.hpp"

namespace wanderer::comp {

namespace tags {
struct bed_trigger_tag;
}  // namespace tags

struct bed_trigger final
{
  using entity = entity_type<tags::bed_trigger_tag>;

  [[maybe_unused]] char unused{};
};

struct is_within_bed_trigger final
{
  bed_trigger::entity trigger_entity{null<bed_trigger>()};
};

void serialize(auto& archive, is_within_bed_trigger& indicator)
{
  archive(indicator.trigger_entity);
}

}  // namespace wanderer::comp
