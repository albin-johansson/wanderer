#pragma once

#include <rect.h>
#include <texture.h>

#include <memory>

#include "types.h"

namespace wanderer {

struct Tile final {
  TileID id;
  centurion::IRect src;
  std::shared_ptr<centurion::Texture> sheet;
};

}  // namespace wanderer
