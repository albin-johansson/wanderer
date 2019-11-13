#include "entity_sheet.h"

namespace wanderer::core {

float EntitySheet::GetSourceY(int y, Direction direction) noexcept {
  switch (direction) {
    default:
    case Direction::UP: { return static_cast<float>(y); }
    case Direction::RIGHT: { return static_cast<float>(y + 192); }
    case Direction::DOWN: { return static_cast<float>(y + 128); }
    case Direction::LEFT: { return static_cast<float>(y + 64); }
  }
}

}
