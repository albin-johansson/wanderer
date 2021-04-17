#pragma once

#include "components/ctx/binds.hpp"

namespace wanderer::sys {

/// \name Configuration
/// \{

/**
 * \brief Attempts to read the binds from the preferred file directory.
 *
 * \ingroup systems
 *
 * \details This function will look for a binds file called `binds.ini` in the preferred
 * file directory. The default binds will be used if no such file was found.
 *
 * \return the parsed binds.
 */
[[nodiscard]] auto load_binds() -> ctx::binds;

/// \} End of configuration

}  // namespace wanderer::sys
