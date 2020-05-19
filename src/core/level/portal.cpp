#include "portal.h"

#include <utility>

#include "tile_map.h"

namespace wanderer {

Portal::Portal(std::weak_ptr<ITileMap> from, std::weak_ptr<ITileMap> target)
{
  this->m_from = std::move(from);
  this->m_target = std::move(target);
}

Portal::~Portal() = default;

}  // namespace wanderer
