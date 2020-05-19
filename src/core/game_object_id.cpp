#include "game_object_id.h"

namespace wanderer {

uint64 GameObjectID::count = 0;

uint64 GameObjectID::next() noexcept
{
  return count++;
}

uint64 GameObjectID::peek() noexcept
{
  return count;
}

}  // namespace wanderer
