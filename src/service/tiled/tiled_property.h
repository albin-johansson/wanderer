#pragma once
#include <string>

namespace albinjohansson::tiled {

/**
 * The TiledProperty struct represents a simple property for a tile.
 *
 * @since 0.1.0
 */
struct TiledProperty final {
  std::string name = "";
  std::string value = "";
  std::string type = "";
};

}
