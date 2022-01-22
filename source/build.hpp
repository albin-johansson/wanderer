#pragma once

#ifdef NDEBUG

#define WANDERER_DEBUG_BUILD 0
#define WANDERER_RELEASE_BUILD 1

#else

#define WANDERER_DEBUG_BUILD 1
#define WANDERER_RELEASE_BUILD 0

#endif  // NDEBUG

namespace wanderer {

#if WANDERER_DEBUG_BUILD
inline constexpr bool is_debug_build = true;
inline constexpr bool is_release_build = !is_debug_build;
#else
inline constexpr bool is_debug_build = false;
inline constexpr bool is_release_build = !is_debug_build;
#endif  // WANDERER_DEBUG_BUILD

}  // namespace wanderer