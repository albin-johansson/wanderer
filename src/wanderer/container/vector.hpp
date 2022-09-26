#pragma once

#include <EASTL/vector.h>

#include "wanderer/container/eastl_new.hpp"

namespace wanderer {

template <typename T>
using Vec = eastl::vector<T>;

}  // namespace wanderer
