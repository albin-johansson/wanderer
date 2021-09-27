#include "load_ground_layers.hpp"

namespace wanderer::sys {

void add_ground_layers(entt::registry& registry, const ir::level& data)
{
  for (const auto& groundLayer : data.ground_layers) {
    auto& layer = registry.emplace<comp::tile_layer>(registry.create(), groundLayer);
    layer.matrix.shrink_to_fit();
  }

  registry.sort<comp::tile_layer>(
      [](const comp::tile_layer& lhs, const comp::tile_layer& rhs) noexcept {
        return lhs.z < rhs.z;
      });
}

}  // namespace wanderer::sys
