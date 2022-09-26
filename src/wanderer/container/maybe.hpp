#pragma once

#include <EASTL/optional.h>

#include "wanderer/container/eastl_new.hpp"

namespace wanderer {

template <typename T>
using Maybe = eastl::optional<T>;

inline constexpr auto nothing = eastl::nullopt;

}  // namespace wanderer
