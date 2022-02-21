#include "ui_system.hpp"

#include <string>   // string
#include <utility>  // move, pair

#include "wanderer/core/centurion_utils.hpp"
#include "wanderer/core/graphics.hpp"
#include "wanderer/core/input_state.hpp"
#include "wanderer/data/cfg.hpp"
#include "wanderer/data/menu_id.hpp"
#include "wanderer/events/misc_events.hpp"
#include "wanderer/misc/assert.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto _process_position(const glm::vec2& pos,
                                     const glm::vec2& size,
                                     const game_cfg& cfg) -> glm::vec2
{
  auto result = pos;

  if (pos.x == -1) {
    result.x = (cfg.logical_size_f.x - size.x) / 2.0f;
  }

  if (pos.y == -1) {
    result.y = (cfg.logical_size_f.y - size.y) / 2.0f;
  }

  return result;
}

void _add_label(entt::registry& registry,
                const entt::entity entity,
                std::string text,
                const glm::vec2& pos,
                const font_size size = font_size::small)
{
  WANDERER_ASSERT_MSG(!text.empty(), "Invalid empty label text!");

  auto& label = registry.emplace<comp::ui_label>(entity);
  label.position = pos;
  label.text = std::move(text);
  label.size = size;
  label.color = cen::colors::white;
}

void _add_label(entt::registry& registry,
                comp::ui_menu& menu,
                std::string text,
                const glm::vec2& pos,
                const font_size size = font_size::small)
{
  const auto entity = menu.labels.emplace_back(registry.create());
  _add_label(registry, entity, std::move(text), pos, size);
}

void _add_button(entt::registry& registry,
                 comp::ui_menu& menu,
                 std::string text,
                 const action_id action,
                 const glm::vec2& pos)
{
  const auto entity = menu.buttons.emplace_back(registry.create());

  auto& button = registry.emplace<comp::ui_button>(entity);
  button.position = pos;
  button.action = action;

  /* The label position is adjusted later, during the first render pass */
  _add_label(registry, entity, std::move(text), pos, font_size::medium);
}

[[nodiscard]] auto _make_menu(entt::registry& registry,
                              std::string title,
                              const bool blocking)
    -> std::pair<entt::entity, comp::ui_menu&>
{
  const auto menuEntity = registry.create();

  auto& menu = registry.emplace<comp::ui_menu>(menuEntity);
  menu.title = std::move(title);
  menu.blocking = blocking;

  if (!menu.title.empty()) {
    _add_label(registry, menu, menu.title, {-1, 70}, font_size::huge);
  }

  return {menuEntity, menu};
}

[[nodiscard]] auto _load_credits_menu(entt::registry& registry) -> entt::entity
{
  auto&& [menuEntity, menu] = _make_menu(registry, "Credits", true);

  _add_button(registry, menu, "Return", action_id::goto_main_menu, {-1, 180});

  return menuEntity;
}

[[nodiscard]] auto _load_saves_menu(entt::registry& registry) -> entt::entity
{
  auto&& [menuEntity, menu] = _make_menu(registry, "Saves", true);

  _add_button(registry, menu, "Return", action_id::goto_main_menu, {-1, 180});

  return menuEntity;
}

[[nodiscard]] auto _load_options_menu(entt::registry& registry) -> entt::entity
{
  auto&& [menuEntity, menu] = _make_menu(registry, "Options", true);

  _add_button(registry, menu, "Return", action_id::goto_main_menu, {-1, 180});

  _add_button(registry,
              menu,
              "Toggle Fullscreen",
              action_id::toggle_fullscreen,
              {-1, 250});

  return menuEntity;
}

[[nodiscard]] auto _load_main_menu(entt::registry& registry) -> entt::entity
{
  auto&& [menuEntity, menu] = _make_menu(registry, "Wanderer", true);

  _add_button(registry, menu, "Play", action_id::goto_game, {-1, 180});
  _add_button(registry, menu, "Options", action_id::goto_options_menu, {-1, 250});
  _add_button(registry, menu, "Saves", action_id::goto_saves_menu, {-1, 300});
  _add_button(registry, menu, "Credits", action_id::goto_credits_menu, {-1, 350});
  _add_button(registry, menu, "Quit", action_id::quit, {-1, 420});

  return menuEntity;
}

[[nodiscard]] auto _load_game_menu(entt::registry& registry) -> entt::entity
{
  auto&& [menuEntity, menu] = _make_menu(registry, "", false);
  return menuEntity;
}

}  // namespace

