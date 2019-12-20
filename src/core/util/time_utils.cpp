#include "time_utils.h"
#include <SDL_timer.h>

namespace albinjohansson::wanderer {

uint64_t TimeUtils::GetMillis() noexcept {
  return SDL_GetTicks();
}

uint64_t TimeUtils::GetHighResTime() noexcept {
  return SDL_GetPerformanceCounter();
}

uint64_t TimeUtils::GetHighResFreq() noexcept {
  return SDL_GetPerformanceFrequency();
}

}
