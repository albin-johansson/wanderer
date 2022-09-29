#pragma once

#include <centurion/opengl.hpp>
#include <centurion/window.hpp>

#include "wanderer/core/events.hpp"
#include "wanderer/core/game_ctx.hpp"
#include "wanderer/core/game_loop.hpp"
#include "wanderer/core/state/game_state.hpp"
#include "wanderer/core/state/game_state_id.hpp"
#include "wanderer/core/vocabulary.hpp"
#include "wanderer/gfx/renderer.hpp"
#include "wanderer/gfx/texture.hpp"
#include "wanderer/type/maybe.hpp"
#include "wanderer/type/vector_map.hpp"

namespace wanderer {

class Game final : GameLoop {
 public:
  Game();

  void run();

  void process_events() override;
  void update(float32 dt) override;
  void render() override;

 private:
  cen::window mWindow;
  cen::gl_context mGL;
  GameCtx mContext;
  Maybe<Renderer> mRenderer;

  void register_events();

  void on_quit();

  void on_change_state(const ChangeStateEvent& event);
};

}  // namespace wanderer
