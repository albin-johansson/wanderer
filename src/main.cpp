// clang-format off
#define RUNE_TEXTURE_ID_UNDERLYING_TYPE entt::id_type
// clang-format on

#include <SDL.h>

#include <centurion.hpp>  // library
#include <cstdio>         // printf
#include <entt.hpp>       // id_type

#include "core/utils/time_utils.hpp"
#include "wanderer_engine.hpp"

inline void wanderer_log(void* data,
                         const int category,
                         const SDL_LogPriority priority,
                         const char* msg)
{
  const auto time = wanderer::current_hhmmss();
  switch (priority)
  {
    default:
      [[fallthrough]];
    case SDL_LOG_PRIORITY_INFO:
      std::printf("LOG %s [INFO] >> %s\n", time.c_str(), msg);
      break;

    case SDL_LOG_PRIORITY_VERBOSE:
      std::printf("LOG %s [VERBOSE] >> %s\n", time.c_str(), msg);
      break;

    case SDL_LOG_PRIORITY_DEBUG:
      std::printf("LOG %s [DEBUG] >> %s\n", time.c_str(), msg);
      break;

    case SDL_LOG_PRIORITY_WARN:
      std::printf("LOG %s [WARNING] >> %s\n", time.c_str(), msg);
      break;

    case SDL_LOG_PRIORITY_ERROR:
      std::printf("LOG %s [ERROR] >> %s\n", time.c_str(), msg);
      break;

    case SDL_LOG_PRIORITY_CRITICAL:
      std::printf("LOG %s [CRITICAL] >> %s\n", time.c_str(), msg);
      break;
  }
}

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