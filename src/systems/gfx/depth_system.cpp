#include "depth_system.hpp"

#include <tuple>  // tie

#include "components/gfx/depth_drawable.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto sort(const comp::depth_drawable& lhs,
                        const comp::depth_drawable& rhs) noexcept -> bool
{
  const auto lhsCenterY = lhs.dst.center_y();
  const auto rhsCenterY = rhs.dst.center_y();

  return std::tie(lhs.layer, lhs.depth, lhsCenterY) <
         std::tie(rhs.layer, rhs.depth, rhsCenterY);
}

}  // namespace

void sort_depth_drawables(entt::registry& registry, const sort_strategy strategy)
{
  if (strategy == sort_strategy::insertion_sort) {
    registry.sort<comp::depth_drawable>(sort, entt::insertion_sort{});
  }
  else /*if (strategy == sort_strategy::std_sort)*/ {
    registry.sort<comp::depth_drawable>(sort);
  }
}

}  // namespace wanderer::sys
