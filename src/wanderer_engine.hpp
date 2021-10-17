#pragma once

#include <rune/everything.hpp>  // engine

#include "core/game.hpp"
#include "core/graphics/graphics_context.hpp"
#include "events/load_game_event.hpp"
#include "events/menu_events.hpp"

namespace wanderer {

using engine_base = rune::engine<Game, GraphicsContext>;

class wanderer_engine final : public engine_base
{
 public:
  wanderer_engine();

 private:
  void on_fullscreen_toggled(const fullscreen_toggled_event& event);

  void on_integer_scaling_toggled(const integer_scaling_toggled_event& event);

  void on_load_game_event(const LoadGameEvent& event);
};

}  // namespace wanderer
