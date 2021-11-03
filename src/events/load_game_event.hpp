#pragma once

#include <string>  // string

namespace wanderer {

/// \brief Emitted when a save file should be loaded.
/// \ingroup events
struct LoadSaveEvent final
{
  std::string name;  ///< The name of the save file entry.
};

}  // namespace wanderer
