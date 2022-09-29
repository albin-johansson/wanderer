#pragma once

#include <EASTL/vector.h>

#include "wanderer/type/eastl_new.hpp"

namespace wanderer {

template <typename T>
using Vector = eastl::vector<T>;

}  // namespace wanderer
