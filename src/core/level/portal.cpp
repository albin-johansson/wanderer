#include "portal.h"
#include <utility>

namespace albinjohansson::wanderer {

Portal::Portal(ITileMap_wptr from, ITileMap_wptr target) {
  this->from = std::move(from);
  this->target = std::move(target);
}

Portal::~Portal() = default;

}
