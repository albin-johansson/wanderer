#pragma once

#include <string>  // string

#include <centurion.hpp>  // keyboard_event, text_input_event
#include <entt.hpp>       // registry, dispatcher

#include "core/day_of_week.hpp"
#include "wanderer_std.hpp"

namespace wanderer::sys {

struct SetTimeResult final
{
  int32 hour{};
  int32 minutes{};
};

void UpdateDevConsole(const cen::keyboard_event& event, entt::dispatcher& dispatcher);

void UpdateDevConsole(const cen::text_input_event& event);

void RenderDevConsole(const entt::registry& shared);

[[nodiscard]] auto ParseSetTimeCommand(const std::string& cmd) -> Maybe<SetTimeResult>;

[[nodiscard]] auto ParseSetDayCommand(const std::string& cmd) -> Maybe<DayOfWeek>;

[[nodiscard]] auto ParseEnterCommand(const std::string& cmd) -> Maybe<MapID>;

}  // namespace wanderer::sys
