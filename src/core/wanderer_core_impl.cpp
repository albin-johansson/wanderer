#include "wanderer_core_impl.h"

#include <log.h>
#include <renderer.h>
#include <sound_effect.h>
#include <window.h>

#include <memory>

#include "action/action_parser.h"
#include "input.h"
#include "menu.h"
#include "menu_impl.h"
#include "menu_state_machine_impl.h"
#include "player_impl.h"
#include "tile_map.h"
#include "tiled_map_parser.h"

using namespace centurion;

namespace albinjohansson::wanderer {

WandererCoreImpl::WandererCoreImpl() noexcept
{}

WandererCoreImpl::~WandererCoreImpl() = default;

// void WandererCoreImpl::init_viewport()
//{
//  // TODO listener for viewport dimensions
//  m_viewport.set_level_width(static_cast<float>(m_activeMap->get_width()));
//  m_viewport.set_level_height(static_cast<float>(m_activeMap->get_height()));
//  m_viewport.set_width(GameConstants::logical_width);
//  m_viewport.set_height(GameConstants::logical_height);
//
//  m_viewport.center(m_player->get_x(),
//                    m_player->get_y(),
//                    Area{m_player->get_width(), m_player->get_height()});
//}

// void WandererCoreImpl::init_menus()
//{
//  auto sharedThis = shared_from_this();
//}

void WandererCoreImpl::handle_input(const Input& input)
{
  m_menuStateMachine->handle_input(input);
  if (!m_menuStateMachine->get_menu().is_blocking()) {
    m_player->handle_input(input, *this);
  }
}

void WandererCoreImpl::update(float delta)
{
  if (!m_menuStateMachine->get_menu().is_blocking()) {
    m_activeMap->tick(*this, m_viewport, delta);

    const auto [ix, iy] = m_player->get_interpolated_position();
    m_viewport.track(
        ix, iy, Area{m_player->get_width(), m_player->get_height()}, delta);
  }
}

void WandererCoreImpl::render(Renderer& renderer, float alpha)
{
  renderer.set_translation_viewport(m_viewport.get_internal());
  m_activeMap->draw(renderer, m_viewport, alpha);
  m_hud.draw(renderer, *this);
  m_menuStateMachine->draw(renderer, m_viewport);
}

void WandererCoreImpl::set_viewport_width(float width)
{
  m_viewport.set_width(width);
}

void WandererCoreImpl::set_viewport_height(float height)
{
  m_viewport.set_height(height);
}

void WandererCoreImpl::quit() noexcept
{
  m_shouldQuit = true;
}

void WandererCoreImpl::play_sound(const std::string& id) const
{
  m_soundEngine->get_sound(id).play();
}

void WandererCoreImpl::set_map(SharedPtr<ITileMap> map)
{
  if (map) {
    m_activeMap = map;

    const auto [px, py] = map->get_player_spawn_position();
    m_player->set_x(px);
    m_player->set_y(py);

    m_viewport.set_level_width(static_cast<float>(map->get_width()));
    m_viewport.set_level_height(static_cast<float>(map->get_height()));
  }
}

bool WandererCoreImpl::should_quit() const noexcept
{
  return m_shouldQuit;
}

const IPlayer& WandererCoreImpl::get_player() const
{
  return *m_player;
}

const ITileMap& WandererCoreImpl::get_active_map() const
{
  return *m_activeMap;
}

}  // namespace albinjohansson::wanderer