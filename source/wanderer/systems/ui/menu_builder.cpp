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
                const HAnchor ha,
                const VAnchor va)
{
  WANDERER_ASSERT_MSG(!text.empty(), "Invalid empty label text!");

  auto& label = registry.emplace<comp::UiLabel>(entity);
  label.offset = offset;
  label.text = std::move(text);
  label.size = size;
  label.color = cen::colors::white;

  auto& anchor = registry.emplace<comp::UiAnchor>(entity);
  anchor.horizontal = ha;
  anchor.vertical = va;
}

auto _add_button(entt::registry& registry,
                 comp::UiMenu& menu,
                 std::string text,
                 const action_id action,
                 const glm::vec2& offset,
                 const HAnchor ha,
                 const VAnchor va) -> entt::entity
{
  const auto entity = menu.buttons.emplace_back(registry.create());

  auto& button = registry.emplace<comp::UiButton>(entity);
  button.action = action;

  _add_label(registry, entity, std::move(text), offset, font_size::medium, ha, va);

  return entity;
}

}  // namespace

menu_builder::menu_builder(entt::registry& registry)
    : mRegistry{registry}
    , mEntity{registry.create()}
{
  registry.emplace<comp::UiMenu>(mEntity);
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
    h_label(menu.title, {0, 0.1f}, HAnchor::center, VAnchor::top);
  }

  return *this;
}

auto menu_builder::line(const glm::vec2& start,
                        const glm::vec2& end,
                        const HAnchor ha,
                        const VAnchor va,
                        const cen::color& color) -> menu_builder&
{
  auto& registry = mRegistry.get();
  auto& menu = get_menu();

  const auto lineEntity = registry.create();
  menu.lines.push_back(lineEntity);

  auto& line = registry.emplace<comp::UiLine>(lineEntity);
  line.start = start;
  line.end = end;
  line.color = color;

  auto& anchor = registry.emplace<comp::UiAnchor>(lineEntity);
  anchor.horizontal = ha;
  anchor.vertical = va;

  return *this;
}

auto menu_builder::s_label(std::string text,
                           const glm::vec2& offset,
                           const HAnchor ha,
                           const VAnchor va) -> menu_builder&
{
  add_label(std::move(text), font_size::small, offset, ha, va);
  return *this;
}

auto menu_builder::m_label(std::string text,
                           const glm::vec2& offset,
                           const HAnchor ha,
                           const VAnchor va) -> menu_builder&
{
  add_label(std::move(text), font_size::medium, offset, ha, va);
  return *this;
}

auto menu_builder::l_label(std::string text,
                           const glm::vec2& offset,
                           const HAnchor ha,
                           const VAnchor va) -> menu_builder&
{
  add_label(std::move(text), font_size::large, offset, ha, va);
  return *this;
}

auto menu_builder::h_label(std::string text,
                           const glm::vec2& offset,
                           const HAnchor ha,
                           const VAnchor va) -> menu_builder&
{
  add_label(std::move(text), font_size::huge, offset, ha, va);
  return *this;
}

auto menu_builder::button(std::string label,
                          const action_id action,
                          const glm::vec2& offset,
                          const HAnchor ha,
                          const VAnchor va) -> menu_builder&
{
  _add_button(mRegistry, get_menu(), std::move(label), action, offset, ha, va);
  return *this;
}

auto menu_builder::toggle(std::string label,
                          const action_id action,
                          const uint64 flag,
                          const glm::vec2& offset,
                          const HAnchor ha,
                          const VAnchor va) -> menu_builder&
{
  auto& registry = mRegistry.get();
  const auto entity = _add_button(registry,  //
                                  get_menu(),
                                  std::move(label),
                                  action,
                                  offset,
                                  ha,
                                  va);

  auto& toggle = registry.emplace<comp::UiSettingsToggle>(entity);
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

  auto& bind = registry.emplace<comp::UiBind>(bindEntity);
  bind.key = key;
  bind.action = action;

  return *this;
}

auto menu_builder::get_menu() -> comp::UiMenu&
{
  auto& registry = mRegistry.get();
  return registry.get<comp::UiMenu>(mEntity);
}

void menu_builder::add_label(entt::entity entity,
                             std::string text,
                             const font_size size,
                             const glm::vec2& offset,
                             const HAnchor ha,
                             const VAnchor va)

{
  auto& registry = mRegistry.get();
  auto& label = registry.emplace<comp::UiLabel>(entity);
  label.offset = offset;
  label.text = std::move(text);
  label.size = size;
  label.color = cen::colors::white;

  auto& anchor = registry.emplace<comp::UiAnchor>(entity);
  anchor.horizontal = ha;
  anchor.vertical = va;
}

void menu_builder::add_label(std::string text,
                             const font_size size,
                             const glm::vec2& offset,
                             const HAnchor ha,
                             const VAnchor va)
{
  auto& registry = mRegistry.get();
  auto& menu = get_menu();

  const auto entity = registry.create();
  menu.labels.push_back(entity);

  add_label(entity, std::move(text), size, offset, ha, va);
}

}  // namespace wanderer::sys::ui