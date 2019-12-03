#include "portal.h"
#include <utility>

namespace albinjohansson::wanderer {

Portal::Portal(std::weak_ptr<TileMapImpl> from, std::weak_ptr<TileMapImpl> target) {
  this->from = std::move(from);
  this->target = std::move(target);
}

Portal::~Portal() = default;

}
