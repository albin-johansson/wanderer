#pragma once
#include "renderer.h"
#include "viewport.h"
#include "entity.h"

namespace wanderer::core {

class EntityDrawDelegate final {
 public:
  EntityDrawDelegate();

  ~EntityDrawDelegate();

  void Draw(visuals::Renderer& renderer,
            const Viewport& viewport,
            const IEntity& entity,
            float srcX,
            float srcY) const noexcept;

};

}
