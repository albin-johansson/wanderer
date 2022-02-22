#include "ui_system.hpp"

#include <string>   // string
#include <utility>  // move, pair

#include "ui/menu_builder.hpp"
#include "wanderer/core/centurion_utils.hpp"
#include "wanderer/core/graphics.hpp"
#include "wanderer/core/input_state.hpp"
#include "wanderer/data/cfg.hpp"
#include "wanderer/data/menu_id.hpp"
#include "wanderer/events/misc_events.hpp"
#include "wanderer/io/settings.hpp"
#include "wanderer/misc/assert.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto _calculate_position(const glm::vec2& offset,
                                       const glm::vec2& size,
                                       const game_cfg& cfg,
                                       const h_anchor halign,
                                       const v_anchor valign) -> glm::vec2
{
  glm::vec2 position{};

  switch (halign) {
    case h_anchor::left:
      position.x = offset.x;
      break;

    case h_anchor::center:
      position.x = ((cfg.logical_size_f.x - size.x) / 2.0f) + offset.x;
      break;

    case h_anchor::right:
      position.x = cfg.logical_size_f.x - size.x - offset.x;
      break;
  }

  switch (valign) {
    case v_anchor::top:
      position.y = offset.y;
      break;

    case v_anchor::center:
      position.y = ((cfg.logical_size_f.y - size.y) / 2.0f) + offset.y;
      break;

    case v_anchor::bottom:
      position.y = cfg.logical_size_f.y - size.y - offset.y;
      break;
  }

  return position;
}

[[nodiscard]] auto _load_credits_menu(entt::registry& registry) -> entt::entity
{
  return ui::menu_builder::build(registry)
      .title("Credits")
      .blocking()
      .button("Return", action_id::goto_main_menu, {0, 180})
      .m_label("Textures by ...", {0, 300}, h_anchor::center, v_anchor::top)
      .bind(cen::scancodes::escape, action_id::goto_main_menu)
      .result();
}

[[nodiscard]] auto _load_saves_menu(entt::registry& registry) -> entt::entity
{
  return ui::menu_builder::build(registry)
      .title("Saves")
      .blocking()
      .button("Return", action_id::goto_main_menu, {0, 180})
      .bind(cen::scancodes::escape, action_id::goto_main_menu)
      .result();
}

[[nodiscard]] auto _load_options_menu(entt::registry& registry) -> entt::entity
{
  return ui::menu_builder::build(registry)
      .title("Options")
      .blocking()
      .button("Return", action_id::goto_main_menu, {0, 180})
      .toggle("Toggle Fullscreen",
              action_id::toggle_fullscreen,
              settings::fullscreen_bit,
              {0, 300})
      .toggle("Toggle VSync", action_id::toggle_vsync, settings::vsync_bit, {0, 350})
      .bind(cen::scancodes::escape, action_id::goto_main_menu)
      .result();
}

[[nodiscard]] auto _load_main_menu(entt::registry& registry) -> entt::entity
{
  return ui::menu_builder::build(registry)
      .title("Wanderer")
      .blocking()
      .button("Play", action_id::goto_game, {0, 180})
      .button("Options", action_id::goto_options_menu, {0, 300})
      .button("Saves", action_id::goto_saves_menu, {0, 350})
      .button("Credits", action_id::goto_credits_menu, {0, 400})
      .button("Quit", action_id::quit, {0, 500})
      .bind(cen::scancodes::escape, action_id::goto_game)
      .result();
}

[[nodiscard]] auto _load_game_menu(entt::registry& registry) -> entt::entity
{
  return ui::menu_builder::build(registry)
      .bind(cen::scancodes::escape, action_id::goto_main_menu)
      .result();
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

    if (button.position && button.size) {
      const auto bounds = as_rect(*button.position, *button.size);
      if (bounds.contains(input.mouse_logical_x(), input.mouse_logical_y())) {
        button.state |= comp::ui_button::hover_bit;

        if (input.was_lmb_released()) {
          dispatcher.enqueue<action_event>(button.action);
        }
      }
    }
  }

  for (const auto bindEntity : menu.binds) {
    const auto& bind = registry.get<comp::ui_bind>(bindEntity);
    if (input.was_released(bind.key)) {
      dispatcher.enqueue<action_event>(bind.action);
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

void render_active_menu(const entt::registry& registry,
                        graphics_ctx& graphics,
                        const settings& settings)
{
  const auto& menus = registry.ctx<comp::ui_menu_ctx>();
  const auto menuEntity = menus.active_menu;
  WANDERER_ASSERT(menuEntity != entt::null);

  const auto& menu = registry.get<comp::ui_menu>(menuEntity);

  if (menu.blocking) {
    constexpr auto bg = cen::colors::black.with_alpha(100);
    graphics.renderer().fill_with(bg);
  }

  for (const auto labelEntity : menu.labels) {
    render_label(registry, labelEntity, graphics);
  }

  for (const auto buttonEntity : menu.buttons) {
    render_button(registry, buttonEntity, graphics, settings);
  }
}

void render_button(const entt::registry& registry,
                   const entt::entity buttonEntity,
                   graphics_ctx& graphics,
                   const settings& settings)
{
  /* Render label first since we base the button frame on the label position */
  render_label(registry, buttonEntity, graphics);

  const auto& button = registry.get<comp::ui_button>(buttonEntity);
  const auto& label = registry.get<comp::ui_label>(buttonEntity);

  WANDERER_ASSERT(label.texture.has_value());
  const auto& texture = label.texture.value();

  const auto size = texture.size().as_f();
  button.size = {size.width + 20, size.height + 15};

  button.position = glm::vec2{label.position->x - (button.size->x - size.width) / 2.0f,
                              label.position->y - (button.size->y - size.height) / 2.0f};

  auto& renderer = graphics.renderer();
  renderer.set_color((button.state & comp::ui_button::hover_bit) ? cen::colors::lime_green
                                                                 : cen::colors::white);
  const auto bounds = as_rect(button.position.value(), button.size.value());
  renderer.draw_rect(bounds);

  if (const auto* toggle = registry.try_get<comp::ui_setting_toggle>(buttonEntity)) {
    const auto x = bounds.max_x() + 5;
    const auto y = bounds.y();

    const cen::frect box{x, y, bounds.height(), bounds.height()};
    renderer.set_color(cen::color{0x33, 0x33, 0x33});
    renderer.fill_rect(box);

    if (settings.test_flag(toggle->flag)) {
      renderer.set_color(cen::colors::lime);
      const cen::frect innerBox{box.x() + 4,
                                box.y() + 4,
                                box.width() - 8,
                                box.height() - 8};
      renderer.fill_rect(innerBox);
    }

    renderer.set_color(cen::colors::white);
    renderer.draw_rect(box);
  }
}

void render_label(const entt::registry& registry,
                  const entt::entity labelEntity,
                  graphics_ctx& graphics)
{
  const auto& cfg = registry.ctx<game_cfg>();
  const auto& label = registry.get<comp::ui_label>(labelEntity);
  const auto& anchor = registry.get<comp::ui_anchor>(labelEntity);

  WANDERER_ASSERT(label.texture.has_value());
  const auto size = label.texture->size().as_f();

  label.position = _calculate_position(label.offset,
                                       {size.width, size.height},
                                       cfg,
                                       anchor.horizontal,
                                       anchor.vertical);

  auto& renderer = graphics.renderer();
  renderer.render(label.texture.value(), as_point(label.position.value()));
}

}  // namespace wanderer::sys