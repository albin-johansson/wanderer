#include "entity_sheet.h"

namespace albinjohansson::wanderer {

int EntitySheet::GetSourceY(int y, Direction direction) noexcept {
  switch (direction) {
    default:
    case Direction::UP: {
      return y;
    }
    case Direction::RIGHT: {
      return y + 192;
    }
    case Direction::DOWN: {
      return y + 128;
    }
    case Direction::LEFT: {
      return y + 64;
    }
  }
}

}
