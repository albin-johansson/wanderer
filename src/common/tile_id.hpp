#pragma once

#include <nenya.hpp>  // strong_type

#include "ints.hpp"

namespace wanderer {

namespace tags {
struct tile_id_tag;
}  // namespace tags

using tile_id = nenya::strong_type<uint32, tags::tile_id_tag>;

}  // namespace wanderer
