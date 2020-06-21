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
  explicit Game(centurion::Renderer& renderer);

  ~Game() noexcept;

  void handle_input(const Input& input);

  void tick(Delta delta);

  void render(centurion::Renderer& renderer, Alpha alpha);

 private:
  entt::registry m_registry;  // TODO consider multiple registries
  entt::dispatcher m_dispatcher;

  ImageCache m_imageCache;

  entt::entity m_player;
  TilemapEntity m_world{entt::entity{entt::null}};
  entt::entity m_viewport;
};

}  // namespace wanderer
