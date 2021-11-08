#include "dev_console_system.hpp"

#include <cassert>      // assert
#include <regex>        // regex, regex_search, smatch, ssub_match
#include <string>       // string
#include <string_view>  // string_view
#include <vector>       // vector

#include <rune/rune.hpp>  // from_string

#include "core/game_constants.hpp"
#include "core/graphics/graphics_context.hpp"
#include "events/switch_map_event.hpp"
#include "systems/ui/menus/menu_system.hpp"
#include "wanderer_std.hpp"

namespace wanderer::sys {
namespace {

inline std::vector<std::string> history;
inline std::string current_cmd;

[[nodiscard]] auto ParseInt(const std::ssub_match& match) -> Maybe<int32>
{
  return rune::from_string<int32>(match.first.operator->());
}

[[nodiscard]] auto ParseFloat(const std::ssub_match& match) -> Maybe<float>
{
  return rune::from_string<float>(match.first.operator->());
}

/* We make use of std::regex because it makes our lives easier, even if the library has
   some issues. This is not performance critical code anyways :) */
void InterpretCommand(entt::dispatcher& dispatcher, const std::string& cmd)
{
  // SYNTAX
  //           god
  //        setday <mon|tue|wed|thu|fri|sat|sun>
  //       settime <II:II>
  //   settimerate <F>
  //  setdaylength <I>
  //         enter <I>
  //         spawn <skeleton|...>

  if (cmd == "god") {
    cen::log::info("Toggle player god mode");
    // TODO
  }
  else if (cmd.starts_with("setday")) {
    if (const auto day = ParseSetDayCommand(cmd)) {
      cen::log::info("Parsed day: %i", *day);
      // TODO
    }
    else {
      cen::log::warn("Invalid syntax/input for the SETDAY command!");
    }
  }
  else if (cmd.starts_with("settime")) {
    if (const auto result = ParseSetTimeCommand(cmd)) {
      cen::log::info("Matched time (%i:%i)", result->hour, result->minutes);
      // TODO
    }
    else {
      cen::log::warn("Invalid syntax/input for the SETTIME command!");
    }
  }
  else if (cmd.starts_with("settimerate")) {
    // TODO
  }
  else if (cmd.starts_with("setdaylength")) {
    // TODO
  }
  else if (cmd.starts_with("enter")) {
    if (const auto id = ParseEnterCommand(cmd)) {
      dispatcher.enqueue<SwitchMapEvent>(*id);
    }
    else {
      cen::log::warn("Invalid syntax/input for the ENTER command!");
    }
  }
  else if (cmd.starts_with("spawn")) {
    // TODO
  }
}

}  // namespace

void UpdateDevConsole(const cen::keyboard_event& event, entt::dispatcher& dispatcher)
{
  if (event.pressed()) {
    if (event.is_active(cen::scancodes::backspace)) {
      if (!current_cmd.empty()) {
        current_cmd.pop_back();
      }
    }
    else if (event.is_active(cen::scancodes::enter)) {
      InterpretCommand(dispatcher, current_cmd);
      history.push_back(current_cmd);
      current_cmd.clear();
    }
  }
}

void UpdateDevConsole(const cen::text_input_event& event)
{
  current_cmd += event.text_utf8();
}

void RenderDevConsole(const entt::registry& shared)
{
  if (IsMenuActive(shared, MenuId::DevConsole)) {
    auto& graphics = shared.ctx<Ref<GraphicsContext>>().get();

    auto& renderer = graphics.GetRenderer();
    renderer.set_color(cen::colors::black.with_alpha(200));

    const auto width = glob::logical_width<int>;
    const auto height = glob::logical_height<int>;

    const auto baseY = height / 2;
    renderer.fill_rect(cen::rect(0, baseY, width, height / 2));

    const auto offset = 20;
    const auto size = static_cast<int>(history.size());

    for (int i = 0; i < size; ++i) {
      const auto y = (baseY + 10) + (i * offset);
      graphics.RenderOutlinedText(history.at(i), {10, y});
    }

    const auto y = (baseY + 10) + (size * offset);

    // Caret
    renderer.set_color(cen::colors::white);
    renderer.draw_rect(cen::rect(6, y - 2, 2, 12));

    if (!current_cmd.empty()) {
      graphics.RenderOutlinedText(current_cmd, {10, y});
    }
  }
}

auto ParseSetTimeCommand(const std::string& cmd) -> Maybe<SetTimeResult>
{
  // Matches HH:MM (doesn't match invalid times)
  static const std::regex regex{"((?:[01][0-9])|(?:2[0-3])):([0-5][0-9])",
                                std::regex::optimize};

  std::smatch matches;
  if (std::regex_search(cmd, matches, regex)) {
    assert(matches.size() == 3);

    SetTimeResult result;
    result.hour = ParseInt(matches[1]).value();
    result.minutes = ParseInt(matches[2]).value();

    return result;
  }
  else {
    return std::nullopt;
  }
}

auto ParseSetDayCommand(const std::string& cmd) -> Maybe<DayOfWeek>
{
  static const std::regex regex{"(?:mon|tue|wed|thu|fri|sat|sun)", std::regex::optimize};

  std::smatch matches;
  if (std::regex_search(cmd, matches, regex)) {
    assert(matches.size() == 1);
    const auto day = matches[0].str();
    return ParseDayOfWeek(day);
  }
  else {
    return std::nullopt;
  }
}

auto ParseEnterCommand(const std::string& cmd) -> Maybe<MapID>
{
  static const std::regex regex{"[0-9]+", std::regex::optimize};

  std::smatch matches;
  if (std::regex_search(cmd, matches, regex)) {
    assert(matches.size() == 1);
    return ParseInt(matches[0]).value();
  }
  else {
    return std::nullopt;
  }
}

}  // namespace wanderer::sys
