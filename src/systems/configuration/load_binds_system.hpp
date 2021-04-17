#pragma once

#include "components/ctx/binds.hpp"

namespace wanderer::sys {

/// \name Configuration
/// \{

[[nodiscard]] auto load_binds() -> ctx::binds;

/// \} End of configuration

}
