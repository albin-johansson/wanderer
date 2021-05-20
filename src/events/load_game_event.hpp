#pragma once

#include <string>  // string

namespace wanderer {

/// \brief Emitted when a save file should be loaded.
/// \ingroup events
struct load_game_event final
{
  std::string name;  ///< The name of the save file entry.
};

}  // namespace wanderer
