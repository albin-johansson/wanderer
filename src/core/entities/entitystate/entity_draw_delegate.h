#pragma once
#include "renderer.h"
#include "viewport.h"
#include "entity.h"

namespace wanderer::core {

class EntityDrawDelegate final {
 public:
  EntityDrawDelegate() = delete;

  ~EntityDrawDelegate() = default;

  static void Draw(visuals::Renderer& renderer,
                   const Viewport& viewport,
                   const IEntity& entity,
                   float srcX,
                   float srcY) noexcept;

};

}
