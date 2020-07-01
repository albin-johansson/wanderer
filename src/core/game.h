#pragma once

#include <renderer.h>

#include "image_cache.h"
#include "input.h"
#include "tilemap.h"
#include "viewport.h"
#include "wanderer_stdinc.h"

namespace wanderer {

class Game final {
 public:
  explicit Game(ctn::Renderer& renderer);

  ~Game() noexcept;

  void handle_input(const Input& input);

  void tick(Delta delta);

  void render(ctn::Renderer& renderer, Alpha alpha);

 private:
  entt::registry m_registry;  // TODO consider multiple registries
  entt::dispatcher m_dispatcher;

  ImageCache m_imageCache;

  entt::entity m_player;
  comp::Tilemap::entity m_world = null_entity<comp::Tilemap>();
  comp::Viewport::entity m_viewport = null_entity<comp::Viewport>();
};

}  // namespace wanderer
