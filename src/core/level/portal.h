#pragma once
#include "tile_map.h"
#include <memory>

namespace albinjohansson::wanderer {

class Portal final {
 private:
  ITileMap_wptr from;
  ITileMap_wptr target;

 public:
  Portal(ITileMap_wptr from, ITileMap_wptr target);

  ~Portal();

  [[nodiscard]] ITileMap_wptr GetFrom() const noexcept { return from; }

  [[nodiscard]] ITileMap_wptr GetTarget() const noexcept { return target; }
};

}
