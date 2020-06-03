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

  void tick(float delta);

  void render(centurion::Renderer& renderer, float alpha);

 private:
  entt::registry m_registry;
  entt::entity m_player;
};

}  // namespace wanderer
