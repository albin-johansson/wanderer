#pragma once

#include <centurion.hpp>  // window
#include <rune.hpp>       // engine

#include "core/game.hpp"
#include "core/graphics/graphics_context.hpp"
#include "events/fullscreen_toggled_event.hpp"
#include "events/integer_scaling_toggled_event.hpp"
#include "events/load_game_event.hpp"

namespace wanderer {

using engine_base = rune::engine<game, graphics_context>;

class wanderer_engine final : public engine_base
{
 public:
  wanderer_engine();

 private:
  void on_fullscreen_toggled(const fullscreen_toggled_event& event);

  void on_integer_scaling_toggled(const integer_scaling_toggled_event& event);

  void on_load_game_event(const load_game_event& event);
};

}  // namespace wanderer
