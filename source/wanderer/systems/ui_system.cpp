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
                                       const HAnchor halign,
                                       const VAnchor valign) -> glm::vec2
{
  glm::vec2 position{};
  const auto absoluteOffset = offset * cfg.logical_size_f;

  switch (halign) {
    case HAnchor::left:
      position.x = absoluteOffset.x;
      break;

    case HAnchor::center:
      position.x = ((cfg.logical_size_f.x - size.x) / 2.0f) + absoluteOffset.x;
      break;

    case HAnchor::right:
      position.x = cfg.logical_size_f.x - size.x - absoluteOffset.x;
      break;
  }

  switch (valign) {
    case VAnchor::top:
      position.y = absoluteOffset.y;
      break;

    case VAnchor::center:
      position.y = ((cfg.logical_size_f.y - size.y) / 2.0f) + absoluteOffset.y;
      break;

    case VAnchor::bottom:
      position.y = cfg.logical_size_f.y - size.y - absoluteOffset.y;
      break;
  }

  return position;
}

[[nodiscard]] auto _load_credits_menu(entt::registry& registry) -> entt::entity
{
  return ui::menu_builder::build(registry)
      .title("Credits")
      .blocking()
      .button("Return", action_id::goto_main_menu, {0, 0.25f})
      .m_label("Textures by ...", {0, 0.4f}, HAnchor::center, VAnchor::top)
      .bind(cen::scancodes::escape, action_id::goto_main_menu)
      .result();
}

[[nodiscard]] auto _load_saves_menu(entt::registry& registry) -> entt::entity
{
  using ha = HAnchor;
  using va = VAnchor;
  return ui::menu_builder::build(registry)
      .title("Saves")
      .blocking()
      .button("Return", action_id::goto_main_menu, {0, 0.25f})

      .button("      <      ", action_id::noop, {0.14f, 0.10f}, ha::left, va::bottom)
      .button("      >      ", action_id::noop, {0.24f, 0.10f}, ha::left, va::bottom)
      // .line({0.22f, 0.35f}, {0.22f, 0.92f}, ha::left, va::top)

      .button("Load", action_id::noop, {0.38f, 0.10f}, ha::left, va::bottom)
      .button("Delete", action_id::noop, {0.46f, 0.10f}, ha::left, va::bottom)

      /* Vertical lines */
      .line({0.09f, 0.35f}, {0.09f, 0.92f}, ha::left, va::top)
      .line({0.35f, 0.35f}, {0.35f, 0.92f}, ha::left, va::top)
      .line({0.35f, 0.35f}, {0.35f, 0.92f}, ha::left, va::top)
      .line({0.09f, 0.35f}, {0.09f, 0.92f}, ha::right, va::top)

      /* Horizontal lines */
      .line({0.36f, 0.15f}, {0.90f, 0.15f}, ha::left, va::bottom)
      .line({0.10f, 0.15f}, {0.34f, 0.15f}, ha::left, va::bottom)
      // .line({0.10f, 0.34f}, {0.34f, 0.34f}, ha::left, va::top)

      .bind(cen::scancodes::escape, action_id::goto_main_menu)
      .result();
}

[[nodiscard]] auto _load_options_menu(entt::registry& registry) -> entt::entity
{
  return ui::menu_builder::build(registry)
      .title("Options")
      .blocking()
      .button("Return", action_id::goto_main_menu, {0, 0.25f})
      .toggle("Fullscreen",
              action_id::toggle_fullscreen,
              settings::fullscreen_bit,
              {0.45f, 0.40f},
              HAnchor::right,
              VAnchor::top)
      .toggle("VSync",
              action_id::toggle_vsync,
              settings::vsync_bit,
              {0.45f, 0.50f},
              HAnchor::right,
              VAnchor::top)
      .toggle("Integer Scaling",
              action_id::toggle_integer_scaling,
              settings::integer_scaling_bit,
              {0.45f, 0.60f},
              HAnchor::right,
              VAnchor::top)
      .bind(cen::scancodes::escape, action_id::goto_main_menu)
      .result();
}

