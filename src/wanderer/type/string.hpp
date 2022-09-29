#pragma once

#include <string_view>  // string_view

#include <EASTL/string.h>
#include <EASTL/string_view.h>

#include "wanderer/type/eastl_new.hpp"

namespace wanderer {

using String = eastl::string;
using StringView = eastl::string_view;

[[nodiscard]] auto from_std(std::string_view str) -> String;

}  // namespace wanderer
