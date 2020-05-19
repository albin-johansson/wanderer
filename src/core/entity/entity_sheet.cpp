#include "entity_sheet.h"

namespace albinjohansson::wanderer {

int EntitySheet::get_source_y(int y, Direction direction) noexcept
{
  switch (direction) {
    default:
    case Direction::Up: {
      return y;
    }
    case Direction::Right: {
      return y + 192;
    }
    case Direction::Down: {
      return y + 128;
    }
    case Direction::Left: {
      return y + 64;
    }
  }
}

}  // namespace albinjohansson::wanderer
