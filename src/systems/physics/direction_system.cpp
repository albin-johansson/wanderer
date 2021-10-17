#include "direction_system.hpp"

#include "common/maybe.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto HorizontalDominantDirection(const comp::Movable& movable) noexcept
    -> maybe<Direction>
{
  if (movable.velocity.x < 0) {
    return Direction::Left;
  }
  else if (movable.velocity.x > 0) {
    return Direction::Right;
  }
  else {
    return std::nullopt;
  }
}

[[nodiscard]] auto VerticalDominantDirection(const comp::Movable& movable) noexcept
    -> maybe<Direction>
{
  if (movable.velocity.y < 0) {
    return Direction::Up;
  }
  else if (movable.velocity.y > 0) {
    return Direction::Down;
  }
  else {
    return std::nullopt;
  }
}

}  // namespace

auto GetDominantDirection(const comp::Movable& movable) noexcept -> Direction
{
  if (const auto horizontal = HorizontalDominantDirection(movable)) {
    return *horizontal;
  }
  else if (const auto vertical = VerticalDominantDirection(movable)) {
    return *vertical;
  }
  else {
    return movable.dir;
  }
}

}  // namespace wanderer::sys
