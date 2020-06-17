#pragma once

#include <renderer.h>

#include "image_cache.h"
#include "input.h"
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
  entt::registry m_registry;
  entt::dispatcher m_dispatcher;

  ImageCache m_imageCache;

  entt::entity m_player;
  entt::entity m_world;
  entt::entity m_viewport;
};

}  // namespace wanderer
