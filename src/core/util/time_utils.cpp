#include "time_utils.h"
#include <SDL_timer.h>

namespace albinjohansson::wanderer {

uint64_t TimeUtils::get_millis() noexcept {
  return SDL_GetTicks();
}

uint64_t TimeUtils::get_high_res_time() noexcept {
  return SDL_GetPerformanceCounter();
}

uint64_t TimeUtils::get_high_res_freq() noexcept {
  return SDL_GetPerformanceFrequency();
}

}
