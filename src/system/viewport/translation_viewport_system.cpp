#include "translation_viewport_system.h"

#include "viewport.h"

namespace wanderer::system::viewport {

void translate(entt::registry& registry,
               const Viewport::entity viewportEntity,
               ctn::Renderer& renderer)
{
  auto const& viewport = registry.get<Viewport>(viewportEntity.get());
  renderer.set_translation_viewport(viewport.bounds);
}

}  // namespace wanderer::system::viewport