[[nodiscard]] auto _load_main_menu(entt::registry& registry) -> entt::entity
{
  return ui::menu_builder::build(registry)
      .title("Wanderer")
      .blocking()
      .button("Play", action_id::goto_game, {0, 0.25f})
      .button("Options", action_id::goto_options_menu, {0, 0.40f})
      .button("Saves", action_id::goto_saves_menu, {0, 0.50f})
      .button("Credits", action_id::goto_credits_menu, {0, 0.60f})
      .button("Quit", action_id::quit, {0, 0.75f})
      .s_label("Albin Johansson ( C) 2018-2022",
               {0.01f, 0.01f},
               HAnchor::left,
               VAnchor::bottom)
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
  auto& ctx = registry.set<comp::UiMenus>();

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
  const auto& ctx = registry.ctx<comp::UiMenus>();
  const auto menuEntity = ctx.active_menu;
  WANDERER_ASSERT(menuEntity != entt::null);

  auto& menu = registry.get<comp::UiMenu>(menuEntity);

  for (const auto buttonEntity : menu.buttons) {
    auto& button = registry.get<comp::UiButton>(buttonEntity);
    button.state &= ~comp::UiButton::hover_bit;

    if (button.position && button.size) {
      const auto bounds = as_rect(*button.position, *button.size);
      if (bounds.contains(input.mouse_logical_x(), input.mouse_logical_y())) {
        button.state |= comp::UiButton::hover_bit;

        if (input.was_lmb_released()) {
          dispatcher.enqueue<action_event>(button.action);
        }
      }
    }
  }

  for (const auto bindEntity : menu.binds) {
    const auto& bind = registry.get<comp::UiBind>(bindEntity);
    if (input.was_released(bind.key)) {
      dispatcher.enqueue<action_event>(bind.action);
    }
  }
}

void switch_menu(entt::registry& registry, const menu_id menu)
{
  auto& ctx = registry.ctx<comp::UiMenus>();
  ctx.active_menu = ctx.menus.at(menu);
}

auto is_current_menu_blocking(const entt::registry& registry) -> bool
{
  const auto& ctx = registry.ctx<comp::UiMenus>();
  const auto& menu = registry.get<comp::UiMenu>(ctx.active_menu);
  return menu.blocking;
}

void init_text_labels(const entt::registry& registry, graphics_ctx& graphics)
{
  const auto& renderer = graphics.renderer();
  for (auto&& [entity, label] : registry.view<comp::UiLabel>().each()) {
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
  const auto& menus = registry.ctx<comp::UiMenus>();
  const auto menuEntity = menus.active_menu;
  WANDERER_ASSERT(menuEntity != entt::null);

  const auto& menu = registry.get<comp::UiMenu>(menuEntity);

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

  for (const auto lineEntity : menu.lines) {
    render_line(registry, lineEntity, graphics);
  }
}

void render_button(const entt::registry& registry,
                   const entt::entity buttonEntity,
                   graphics_ctx& graphics,
                   const settings& settings)
{
  constexpr cen::color button_bg{0x33, 0x33, 0x33};

  /* Render label first since we base the button frame on the label position */
  render_label(registry, buttonEntity, graphics);

  const auto& button = registry.get<comp::UiButton>(buttonEntity);
  const auto& label = registry.get<comp::UiLabel>(buttonEntity);

  WANDERER_ASSERT(label.texture.has_value());
  const auto& texture = label.texture.value();

  const auto size = texture.size().as_f();
  button.size = {size.width + 20, size.height + 15};

  button.position = glm::vec2{label.position->x - (button.size->x - size.width) / 2.0f,
                              label.position->y - (button.size->y - size.height) / 2.0f};

  auto& renderer = graphics.renderer();
  const auto bounds = as_rect(button.position.value(), button.size.value());

  /* We can't have the background be too strong, since the label is drawn before */
  renderer.set_color(button_bg.with_alpha(20));
  renderer.fill_rect(bounds);

  renderer.set_color((button.state & comp::UiButton::hover_bit) ? cen::colors::lime_green
                                                                : cen::colors::white);
  renderer.draw_rect(bounds);

  if (const auto* toggle = registry.try_get<comp::UiSettingsToggle>(buttonEntity)) {
    const auto x = bounds.max_x() + 5;
    const auto y = bounds.y();

    const cen::frect box{x, y, bounds.height(), bounds.height()};
    renderer.set_color(button_bg);
    renderer.fill_rect(box);

    if (settings.test_flag(toggle->flag)) {
      renderer.set_color(cen::colors::white);
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
  const auto& label = registry.get<comp::UiLabel>(labelEntity);
  const auto& anchor = registry.get<comp::UiAnchor>(labelEntity);

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

void render_line(const entt::registry& registry,
                 entt::entity lineEntity,
                 graphics_ctx& graphics)
{
  const auto& cfg = registry.ctx<game_cfg>();
  const auto& line = registry.get<comp::UiLine>(lineEntity);
  const auto& anchor = registry.get<comp::UiAnchor>(lineEntity);

  const auto start =
      _calculate_position(line.start, {0, 0}, cfg, anchor.horizontal, anchor.vertical);

  const auto end =
      _calculate_position(line.end, {0, 0}, cfg, anchor.horizontal, anchor.vertical);

  auto& renderer = graphics.renderer();
  renderer.set_color(line.color);
  renderer.draw_line(as_point(start), as_point(end));
}

}  // namespace wanderer::sys