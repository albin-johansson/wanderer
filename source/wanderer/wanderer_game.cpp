#include "wanderer_game.hpp"

#include <centurion.hpp>

#include "data/cfg.hpp"
#include "events/misc_events.hpp"
#include "misc/exception.hpp"
#include "misc/logging.hpp"
#include "systems/registry_system.hpp"

namespace wanderer {

wanderer_game::wanderer_game()
    : mCfg{make_game_cfg()}
    , mGraphics{mCfg}
    , mRegistry{sys::make_main_registry()}
{
  mDispatcher.sink<action_event>().connect<&wanderer_game::on_action>(this);

  // TODO load levels

  const auto output = mGraphics.renderer().output_size();
  log_debug("Output size... ({}, {})", output.width, output.height);
}

void wanderer_game::run()
{
  auto& window = mGraphics.window();
  window.center();
  //  window.set_fullscreen_desktop(true);
  window.show();

  start();

  window.hide();
}

void wanderer_game::process_events()
{
  cen::event_handler event;

  while (event.poll()) {
    if (event.is(cen::event_type::quit)) {
      stop();
      break;
    }
    else if (event.is(cen::event_type::key_up)) {
      const auto& ke = event.get<cen::keyboard_event>();
      if (ke.is_active(cen::scancodes::q)) {
        stop();
        break;
      }
    }
  }

  mInput.refresh(mGraphics.renderer());
  mMenus.poll(mInput, mDispatcher);
}

void wanderer_game::update(const float32 dt)
{
  mDispatcher.update();
  if (!mMenus.is_blocking()) {
    //
  }
}

void wanderer_game::render()
{
  auto& renderer = mGraphics.renderer();
  renderer.clear_with(cen::colors::hot_pink);

  mMenus.render(mGraphics);

  const auto mx = mInput.mouse_logical_x();
  const auto my = mInput.mouse_logical_y();
  renderer.set_color(cen::colors::lime);
  renderer.fill_circle<float>({mx, my}, 3);

  renderer.present();
}

void wanderer_game::on_action(const action_event& event)
{
  switch (event.action) {
    case action_id::noop:
      break;

    case action_id::quit:
      stop();
      break;

    case action_id::goto_game:
      mMenus.switch_to(menu_id::game);
      break;

    case action_id::goto_main_menu:
      mMenus.switch_to(menu_id::home);
      break;

    case action_id::goto_options_menu:
      mMenus.switch_to(menu_id::options);
      break;

    case action_id::goto_credits_menu:
      mMenus.switch_to(menu_id::credits);
      break;

    case action_id::toggle_fullscreen: {
      auto& window = mGraphics.window();
      window.set_fullscreen_desktop(!window.is_fullscreen_desktop());
      break;
    }
    default:
      throw_traced(wanderer_error{"Invalid action!"});
  }
}

}  // namespace wanderer