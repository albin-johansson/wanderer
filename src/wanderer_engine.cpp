#include "wanderer_engine.hpp"

#include "core/game_constants.hpp"

namespace wanderer {

WandererEngine::WandererEngine() : engine_base{}
{
  // clang-format off
  auto& game = get_game();
  game.sink<fullscreen_toggled_event>().connect<&WandererEngine::OnFullscreenToggled>(this);
  game.sink<integer_scaling_toggled_event>().connect<&WandererEngine::OnIntegerScalingToggled>(this);
  game.sink<LoadGameEvent>().connect<&WandererEngine::OnLoadGameEvent>(this);
  // clang-format on
}

void WandererEngine::OnFullscreenToggled(const fullscreen_toggled_event& event)
{
  auto& window = get_window();

  // TODO make it possible to specify whether to use real fullscreen or fullscreen desktop
  if (event.enabled) {
    window.set_size(cen::screen::size().value());
    window.set_fullscreen_desktop(true);
  }
  else {
    window.set_fullscreen_desktop(false);
    window.set_width(cen::screen::width().value() / 2);
    window.set_height(cen::screen::height().value() / 2);
  }
}

void WandererEngine::OnIntegerScalingToggled(const integer_scaling_toggled_event& event)
{
  get_graphics().get_renderer().set_logical_integer_scaling(event.enabled);
}

void WandererEngine::OnLoadGameEvent(const LoadGameEvent& event)
{
  get_game().load_save(event.name, get_graphics());
}

}  // namespace wanderer