void load_menus(entt::registry& registry)
{
  auto& ctx = registry.set<comp::ui_menu_ctx>();

  ctx.menus[menu_id::game] = _load_game_menu(registry);
  ctx.menus[menu_id::home] = _load_main_menu(registry);
  ctx.menus[menu_id::options] = _load_options_menu(registry);
  ctx.menus[menu_id::saves] = _load_saves_menu(registry);
  ctx.menus[menu_id::credits] = _load_credits_menu(registry);

  ctx.active_menu = ctx.menus.at(menu_id::home);
}

void update_menus(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  const input_state& input)
{
  const auto& ctx = registry.ctx<comp::ui_menu_ctx>();
  const auto menuEntity = ctx.active_menu;
  WANDERER_ASSERT(menuEntity != entt::null);

  auto& menu = registry.get<comp::ui_menu>(menuEntity);

  for (const auto buttonEntity : menu.buttons) {
    auto& button = registry.get<comp::ui_button>(buttonEntity);
    button.state &= ~comp::ui_button::hover_bit;

    if (button.size.has_value()) {
      const auto bounds = as_rect(button.position, *button.size);
      if (bounds.contains(input.mouse_logical_x(), input.mouse_logical_y())) {
        button.state |= comp::ui_button::hover_bit;

        if (input.was_lmb_released()) {
          dispatcher.enqueue<action_event>(button.action);
        }
      }
    }
  }
}

void switch_menu(entt::registry& registry, const menu_id menu)
{
  auto& ctx = registry.ctx<comp::ui_menu_ctx>();
  ctx.active_menu = ctx.menus.at(menu);
}

auto is_current_menu_blocking(const entt::registry& registry) -> bool
{
  const auto& ctx = registry.ctx<comp::ui_menu_ctx>();
  const auto& menu = registry.get<comp::ui_menu>(ctx.active_menu);
  return menu.blocking;
}

void init_text_labels(const entt::registry& registry, graphics_ctx& graphics)
{
  const auto& renderer = graphics.renderer();
  for (auto&& [entity, label] : registry.view<comp::ui_label>().each()) {
    WANDERER_ASSERT(!label.text.empty());

    if (!label.texture) {
      const auto& font = graphics.get_pixelated_font(label.size);
      const auto surface = font.render_blended(label.text.c_str(), label.color);
      label.texture = renderer.create_texture(surface);
    }
  }
}

void render_active_menu(const entt::registry& registry, graphics_ctx& graphics)
{
  const auto& menus = registry.ctx<comp::ui_menu_ctx>();
  const auto menuEntity = menus.active_menu;
  WANDERER_ASSERT(menuEntity != entt::null);

  const auto& menu = registry.get<comp::ui_menu>(menuEntity);

  if (menu.blocking) {
    constexpr auto bg = cen::colors::black.with_alpha(100);
    graphics.renderer().fill_with(bg);
  }

  const auto& cfg = registry.ctx<game_cfg>();

  for (const auto buttonEntity : menu.buttons) {
    render_button(registry, buttonEntity, graphics);
  }

  for (const auto labelEntity : menu.labels) {
    render_label(registry, labelEntity, graphics);
  }
}

void render_button(const entt::registry& registry,
                   const entt::entity buttonEntity,
                   graphics_ctx& graphics)
{
  const auto& cfg = registry.ctx<game_cfg>();

  const auto& button = registry.get<comp::ui_button>(buttonEntity);
  const auto& label = registry.get<comp::ui_label>(buttonEntity);

  WANDERER_ASSERT(label.texture.has_value());
  const auto& texture = label.texture.value();

  const auto size = texture.size().as_f();
  button.size = {size.width + 20, size.height + 15};

  WANDERER_ASSERT(button.size.has_value());
  button.position = _process_position(button.position, button.size.value(), cfg);

  auto& renderer = graphics.renderer();
  renderer.set_color((button.state & comp::ui_button::hover_bit) ? cen::colors::lime_green
                                                                 : cen::colors::cyan);
  renderer.draw_rect(as_rect(button.position, button.size.value()));

  label.position = {button.position.x + (button.size->x - size.width) / 2.0f,
                    button.position.y + (button.size->y - size.height) / 2.0f};
  render_label(registry, buttonEntity, graphics);
}

void render_label(const entt::registry& registry,
                  const entt::entity labelEntity,
                  graphics_ctx& graphics)
{
  const auto& cfg = registry.ctx<game_cfg>();
  const auto& label = registry.get<comp::ui_label>(labelEntity);

  WANDERER_ASSERT(label.texture.has_value());
  const auto size = label.texture->size().as_f();

  label.position = _process_position(label.position, {size.width, size.height}, cfg);

  auto& renderer = graphics.renderer();
  renderer.render(label.texture.value(), as_point(label.position));
}

}  // namespace wanderer::sys