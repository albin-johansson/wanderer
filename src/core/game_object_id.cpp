#include "game_object_id.h"

namespace albinjohansson::wanderer {

int GameObjectID::count = 0;

int GameObjectID::next() noexcept {
  return count++;
}

int GameObjectID::peek() noexcept {
  return count;
}

}
