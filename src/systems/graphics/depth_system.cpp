#include "depth_system.hpp"

#include <tuple>  // tie

#include "depth_drawable.hpp"

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

void update_depth(entt::registry& registry)
{
  registry.sort<comp::depth_drawable>(sort, entt::insertion_sort{});
}

}  // namespace wanderer::sys
