#include "cinematic_system.hpp"

#include <fmt/chrono.h>

#include "ui_system.hpp"
#include "wanderer/core/centurion_utils.hpp"
#include "wanderer/core/graphics.hpp"
#include "wanderer/data/cfg.hpp"
#include "wanderer/data/components/rendering.hpp"
#include "wanderer/data/components/ui.hpp"

using namespace cen::literals::time_literals;

namespace wanderer::sys {
namespace {

[[nodiscard]] auto _determine_cinematic_text_alpha(const comp::cinematic_fade& cinematic)
    -> uint8
{
  auto asFloat = [](auto duration) { return static_cast<float64>(duration.count()); };

  const auto duration = cen::ticks64() - cinematic.start;

  if (duration <= cinematic.transition) {
    const auto ratio = asFloat(duration) / asFloat(cinematic.transition);
    return static_cast<uint8>(ratio * 255.0);
  }
  else if (duration > cinematic.transition &&
           duration <= cinematic.transition + cinematic.pause) {
    return 255;
  }
  else {
    const auto progress = duration - (cinematic.transition + cinematic.pause);
    const auto ratio = asFloat(progress) / asFloat(cinematic.transition);
    return 255 - static_cast<uint8>(ratio * 255.0);
  }
}

}  // namespace

void schedule_startup_cinematic_fade(entt::registry& registry)
{
  auto& cinematic = registry.set<comp::cinematic_fade>();
  cinematic.start = cen::ticks64();
  cinematic.transition = 750_ms;
  cinematic.pause = 1'500_ms;
  cinematic.bg = cen::colors::black;

  const auto titleEntity = cinematic.labels.emplace_back(registry.create());
  auto& title = registry.emplace<comp::ui_label>(titleEntity);
  title.position = {-1, 250};
  title.text = "Wanderer";
  title.color = cen::colors::white;
  title.size = font_size::huge;

  {
    const auto labelEntity = cinematic.labels.emplace_back(registry.create());
    auto& text = registry.emplace<comp::ui_label>(labelEntity);
    text.position = {-1, 320};
    text.text = "A game by Albin Johansson";
    text.color = cen::colors::white;
    text.size = font_size::medium;
  }
}

void update_cinematic_fade(entt::registry& registry)
{
  if (auto* cinematic = registry.try_ctx<comp::cinematic_fade>()) {
    const auto diff = cen::ticks64() - cinematic->start;
    const auto total = (cinematic->transition * 2u) + cinematic->pause;
    if (diff >= total) {
      for (const auto labelEntity : cinematic->labels) {
        registry.destroy(labelEntity);
      }

      registry.unset<comp::cinematic_fade>();
    }
  }
}

void render_cinematic_fade(const entt::registry& registry, graphics_ctx& graphics)
{
  if (const auto* cinematic = registry.try_ctx<comp::cinematic_fade>()) {
    graphics.renderer().fill_with(cinematic->bg);

    const auto alpha = _determine_cinematic_text_alpha(*cinematic);

    for (const auto labelEntity : cinematic->labels) {
      const auto& label = registry.get<comp::ui_label>(labelEntity);
      label.texture.value().set_alpha_mod(alpha);
      render_label(registry, labelEntity, graphics);
    }
  }
}

auto is_cinematic_fade_active(const entt::registry& registry) -> bool
{
  return registry.try_ctx<comp::cinematic_fade>() != nullptr;
}

}  // namespace wanderer::sys