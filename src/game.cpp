#include "game.hpp"

#include "animation_system.hpp"
#include "depth_drawables_system.hpp"
#include "event_connections.hpp"
#include "humanoid_animation_system.hpp"
#include "humanoid_state_system.hpp"
#include "input_system.hpp"
#include "layer_rendering_system.hpp"
#include "level_factory.hpp"
#include "make_dispatcher.hpp"
#include "movement_system.hpp"
#include "tile_animation_system.hpp"
#include "viewport_system.hpp"

namespace wanderer {

game::game(cen::renderer& renderer)
    : m_dispatcher{make_dispatcher()}
    , m_level{level_factory::make("resource/map/world.json",
                                  renderer,
                                  m_imageCache)}
{}

game::~game() noexcept
{
  disconnect_events(m_dispatcher);
}

void game::handle_input(const cen::mouse_state& mouseState,
                        const cen::key_state& keyState)
{
  m_menus.update(mouseState, keyState);
  if (!m_menus.is_blocking()) {
    sys::input::update(m_level.registry(),
                       m_dispatcher,
                       m_level.player(),
                       keyState);
  }
}

void game::tick(const delta dt)
{
  if (!m_menus.is_blocking()) {
    m_dispatcher.update();

    auto& registry = m_level.registry();
    sys::humanoid::update_state(registry, m_dispatcher);

    sys::humanoid::update_animation(registry);
    sys::tile::update_animation(registry);

    sys::movement::update(m_level, dt);
    sys::depthdrawable::update_movable(registry);

    sys::animated::update(registry);
    sys::viewport::update(m_level, m_level.player().get(), dt);
  }
}

void game::render(cen::renderer& renderer)
{
  auto& registry = m_level.registry();

  sys::viewport::translate(registry, m_level.viewport(), renderer);
  sys::layer::render_ground(registry,
                            m_level.tilemap(),
                            renderer,
                            m_level.get_render_bounds());
  sys::depthdrawable::sort(registry);
  sys::depthdrawable::render(registry, renderer);

  if (m_menus.is_blocking()) {
    m_menus.render(renderer);
  }
}

}  // namespace wanderer
