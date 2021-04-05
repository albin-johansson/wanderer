#include "create_controls_menu.hpp"

#include "button.hpp"
#include "button_system.hpp"
#include "grid_system.hpp"
#include "key_bind_system.hpp"
#include "label.hpp"
#include "label_system.hpp"
#include "menu_system.hpp"

using namespace entt::literals;

namespace wanderer::sys {
namespace {

void add_buttons(entt::registry& registry, const comp::menu::entity entity)
{
  auto& pack = registry.emplace<comp::button_pack>(entity);
  auto& buttons = pack.buttons;

  // clang-format off
  buttons.push_back(make_button(registry, "Return", menu_action::goto_home, 4));
  // clang-format on
}

void add_labels(entt::registry& registry, const comp::menu::entity entity)
{
  auto& pack = registry.emplace<comp::label_pack>(entity);
  auto& labels = pack.labels;

  constexpr auto x = column_to_x(13);
  labels.push_back(sys::make_label(registry, "Move Up", x, row_to_y(6)));
  labels.push_back(sys::make_label(registry, "Move Down", x, row_to_y(7)));
  labels.push_back(sys::make_label(registry, "Move Left", x, row_to_y(8)));
  labels.push_back(sys::make_label(registry, "Move Right", x, row_to_y(9)));
  labels.push_back(sys::make_label(registry, "Attack", x, row_to_y(10)));
  labels.push_back(sys::make_label(registry, "Interact", x, row_to_y(11)));
}

}  // namespace

auto create_controls_menu(entt::registry& registry) -> comp::menu::entity
{
  const auto entity = make_menu(registry, "Controls", menu_id::controls);
  registry.set<comp::controls_menu>(entity);

  add_buttons(registry, entity);
  add_labels(registry, entity);
  add_binds(registry,
            entity,
            comp::key_bind{cen::scancodes::escape, menu_action::goto_home});

  return entity;
}

}  // namespace wanderer::sys
