#include "menu_state_machine_impl.h"

#include <menu_parser.h>
#include <renderer.h>

#include "input.h"
#include "menu.h"
#include "viewport.h"
#include "wanderer_core.h"

using namespace centurion;

namespace albinjohansson::wanderer {

MenuStateMachineImpl::MenuStateMachineImpl()
    : m_typewriterFonts("resources/font/type_writer.ttf")
{}

MenuStateMachineImpl::~MenuStateMachineImpl() = default;

void MenuStateMachineImpl::draw(Renderer& renderer,
                                const Viewport& viewport) const
{
  m_menus.at(m_activeMenuID)->draw(renderer, viewport, m_typewriterFonts);
}

void MenuStateMachineImpl::add_menu(MenuID id, Unique<IMenu> menu)
{
  m_menus.emplace(id, std::move(menu));
}

void MenuStateMachineImpl::set_menu(MenuID id) noexcept
{
  m_activeMenuID = id;
}

void MenuStateMachineImpl::handle_input(const Input& input) noexcept
{
  m_menus.at(m_activeMenuID)->handle_input(input);
}

const IMenu& MenuStateMachineImpl::get_menu() const
{
  return *m_menus.at(m_activeMenuID);
}

// FIXME problem with time based entities and blocking menus, where the NPC
// cooldowns are affected

}  // namespace albinjohansson::wanderer
