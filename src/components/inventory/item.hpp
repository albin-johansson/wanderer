#pragma once

#include "core/aliases/entity_type.hpp"

namespace wanderer::comp {

namespace tags {
struct item_tag;
}  // namespace tags

struct item final
{
  using entity = entity_type<tags::item_tag>;
  // TODO include texture_id
};

// TODO make serializable

}  // namespace wanderer::comp
