#include "translation_viewport_system.h"

#include "viewport.h"

namespace wanderer::system {

void update_translation_viewport(entt::registry& registry,
                                 const Viewport::entity viewportEntity,
                                 ctn::Renderer& renderer)
{
  if (const auto* view = registry.try_get<Viewport>(viewportEntity.get());
      view) {
    renderer.set_translation_viewport(view->bounds);
  }
}

}  // namespace wanderer::system
