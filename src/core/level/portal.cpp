#include "portal.h"
#include "tile_map.h"
#include <utility>

namespace albinjohansson::wanderer {

Portal::Portal(std::weak_ptr<ITileMap> from, std::weak_ptr<ITileMap> target) {
  this->from = std::move(from);
  this->target = std::move(target);
}

Portal::~Portal() = default;

}
