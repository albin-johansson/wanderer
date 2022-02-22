#include "menu_builder.hpp"

#include <utility>  // move

#include "wanderer/misc/assert.hpp"

namespace wanderer::sys::ui {
namespace {

void _add_label(entt::registry& registry,
                const entt::entity entity,
                std::string text,
                const glm::vec2& offset,
                const font_size size,
                const h_anchor halign,
                const v_anchor valign)
{
  WANDERER_ASSERT_MSG(!text.empty(), "Invalid empty label text!");

  auto& label = registry.emplace<comp::ui_label>(entity);
  label.offset = offset;
  label.text = std::move(text);
  label.size = size;
  label.color = cen::colors::white;

  auto& anchor = registry.emplace<comp::ui_anchor>(entity);
  anchor.horizontal = halign;
  anchor.vertical = valign;
}

auto _add_button(entt::registry& registry,
                 comp::ui_menu& menu,
                 std::string text,
                 const action_id action,
                 const glm::vec2& offset) -> entt::entity
{
  const auto entity = menu.buttons.emplace_back(registry.create());

  auto& button = registry.emplace<comp::ui_button>(entity);
  button.action = action;

  _add_label(registry,
             entity,
             std::move(text),
             offset,
             font_size::medium,
             h_anchor::center,
             v_anchor::top);

  return entity;
}

}  // namespace

menu_builder::menu_builder(entt::registry& registry)
    : mRegistry{registry}
    , mEntity{registry.create()}
{
  registry.emplace<comp::ui_menu>(mEntity);
}

auto menu_builder::build(entt::registry& registry) -> menu_builder
{
  return menu_builder{registry};
}

auto menu_builder::blocking() -> menu_builder&
{
  get_menu().blocking = true;
  return *this;
}

auto menu_builder::title(std::string title) -> menu_builder&
{
  auto& menu = get_menu();
  menu.title = std::move(title);

  if (!menu.title.empty()) {
    h_label(menu.title, {0, 0.1f}, h_anchor::center, v_anchor::top);
  }

  return *this;
}

auto menu_builder::s_label(std::string text,
                           const glm::vec2& offset,
                           const h_anchor ha,
                           const v_anchor va) -> menu_builder&
{
  add_label(std::move(text), font_size::small, offset, ha, va);
  return *this;
}

auto menu_builder::m_label(std::string text,
                           const glm::vec2& offset,
                           const h_anchor ha,
                           const v_anchor va) -> menu_builder&
{
  add_label(std::move(text), font_size::medium, offset, ha, va);
  return *this;
}

auto menu_builder::l_label(std::string text,
                           const glm::vec2& offset,
                           const h_anchor ha,
                           const v_anchor va) -> menu_builder&
{
  add_label(std::move(text), font_size::large, offset, ha, va);
  return *this;
}

auto menu_builder::h_label(std::string text,
                           const glm::vec2& offset,
                           const h_anchor ha,
                           const v_anchor va) -> menu_builder&
{
  add_label(std::move(text), font_size::huge, offset, ha, va);
  return *this;
}

auto menu_builder::button(std::string label,
                          const action_id action,
                          const glm::vec2& offset) -> menu_builder&
{
  _add_button(mRegistry, get_menu(), std::move(label), action, offset);
  return *this;
}

auto menu_builder::toggle(std::string label,
                          const action_id action,
                          const uint64 flag,
                          const glm::vec2& offset) -> menu_builder&
{
  auto& registry = mRegistry.get();
  const auto entity = _add_button(registry,  //
                                  get_menu(),
                                  std::move(label),
                                  action,
                                  offset);

  auto& toggle = registry.emplace<comp::ui_setting_toggle>(entity);
  toggle.flag = flag;

  return *this;
}

auto menu_builder::bind(const cen::scan_code& key, const action_id action)
    -> menu_builder&
{
  auto& registry = mRegistry.get();
  auto& menu = get_menu();

  const auto bindEntity = registry.create();
  menu.binds.push_back(bindEntity);

  auto& bind = registry.emplace<comp::ui_bind>(bindEntity);
  bind.key = key;
  bind.action = action;

  return *this;
}

auto menu_builder::get_menu() -> comp::ui_menu&
{
  auto& registry = mRegistry.get();
  return registry.get<comp::ui_menu>(mEntity);
}

void menu_builder::add_label(entt::entity entity,
                             std::string text,
                             const font_size size,
                             const glm::vec2& offset,
                             const h_anchor ha,
                             const v_anchor va)

{
  auto& registry = mRegistry.get();
  auto& label = registry.emplace<comp::ui_label>(entity);
  label.offset = offset;
  label.text = std::move(text);
  label.size = size;
  label.color = cen::colors::white;

  auto& anchor = registry.emplace<comp::ui_anchor>(entity);
  anchor.horizontal = ha;
  anchor.vertical = va;
}

void menu_builder::add_label(std::string text,
                             const font_size size,
                             const glm::vec2& offset,
                             const h_anchor ha,
                             const v_anchor va)
{
  auto& registry = mRegistry.get();
  auto& menu = get_menu();

  const auto entity = registry.create();
  menu.labels.push_back(entity);

  add_label(entity, std::move(text), size, offset, ha, va);
}

}  // namespace wanderer::sys::ui