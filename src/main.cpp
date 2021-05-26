// clang-format off
#define RUNE_TEXTURE_ID_UNDERLYING_TYPE entt::id_type
// clang-format on

#include <SDL.h>

#include <centurion.hpp>  // library
#include <entt.hpp>       // id_type
#include <format>         // format
#include <iostream>       // clog
#include <string_view>    // string_view

#include "core/utils/time_utils.hpp"
#include "wanderer_engine.hpp"

namespace {

[[nodiscard]] auto to_string(const SDL_LogPriority priority) noexcept -> std::string_view
{
  switch (priority)
  {
    default:
      [[fallthrough]];

    case SDL_LOG_PRIORITY_INFO:
      return "INFO";

    case SDL_LOG_PRIORITY_VERBOSE:
      return "VERBOSE";

    case SDL_LOG_PRIORITY_DEBUG:
      return "DEBUG";

    case SDL_LOG_PRIORITY_WARN:
      return "WARNING";

    case SDL_LOG_PRIORITY_ERROR:
      return "ERROR";

    case SDL_LOG_PRIORITY_CRITICAL:
      return "CRITICAL";
  }
}

void wanderer_log(void* /*data*/,
                  const int /*category*/,
                  const SDL_LogPriority priority,
                  const char* msg)
{
  const auto time = wanderer::current_hhmmss();
  std::clog << std::format("LOG {} [{}] > {}\n", time, to_string(priority), msg);
}

}  // namespace

auto main(int, char**) -> int
{
  cen::library centurion;
  SDL_LogSetOutputFunction(wanderer_log, nullptr);

  if constexpr (cen::is_debug_build())
  {
    cen::log::set_priority(cen::log_priority::debug);
  }

  wanderer::wanderer_engine engine;
  return engine.run();
}