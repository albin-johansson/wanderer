#pragma once

#include <rune/everything.hpp>  // engine

#include "core/game.hpp"
#include "core/graphics/graphics_context.hpp"
#include "events/load_game_event.hpp"
#include "events/menu_events.hpp"

namespace wanderer {

using engine_base = rune::engine<Game, GraphicsContext>;

class WandererEngine final : public engine_base
{
 public:
  WandererEngine();

 private:
  void OnFullscreenToggled(const fullscreen_toggled_event& event);

  void OnIntegerScalingToggled(const integer_scaling_toggled_event& event);

  void OnLoadGameEvent(const LoadGameEvent& event);
};

}  // namespace wanderer
