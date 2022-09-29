#pragma once

#include <EASTL/hash_map.h>

#include "wanderer/type/eastl_new.hpp"

namespace wanderer {

template <typename K, typename V>
using HashMap = eastl::hash_map<K, V>;

}  // namespace wanderer