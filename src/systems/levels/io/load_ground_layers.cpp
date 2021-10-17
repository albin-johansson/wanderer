#include "load_ground_layers.hpp"

namespace wanderer::sys {

void AddGroundLayers(entt::registry& registry, const ir::level& data)
{
  for (const auto& groundLayer : data.ground_layers) {
    auto& layer = registry.emplace<comp::TileLayer>(registry.create(), groundLayer);
    layer.matrix.shrink_to_fit();
  }

  registry.sort<comp::TileLayer>(
      [](const comp::TileLayer& lhs, const comp::TileLayer& rhs) noexcept {
        return lhs.z < rhs.z;
      });
}

}  // namespace wanderer::sys
