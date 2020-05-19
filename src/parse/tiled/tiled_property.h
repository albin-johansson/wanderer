#pragma once
#include <string>

namespace tiled {

/**
 * The TiledProperty struct represents a simple property for a tile.
 *
 * @since 0.1.0
 */
struct TiledProperty final {
  std::string name = "";
  std::string type = "";
  std::string value = "";
};

}  // namespace tiled
