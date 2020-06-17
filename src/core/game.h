#pragma once
#include <renderer.h>

#include "input.h"
#include "types.h"
#include "viewport.h"

namespace wanderer {

class Game final {
 public:
  explicit Game(centurion::Renderer& renderer);

  void handle_input(const Input& input);

  void tick(float delta);

  void render(centurion::Renderer& renderer, float alpha);

 private:
  entt::registry m_registry;
//  entt::dispatcher m_dispatcher;
  entt::entity m_player;
  entt::entity m_world;
  entt::entity m_viewport;
};

}  // namespace wanderer
