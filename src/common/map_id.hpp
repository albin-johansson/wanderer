#pragma once

#include <nenya.hpp>  // strong_type

#include "ints.hpp"

namespace wanderer {

namespace tags {
struct map_id_tag;
}  // namespace tags

using map_id = nenya::strong_type<int32, tags::map_id_tag>;

}  // namespace wanderer
