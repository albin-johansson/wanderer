#include "depth_system.hpp"

#include <tuple>  // tie

#include "components/gfx/drawable.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto Sorter(const comp::Drawable& lhs, const comp::Drawable& rhs) noexcept
    -> bool
{
  const auto lhsCenterY = lhs.dst.center_y();
  const auto rhsCenterY = rhs.dst.center_y();

  return std::tie(lhs.layer, lhs.depth, lhsCenterY) <
         std::tie(rhs.layer, rhs.depth, rhsCenterY);
}

}  // namespace

void UpdateDepth(entt::registry& registry, SortStrategy strategy)
{
  if (strategy == SortStrategy::InsertionSort) {
    registry.sort<comp::Drawable>(Sorter, entt::insertion_sort{});
  }
  else /*if (strategy == sort_strategy::std_sort)*/ {
    registry.sort<comp::Drawable>(Sorter);
  }
}

}  // namespace wanderer::sys
