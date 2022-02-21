#pragma once

#ifdef NDEBUG

#define WANDERER_DEBUG_BUILD 0
#define WANDERER_RELEASE_BUILD 1

#else

#define WANDERER_DEBUG_BUILD 1
#define WANDERER_RELEASE_BUILD 0

#endif  // NDEBUG

#ifdef WIN32
#define WANDERER_PLATFORM_WINDOWS 1
#else
#define WANDERER_PLATFORM_WINDOWS 0
#endif  // WIN32

#ifdef __APPLE__
#define WANDERER_PLATFORM_OSX 1
#else
#define WANDERER_PLATFORM_OSX 0
#endif  // __APPLE__

#ifdef _MSC_VER
#define WANDERER_COMPILER_MSVC 1
#else
#define WANDERER_COMPILER_MSVC 0
#endif  // _MSC_VER

#ifdef __GNUC__
#define WANDERER_COMPILER_GCC 1
#else
#define WANDERER_COMPILER_GCC 0
#endif  // __GNUC__

#ifdef __clang__
#define WANDERER_COMPILER_CLANG 1
#else
#define WANDERER_COMPILER_CLANG 0
#endif  // __clang__

namespace wanderer {

#if WANDERER_DEBUG_BUILD
inline constexpr bool is_debug_build = true;
inline constexpr bool is_release_build = !is_debug_build;
#else
inline constexpr bool is_debug_build = false;
inline constexpr bool is_release_build = !is_debug_build;
#endif  // WANDERER_DEBUG_BUILD

#if WANDERER_PLATFORM_WINDOWS
inline constexpr bool is_windows = true;
inline constexpr bool on_windows = true;
#else
inline constexpr bool is_windows = false;
inline constexpr bool on_windows = false;
#endif  // WANDERER_PLATFORM_WINDOWS

#ifdef WANDERER_PLATFORM_OSX
inline constexpr bool is_osx = true;
inline constexpr bool on_osx = true;
#else
inline constexpr bool is_osx = false;
inline constexpr bool on_osx = false;
#endif  // WANDERER_PLATFORM_OSX

}  // namespace wanderer