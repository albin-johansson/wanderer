#pragma once

#include <centurion.hpp>

#include "wanderer/misc/logging.hpp"

#ifdef NDEBUG
#define WANDERER_PROFILE_START
#else
#define WANDERER_PROFILE_START const auto wndr_profile_start = cen::now();
#endif  // NDEBUG

#ifdef NDEBUG
#define WANDERER_PROFILE_END(Msg)
#else
#define WANDERER_PROFILE_END(Msg)                                       \
  const auto wndr_profile_end = cen::now();                             \
  const auto wndr_profile_diff =                                        \
      static_cast<double>(wndr_profile_end - wndr_profile_start);       \
  const auto wndr_profile_freq = static_cast<double>(cen::frequency()); \
  wanderer::log_debug(Msg " in {} seconds", wndr_profile_diff / wndr_profile_freq);
#endif  // NDEBUG