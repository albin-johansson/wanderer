#pragma once
#include <renderer.h>

#include <entt.hpp>

#include "input.h"
#include "types.h"

namespace wanderer {

class Game {
 public:
  void init();

  void handle_input(const Input& input);

  void tick(f32 delta);

  void render(centurion::Renderer& renderer, f32 alpha);

 private:
  entt::registry m_registry;
  entt::entity m_player;
};

}  // namespace wanderer
