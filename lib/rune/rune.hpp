/*
 * MIT License
 * Copyright (c) 2021 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

// #include "rune/aliases/czstring.hpp"


namespace rune {

/// \addtogroup core
/// \{

using czstring = const char*;

/// \} End of group

}  // namespace rune

// #include "rune/aliases/delta_time.hpp"
#ifndef RUNE_ALIASES_DELTA_TIME_HPP
#define RUNE_ALIASES_DELTA_TIME_HPP

namespace rune {

#ifndef RUNE_DELTA_TIME_TYPE
#define RUNE_DELTA_TIME_TYPE float
#endif  // RUNE_DELTA_TIME_TYPE

/**
 * \brief The type used for delta time values, e.g. in the `tick()` function of game class
 * implementations.
 *
 * \details By default, this alias is equivalent to `float`.
 *
 * \ingroup core
 *
 * \see `RUNE_DELTA_TIME_TYPE`
 */
using delta_time = RUNE_DELTA_TIME_TYPE;

}  // namespace rune

#endif  // RUNE_ALIASES_DELTA_TIME_HPP

// #include "rune/aliases/integers.hpp"
#ifndef RUNE_ALIASES_INTEGERS_HPP
#define RUNE_ALIASES_INTEGERS_HPP

#include <centurion.hpp>  // ...

namespace rune {

/// \addtogroup core
/// \{

/// Unsigned integer.
using uint = cen::uint;

/// Used as the argument type to integral literal operators.
using ulonglong = cen::ulonglong;

/// 8-bit signed integer.
using int8 = cen::i8;

/// 16-bit signed integer.
using int16 = cen::i16;

/// 32-bit signed integer.
using int32 = cen::i32;

/// 64-bit signed integer.
using int64 = cen::i64;

/// 8-bit unsigned integer.
using uint8 = cen::u8;

/// 16-bit unsigned integer.
using uint16 = cen::u16;

/// 32-bit unsigned integer.
using uint32 = cen::u32;

/// 64-bit unsigned integer.
using uint64 = cen::u64;

/// \} End of group core

}  // namespace rune

#endif  // RUNE_ALIASES_INTEGERS_HPP

// #include "rune/core/aabb_tree.hpp"

// #include "rune/core/compiler.hpp"
#ifndef RUNE_CORE_COMPILER_HPP
#define RUNE_CORE_COMPILER_HPP

namespace rune {

/// \addtogroup core
/// \{

/// \name Compiler checks
/// \{

/// Indicates whether or not the current compiler is MSVC
[[nodiscard]] constexpr auto on_msvc() noexcept -> bool
{
#ifdef _MSC_VER
  return true;
#else
  return false;
#endif  // _MSC_VER
}

/// Indicates whether or not the current compiler is GCC
[[nodiscard]] constexpr auto on_gcc() noexcept -> bool
{
#ifdef __GNUC__
  return true;
#else
  return false;
#endif  // __GNUC__
}

/// Indicates whether or not the current compiler is Clang
[[nodiscard]] constexpr auto on_clang() noexcept -> bool
{
#ifdef __clang__
  return true;
#else
  return false;
#endif  // __clang__
}

/// \} End of compiler checks

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CORE_COMPILER_HPP

// #include "rune/core/concepts.hpp"
#ifndef RUNE_CORE_CONCEPTS_HPP
#define RUNE_CORE_CONCEPTS_HPP

#include <type_traits>  // is_arithmetic_v, is_same_v

namespace rune {

/// \addtogroup core
/// \{

/// Concept for a type that is either integral or floating-point, but not `bool`.
template <typename T>
concept numeric = std::is_arithmetic_v<T> && !std::is_same_v<T, bool>;

// clang-format off

template <typename T>
concept has_value_type = requires
{
  typename T::value_type;
};

// clang-format on

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CORE_CONCEPTS_HPP
// #include "rune/core/engine.hpp"
#ifndef RUNE_CORE_ENGINE_HPP
#define RUNE_CORE_ENGINE_HPP

#include <centurion.hpp>  // window
#include <concepts>       // derived_from

// #include "game.hpp"
#ifndef RUNE_CORE_GAME_HPP
#define RUNE_CORE_GAME_HPP

#include <concepts>  // convertible_to

// #include "../aliases/delta_time.hpp"
#ifndef RUNE_ALIASES_DELTA_TIME_HPP
#define RUNE_ALIASES_DELTA_TIME_HPP

namespace rune {

#ifndef RUNE_DELTA_TIME_TYPE
#define RUNE_DELTA_TIME_TYPE float
#endif  // RUNE_DELTA_TIME_TYPE

/**
 * \brief The type used for delta time values, e.g. in the `tick()` function of game class
 * implementations.
 *
 * \details By default, this alias is equivalent to `float`.
 *
 * \ingroup core
 *
 * \see `RUNE_DELTA_TIME_TYPE`
 */
using delta_time = RUNE_DELTA_TIME_TYPE;

}  // namespace rune

#endif  // RUNE_ALIASES_DELTA_TIME_HPP

// #include "graphics.hpp"
#ifndef RUNE_CORE_GRAPHICS_HPP
#define RUNE_CORE_GRAPHICS_HPP

#include <centurion.hpp>  // window, renderer, texture, font_cache, pixel_format
#include <cstddef>        // size_t
#include <string>         // string
#include <unordered_map>  // unordered_map
#include <utility>        // forward
#include <vector>         // vector

namespace rune {

/// \addtogroup core
/// \{

/// \name Configuration macros
/// \{

/**
 * \def RUNE_GRAPHICS_RENDERER_FLAGS
 *
 * \brief The renderer flags used when creating `graphics` instances.
 *
 * \note This macro should expand to a `uint32` value.
 *
 * \details By default, this macro expands to `cen::renderer::default_flags()`.
 */
#ifndef RUNE_GRAPHICS_RENDERER_FLAGS
#define RUNE_GRAPHICS_RENDERER_FLAGS cen::renderer::default_flags()
#endif  // RUNE_GRAPHICS_RENDERER_FLAGS

/// \} End of configuration macros

class graphics
{
 public:
  using size_type = std::size_t;

  // TODO strong types
  using texture_index = size_type;
  using texture_id = size_type;
  using font_id = size_type;

  template <typename T>
  explicit graphics(const cen::basic_window<T>& window)
      : m_renderer{window, RUNE_GRAPHICS_RENDERER_FLAGS}
      , m_format{window.get_pixel_format()}
  {}

  virtual ~graphics() noexcept = default;

  /// \name Texture loading
  /// \{

  auto load(const texture_id id, const std::string& path) -> texture_index
  {
    if (const auto it = m_indices.find(id); it != m_indices.end())
    {
      return it->second;
    }
    else
    {
      const auto index = m_textures.size();

      m_textures.emplace_back(m_renderer, path);
      m_indices.try_emplace(id, index);

      return index;
    }
  }

  /// \} End of texture loading

  void set_blend_mode(const cen::blend_mode mode)
  {
    m_renderer.set_blend_mode(mode);
  }

  template <typename... Args>
  void emplace_font(const size_type id, Args&&... args)
  {
    m_renderer.emplace_font(id, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void emplace_cache(const font_id id, Args&&... args)
  {
    m_caches.try_emplace(id, std::forward<Args>(args)...);
  }

  [[nodiscard]] auto renderer() noexcept -> cen::renderer&
  {
    return m_renderer;
  }

  [[nodiscard]] auto renderer() const noexcept -> const cen::renderer&
  {
    return m_renderer;
  }

  [[nodiscard]] auto format() const noexcept -> cen::pixel_format
  {
    return m_format;
  }

 private:
  cen::renderer m_renderer;
  cen::pixel_format m_format;
  std::vector<cen::texture> m_textures;
  std::unordered_map<texture_id, texture_index> m_indices;
  std::unordered_map<size_type, cen::font_cache> m_caches;
};

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CORE_GRAPHICS_HPP

// #include "input.hpp"
#ifndef RUNE_CORE_INPUT_HPP
#define RUNE_CORE_INPUT_HPP

#include <centurion.hpp>  // keyboard, mouse

namespace rune {

/// \addtogroup core
/// \{

struct input final
{
  cen::keyboard keyboard;
  cen::mouse mouse;
};

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CORE_INPUT_HPP


namespace rune {

/// \addtogroup core
/// \{

// clang-format off

template <typename T>
concept game_type = requires (T game, const input& input, graphics& graphics, delta_time dt)
{
  { game.handle_input(input) };
  { game.tick(dt) };
  { game.render(graphics) };
  { game.should_quit() } -> std::convertible_to<bool>;
};

template <typename T>
concept has_on_start = requires (T game)
{
  { game.on_start() };
};

template <typename T>
concept has_on_exit = requires (T game)
{
  { game.on_exit() };
};

// clang-format on

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CORE_GAME_HPP
// #include "graphics.hpp"

// #include "input.hpp"

// #include "semi_fixed_game_loop.hpp"
#ifndef RUNE_CORE_SEMI_FIXED_GAME_LOOP_HPP
#define RUNE_CORE_SEMI_FIXED_GAME_LOOP_HPP

#include <algorithm>      // min
#include <centurion.hpp>  // ...
#include <concepts>       // floating_point

// #include "../aliases/delta_time.hpp"

// #include "rune_error.hpp"
#ifndef RUNE_CORE_RUNE_ERROR_HPP
#define RUNE_CORE_RUNE_ERROR_HPP

#include <exception>  // exception

// #include "../aliases/czstring.hpp"


namespace rune {

/// \addtogroup core
/// \{

using czstring = const char*;

/// \} End of group

}  // namespace rune


namespace rune {

/// \addtogroup core
/// \{

class rune_error final : public std::exception
{
 public:
  explicit rune_error(const czstring what) noexcept : m_what{what}
  {}

  [[nodiscard]] auto what() const -> czstring override
  {
    return m_what;
  }

 private:
  czstring m_what{"n/a"};
};

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CORE_RUNE_ERROR_HPP


namespace rune {

/// \addtogroup core
/// \{

/// \name Configuration macros
/// \{

/**
 * \def RUNE_MAX_TICK_RATE
 *
 * \brief The maximum tick rate of the game loop, i.e. the maximum amount of ticks per
 * second.
 *
 * \note The value of this macro should be a `double`.
 *
 * \details The game loop will try to run at the refresh rate of the primary screen, as
 * long as the the refresh rate isn't greater than the value of this macro. By default,
 * this macro expands to `120.0`.
 */
#ifndef RUNE_MAX_TICK_RATE
#define RUNE_MAX_TICK_RATE 120.0
#endif  // RUNE_MAX_TICK_RATE

/**
 * \def RUNE_ENGINE_MAX_FRAMES_PER_TICK
 *
 * \brief The maximum amount of frames that the game loop can run per tick.
 *
 * \note The value of this macro should be an `int`.
 *
 * \details The purpose of this limit is to avoid the "spiral-of-death". By default, this
 * macro expands to `5`.
 */
#ifndef RUNE_ENGINE_MAX_FRAMES_PER_TICK
#define RUNE_ENGINE_MAX_FRAMES_PER_TICK 5
#endif  // RUNE_ENGINE_MAX_FRAMES_PER_TICK

/// \} End of configuration macros

/// \copybrief RUNE_MAX_TICK_RATE
/// \see `RUNE_MAX_TICK_RATE`
inline constexpr double max_tick_rate = RUNE_MAX_TICK_RATE;

/// \copybrief RUNE_ENGINE_MAX_FRAMES_PER_TICK
/// \see `RUNE_ENGINE_MAX_FRAMES_PER_TICK`
inline constexpr int engine_max_frames_per_tick = RUNE_ENGINE_MAX_FRAMES_PER_TICK;

/**
 * \brief Returns the tick rate used by the game loop.
 *
 * \details The tick rate is determined by comparing the refresh rate of the primary
 * screen and the maximum tick rate, and selecting the minimum value.
 *
 * \return the tick rate used by the game loop.
 *
 * \see `max_tick_rate`
 * \see `RUNE_MAX_TICK_RATE`
 */
[[nodiscard]] inline auto tick_rate() -> double
{
  return std::min(static_cast<double>(max_tick_rate),
                  static_cast<double>(cen::screen::refresh_rate().value()));
}

template <game_type Game, std::derived_from<graphics> Graphics>
class engine;

template <game_type Game, std::derived_from<graphics> Graphics>
class semi_fixed_game_loop
{
 public:
  using engine_type = engine<Game, Graphics>;
  using seconds_type = cen::seconds<double>;

  explicit semi_fixed_game_loop(engine_type* engine)
      : m_engine{engine}
      , m_rate{tick_rate()}
      , m_delta{1.0 / m_rate}
      , m_current{cen::counter::now_in_seconds<double>()}
  {
    if (!m_engine)
    {
      throw rune_error{"Cannot create semi_fixed_game_loop from null engine!"};
    }
  }

  void fetch_current_time() noexcept
  {
    m_current = cen::counter::now_in_seconds<double>();
  }

  void tick()
  {
    const auto newTime = cen::counter::now_in_seconds<double>();
    auto frameTime = newTime - m_current;

    m_current = newTime;
    auto nSteps = 0;

    while (frameTime > seconds_type::zero())
    {
      if (nSteps > engine_max_frames_per_tick)
      {
        break;  // avoids spiral-of-death by limiting maximum amount of steps
      }

      m_running = m_engine->update_input();
      if (!m_running)
      {
        break;
      }

      const auto dt = std::min(frameTime, m_delta);
      m_engine->update_logic(static_cast<delta_time>(dt.count()));

      frameTime -= dt;

      ++nSteps;
    }
  }

  [[nodiscard]] auto is_running() const noexcept -> bool
  {
    return m_running;
  }

 private:
  engine_type* m_engine{};
  double m_rate;
  seconds_type m_delta;
  seconds_type m_current;
  bool m_running{true};
};

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CORE_SEMI_FIXED_GAME_LOOP_HPP


namespace rune {

/// \addtogroup core
/// \{

// clang-format off

// clang-format on

template <game_type Game, std::derived_from<graphics> Graphics = graphics>
class engine
{
 public:
  using game_type = Game;
  using graphics_type = Graphics;
  using loop_type = semi_fixed_game_loop<game_type, graphics_type>;

  // clang-format off

  engine()
    : m_loop{this}
    , m_window{"Rune window"}
    , m_graphics{m_window}
  {}

  // clang-format on

  void update_logic(const delta_time dt)
  {
    m_game.tick(dt);
  }

  auto update_input() -> bool
  {
    m_input.mouse.update(m_graphics.renderer().output_size());
    m_input.keyboard.update();

    cen::event::update();

    m_game.handle_input(m_input);

    return !m_game.should_quit() && !cen::event::in_queue(cen::event_type::quit);
  }

  auto run() -> int
  {
    m_window.show();

    m_loop.fetch_current_time();

    if constexpr (has_on_start<Game>)
    {
      m_game.on_start();
    }

    auto& renderer = m_graphics.renderer();
    while (m_loop.is_running())
    {
      m_loop.tick();

      renderer.clear_with(cen::colors::black);
      m_game.render(m_graphics);
      renderer.present();
    }

    if constexpr (has_on_exit<Game>)
    {
      m_game.on_exit();
    }

    m_window.hide();

    return 0;
  }

 private:
  loop_type m_loop;

  cen::window m_window;
  graphics_type m_graphics;
  input m_input;

  game_type m_game;
};

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CORE_ENGINE_HPP

// #include "rune/core/game.hpp"
#ifndef RUNE_CORE_GAME_HPP
#define RUNE_CORE_GAME_HPP

#include <concepts>  // convertible_to

// #include "../aliases/delta_time.hpp"

// #include "graphics.hpp"

// #include "input.hpp"


namespace rune {

/// \addtogroup core
/// \{

// clang-format off

template <typename T>
concept game_type = requires (T game, const input& input, graphics& graphics, delta_time dt)
{
  { game.handle_input(input) };
  { game.tick(dt) };
  { game.render(graphics) };
  { game.should_quit() } -> std::convertible_to<bool>;
};

template <typename T>
concept has_on_start = requires (T game)
{
  { game.on_start() };
};

template <typename T>
concept has_on_exit = requires (T game)
{
  { game.on_exit() };
};

// clang-format on

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CORE_GAME_HPP
// #include "rune/core/rune_error.hpp"
#ifndef RUNE_CORE_RUNE_ERROR_HPP
#define RUNE_CORE_RUNE_ERROR_HPP

#include <exception>  // exception

// #include "../aliases/czstring.hpp"


namespace rune {

/// \addtogroup core
/// \{

class rune_error final : public std::exception
{
 public:
  explicit rune_error(const czstring what) noexcept : m_what{what}
  {}

  [[nodiscard]] auto what() const -> czstring override
  {
    return m_what;
  }

 private:
  czstring m_what{"n/a"};
};

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CORE_RUNE_ERROR_HPP

// #include "rune/core/semi_fixed_game_loop.hpp"
#ifndef RUNE_CORE_SEMI_FIXED_GAME_LOOP_HPP
#define RUNE_CORE_SEMI_FIXED_GAME_LOOP_HPP

#include <algorithm>      // min
#include <centurion.hpp>  // ...
#include <concepts>       // floating_point

// #include "../aliases/delta_time.hpp"

// #include "rune_error.hpp"


namespace rune {

/// \addtogroup core
/// \{

/// \name Configuration macros
/// \{

/**
 * \def RUNE_MAX_TICK_RATE
 *
 * \brief The maximum tick rate of the game loop, i.e. the maximum amount of ticks per
 * second.
 *
 * \note The value of this macro should be a `double`.
 *
 * \details The game loop will try to run at the refresh rate of the primary screen, as
 * long as the the refresh rate isn't greater than the value of this macro. By default,
 * this macro expands to `120.0`.
 */
#ifndef RUNE_MAX_TICK_RATE
#define RUNE_MAX_TICK_RATE 120.0
#endif  // RUNE_MAX_TICK_RATE

/**
 * \def RUNE_ENGINE_MAX_FRAMES_PER_TICK
 *
 * \brief The maximum amount of frames that the game loop can run per tick.
 *
 * \note The value of this macro should be an `int`.
 *
 * \details The purpose of this limit is to avoid the "spiral-of-death". By default, this
 * macro expands to `5`.
 */
#ifndef RUNE_ENGINE_MAX_FRAMES_PER_TICK
#define RUNE_ENGINE_MAX_FRAMES_PER_TICK 5
#endif  // RUNE_ENGINE_MAX_FRAMES_PER_TICK

/// \} End of configuration macros

/// \copybrief RUNE_MAX_TICK_RATE
/// \see `RUNE_MAX_TICK_RATE`
inline constexpr double max_tick_rate = RUNE_MAX_TICK_RATE;

/// \copybrief RUNE_ENGINE_MAX_FRAMES_PER_TICK
/// \see `RUNE_ENGINE_MAX_FRAMES_PER_TICK`
inline constexpr int engine_max_frames_per_tick = RUNE_ENGINE_MAX_FRAMES_PER_TICK;

/**
 * \brief Returns the tick rate used by the game loop.
 *
 * \details The tick rate is determined by comparing the refresh rate of the primary
 * screen and the maximum tick rate, and selecting the minimum value.
 *
 * \return the tick rate used by the game loop.
 *
 * \see `max_tick_rate`
 * \see `RUNE_MAX_TICK_RATE`
 */
[[nodiscard]] inline auto tick_rate() -> double
{
  return std::min(static_cast<double>(max_tick_rate),
                  static_cast<double>(cen::screen::refresh_rate().value()));
}

template <game_type Game, std::derived_from<graphics> Graphics>
class engine;

template <game_type Game, std::derived_from<graphics> Graphics>
class semi_fixed_game_loop
{
 public:
  using engine_type = engine<Game, Graphics>;
  using seconds_type = cen::seconds<double>;

  explicit semi_fixed_game_loop(engine_type* engine)
      : m_engine{engine}
      , m_rate{tick_rate()}
      , m_delta{1.0 / m_rate}
      , m_current{cen::counter::now_in_seconds<double>()}
  {
    if (!m_engine)
    {
      throw rune_error{"Cannot create semi_fixed_game_loop from null engine!"};
    }
  }

  void fetch_current_time() noexcept
  {
    m_current = cen::counter::now_in_seconds<double>();
  }

  void tick()
  {
    const auto newTime = cen::counter::now_in_seconds<double>();
    auto frameTime = newTime - m_current;

    m_current = newTime;
    auto nSteps = 0;

    while (frameTime > seconds_type::zero())
    {
      if (nSteps > engine_max_frames_per_tick)
      {
        break;  // avoids spiral-of-death by limiting maximum amount of steps
      }

      m_running = m_engine->update_input();
      if (!m_running)
      {
        break;
      }

      const auto dt = std::min(frameTime, m_delta);
      m_engine->update_logic(static_cast<delta_time>(dt.count()));

      frameTime -= dt;

      ++nSteps;
    }
  }

  [[nodiscard]] auto is_running() const noexcept -> bool
  {
    return m_running;
  }

 private:
  engine_type* m_engine{};
  double m_rate;
  seconds_type m_delta;
  seconds_type m_current;
  bool m_running{true};
};

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CORE_SEMI_FIXED_GAME_LOOP_HPP

// #include "rune/core/to_string.hpp"
#ifndef RUNE_CORE_TO_STRING_HPP
#define RUNE_CORE_TO_STRING_HPP

#include <array>         // array
#include <charconv>      // to_chars
#include <concepts>      // floating_point
#include <cstddef>       // size_t
#include <optional>      // optional
#include <string>        // string, to_string
#include <system_error>  // errc

// #include "compiler.hpp"
#ifndef RUNE_CORE_COMPILER_HPP
#define RUNE_CORE_COMPILER_HPP

namespace rune {

/// \addtogroup core
/// \{

/// \name Compiler checks
/// \{

/// Indicates whether or not the current compiler is MSVC
[[nodiscard]] constexpr auto on_msvc() noexcept -> bool
{
#ifdef _MSC_VER
  return true;
#else
  return false;
#endif  // _MSC_VER
}

/// Indicates whether or not the current compiler is GCC
[[nodiscard]] constexpr auto on_gcc() noexcept -> bool
{
#ifdef __GNUC__
  return true;
#else
  return false;
#endif  // __GNUC__
}

/// Indicates whether or not the current compiler is Clang
[[nodiscard]] constexpr auto on_clang() noexcept -> bool
{
#ifdef __clang__
  return true;
#else
  return false;
#endif  // __clang__
}

/// \} End of compiler checks

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CORE_COMPILER_HPP

// #include "concepts.hpp"
#ifndef RUNE_CORE_CONCEPTS_HPP
#define RUNE_CORE_CONCEPTS_HPP

#include <type_traits>  // is_arithmetic_v, is_same_v

namespace rune {

/// \addtogroup core
/// \{

/// Concept for a type that is either integral or floating-point, but not `bool`.
template <typename T>
concept numeric = std::is_arithmetic_v<T> && !std::is_same_v<T, bool>;

// clang-format off

template <typename T>
concept has_value_type = requires
{
  typename T::value_type;
};

// clang-format on

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CORE_CONCEPTS_HPP

namespace rune {

/// \addtogroup core
/// \{

/**
 * \brief Returns a string representation of an arithmetic value.
 *
 * \note The default buffer size is guaranteed to work for 64-bit integers and floats.
 *
 * \remark This function just calls `std::to_string()` on GCC, or if the compiler is
 * Clang and the supplied number is floating-point.
 *
 * \tparam BufferSize the size of the stack buffer used, must be big enough to store the
 * characters of the string representation of the value.
 *
 * \tparam T the type of the value that will be converted.
 *
 * \param number the number that will be converted.
 *
 * \return a string representation of the supplied value; `std::nullopt` if something goes
 * wrong.
 */
template <numeric T, std::size_t BufferSize = 24>
[[nodiscard]] auto to_string(const T number) -> std::optional<std::string>
{
  if constexpr (on_gcc() || (on_clang() && std::floating_point<T>))
  {
    return std::to_string(number);
  }
  else
  {
    std::array<char, BufferSize> buffer{};
    const auto [ptr, error] =
        std::to_chars(buffer.data(), buffer.data() + buffer.size(), number);
    if (error == std::errc{})
    {
      return std::string{buffer.data(), ptr};
    }
    else
    {
      return std::nullopt;
    }
  }
}

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CORE_TO_STRING_HPP

// #include "rune/doxygen.hpp"
/// \defgroup core Core
/// \brief Core components of the library.

/// \defgroup tmx TMX
/// \brief Responsible for parsing Tiled JSON map files.

/// \defgroup math Math
/// \brief Contains numeric and mathematical components.

/// \defgroup io IO
/// \brief Filesystem utilities related to JSON, Ini, etc.

// #include "rune/generic/stack_resource.hpp"

// #include "rune/generic/static_vector.hpp"

// #include "rune/generic/vector_map.hpp"

// #include "rune/io/ini.hpp"

// #include "rune/io/json_utils.hpp"
#ifndef RUNE_IO_JSON_UTILS_HPP
#define RUNE_IO_JSON_UTILS_HPP

#include <cassert>      // assert
#include <filesystem>   // path
#include <fstream>      // ifstream
#include <json.hpp>     // json
#include <optional>     // optional
#include <string_view>  // string_view
#include <variant>      // variant

// #include "../core/concepts.hpp"
#ifndef RUNE_CORE_CONCEPTS_HPP
#define RUNE_CORE_CONCEPTS_HPP

#include <type_traits>  // is_arithmetic_v, is_same_v

namespace rune {

/// \addtogroup core
/// \{

/// Concept for a type that is either integral or floating-point, but not `bool`.
template <typename T>
concept numeric = std::is_arithmetic_v<T> && !std::is_same_v<T, bool>;

// clang-format off

template <typename T>
concept has_value_type = requires
{
  typename T::value_type;
};

// clang-format on

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CORE_CONCEPTS_HPP

namespace rune {

/// \addtogroup io
/// \{

/// \name JSON
/// \{

// clang-format off

template <typename T>
concept json_type = requires (const nlohmann::json& json)
{
  { json.get<T>() };
};

// clang-format on

/**
 * \brief Parses the JSON file at the specified path, and returns the contents.
 *
 * \pre `file` must refer to a JSON file.
 *
 * \param file the file path of the JSON file.
 *
 * \return the parsed JSON data.
 */
[[nodiscard]] inline auto read_json(const std::filesystem::path& file) -> nlohmann::json
{
  assert(file.extension() == ".json");
  std::ifstream stream{file};

  nlohmann::json json;
  stream >> json;

  return json;
}

/**
 * \brief Writes the data associated with the specified key to the specified value, as
 * long as the key exists in the JSON object.
 *
 * \details This function requires that values of type `T` can be obtained from JSON
 * objects, i.e. the type needs to provide an overload of the `from_json()` function.
 *
 * \note This function has no effect if there is no element associated with the specified
 * key.
 *
 * \tparam T the deduced the type of the value that might be assigned.
 *
 * \param json the JSON object.
 * \param key the element to look for.
 * \param[out] value a reference to the value that will be assigned with the data
 * associated with `key`, if it exists.
 */
template <json_type T>
void get_if_exists(const nlohmann::json& json, const std::string_view key, T& value)
{
  if (const auto it = json.find(key); it != json.end())
  {
    value = it->get<T>();
  }
}

/// \copydoc get_if_exists()
template <json_type T>
void get_if_exists(const nlohmann::json& json,
                   const std::string_view key,
                   std::optional<T>& value)
{
  if (const auto it = json.find(key); it != json.end())
  {
    value = it->get<T>();
  }
}

template <has_value_type T>
void emplace(const nlohmann::json& json, const std::string_view key, T& value)
{
  static_assert(json_type<typename T::value_type>);

  const auto it = json.find(key);
  assert(it != json.end());

  value = T{it->get<typename T::value_type>()};
}

template <has_value_type T>
void emplace(const nlohmann::json& json,
             const std::string_view key,
             std::optional<T>& value)
{
  static_assert(json_type<typename T::value_type>);

  const auto it = json.find(key);
  assert(it != json.end());

  value = T{it->get<typename T::value_type>()};
}

template <has_value_type T>
void emplace_if_exists(const nlohmann::json& json, const std::string_view key, T& value)
{
  static_assert(json_type<typename T::value_type>);

  if (const auto it = json.find(key); it != json.end())
  {
    value = T{it->get<typename T::value_type>()};
  }
}

template <has_value_type T>
void emplace_if_exists(const nlohmann::json& json,
                       const std::string_view key,
                       std::optional<T>& value)
{
  static_assert(json_type<typename T::value_type>);

  if (const auto it = json.find(key); it != json.end())
  {
    value.emplace(it->get<typename T::value_type>());
  }
}

/**
 * \brief Writes the data associated with the specified key to the specified variant, as
 * long as the key exists in the JSON object.
 *
 * \details This function requires that values of type `T` can be obtained from JSON
 * objects, i.e. the type needs to provide an overload of the `from_json()` function.
 *
 * \note This function has no effect if there is no element associated with the specified
 * key.
 *
 * \tparam T the type of the data that will be extracted from the JSON object.
 * \tparam Types the types used by the variant.
 *
 * \param json the JSON object.
 * \param key the element to look for.
 * \param[out] variant the variant that the data will be written to.
 */
template <json_type T, typename... Types>
void emplace_if_exists(const nlohmann::json& json,
                       const std::string_view key,
                       std::variant<Types...>& variant)
{
  if (const auto it = json.find(key); it != json.end())
  {
    variant.template emplace<T>(it->get<T>());
  }
}

/**
 * \brief Fills a container with values from a JSON array.
 *
 * \details This function requires that values of type `Container::value_type` can be
 * obtained from JSON objects, i.e. the type needs to provide an overload of the
 * `from_json()` function.
 *
 * \pre `array` must represent a JSON array.
 *
 * \tparam Container the container type, e.g. `std::vector` or `std::array`.
 *
 * \param array the JSON array that provides the source data.
 * \param[out] container the container that will be filled.
 */
template <has_value_type Container>
void fill(const nlohmann::json& array, Container& container)
{
  static_assert(json_type<typename Container::value_type>);
  assert(array.is_array());

  container.reserve(array.size());
  for (const auto& [key, value] : array.items())
  {
    container.push_back(value.template get<typename Container::value_type>());
  }
}

/**
 * \brief Fills a container with values from a JSON array.
 *
 * \details This function requires that values of type `Container::value_type` can be
 * obtained from JSON objects, i.e. the type needs to provide an overload of the
 * `from_json()` function.
 *
 * \pre `json` must contain the specified key.
 * \pre The JSON element associated with the specified key must be an array.
 *
 * \tparam Container the container type, e.g. `std::vector` or `std::array`.
 *
 * \param json the JSON object that contains an array associated with the specified key.
 * \param key the key of the JSON array element.
 * \param[out] container the container that will be filled.
 */
template <has_value_type Container>
void fill(const nlohmann::json& json, const std::string_view key, Container& container)
{
  static_assert(json_type<typename Container::value_type>);

  const auto it = json.find(key);
  assert(it != json.end());
  assert(it->is_array());

  container.reserve(it->size());
  for (const auto& [key, value] : it->items())
  {
    container.push_back(value.template get<typename Container::value_type>());
  }
}

/**
 * \brief Fills a container with values from a JSON array, if it exists.
 *
 * \details This function requires that values of type `Container::value_type` can be
 * obtained from JSON objects, i.e. the type needs to provide an overload of the
 * `from_json()` function.
 *
 * \note This function has no effect if there is no element associated with the specified
 * key.
 *
 * \pre The JSON element associated with the specified key must be an array.
 *
 * \tparam Container the container type, e.g. `std::vector` or `std::array`.
 *
 * \param json the JSON object that contains an array associated with the specified key.
 * \param key the key of the JSON array element.
 * \param[out] container the container that will be filled.
 */
template <has_value_type Container>
void fill_if_exists(const nlohmann::json& json,
                    const std::string_view key,
                    Container& container)
{
  static_assert(json_type<typename Container::value_type>);

  if (const auto it = json.find(key); it != json.end())
  {
    assert(it->is_array());
    container.reserve(it->size());
    for (const auto& [key, value] : it->items())
    {
      container.push_back(value.template get<typename Container::value_type>());
    }
  }
}

/// \} End of JSON

/// \} End of group io

}  // namespace rune

#endif  // RUNE_IO_JSON_UTILS_HPP

// #include "rune/math/almost_equal.hpp"
#ifndef RUNE_MATH_ALMOST_EQUAL_HPP
#define RUNE_MATH_ALMOST_EQUAL_HPP

#include <cmath>     // abs
#include <concepts>  // floating_point

namespace rune {

/// \addtogroup math
/// \{

// clang-format off

/// The default epsilon value used for floating point comparisons.
inline constexpr double default_epsilon = 0.00001;

/**
 * \brief Indicates whether or not two floating-point values are almost equal.
 *
 * \details The two values are considered equal if the absolute value of their difference
 * is in the range [0, `epsilon`).
 *
 * \param a the first value.
 * \param b the second value.
 * \param epsilon the epsilon value.
 *
 * \return `true` if the values are almost equal; `false` otherwise.
 */
template <std::floating_point T>
[[nodiscard]] auto almost_equal(const T a,
                                const T b,
                                const T epsilon = default_epsilon) noexcept(noexcept(std::abs(a)))
    -> bool
{
  return std::abs(a - b) < epsilon;
}

// clang-format on

/// \} End of group math

}  // namespace rune

#endif  // RUNE_MATH_ALMOST_EQUAL_HPP

// #include "rune/math/vector2.hpp"
#ifndef RUNE_MATH_VECTOR2_HPP
#define RUNE_MATH_VECTOR2_HPP

#include <cmath>     // lerp, sqrt
#include <concepts>  // floating_point
#include <ostream>   // ostream
#include <string>    // string

// #include "../core/to_string.hpp"
#ifndef RUNE_CORE_TO_STRING_HPP
#define RUNE_CORE_TO_STRING_HPP

#include <array>         // array
#include <charconv>      // to_chars
#include <concepts>      // floating_point
#include <cstddef>       // size_t
#include <optional>      // optional
#include <string>        // string, to_string
#include <system_error>  // errc

// #include "compiler.hpp"
#ifndef RUNE_CORE_COMPILER_HPP
#define RUNE_CORE_COMPILER_HPP

namespace rune {

/// \addtogroup core
/// \{

/// \name Compiler checks
/// \{

/// Indicates whether or not the current compiler is MSVC
[[nodiscard]] constexpr auto on_msvc() noexcept -> bool
{
#ifdef _MSC_VER
  return true;
#else
  return false;
#endif  // _MSC_VER
}

/// Indicates whether or not the current compiler is GCC
[[nodiscard]] constexpr auto on_gcc() noexcept -> bool
{
#ifdef __GNUC__
  return true;
#else
  return false;
#endif  // __GNUC__
}

/// Indicates whether or not the current compiler is Clang
[[nodiscard]] constexpr auto on_clang() noexcept -> bool
{
#ifdef __clang__
  return true;
#else
  return false;
#endif  // __clang__
}

/// \} End of compiler checks

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CORE_COMPILER_HPP

// #include "concepts.hpp"
#ifndef RUNE_CORE_CONCEPTS_HPP
#define RUNE_CORE_CONCEPTS_HPP

#include <type_traits>  // is_arithmetic_v, is_same_v

namespace rune {

/// \addtogroup core
/// \{

/// Concept for a type that is either integral or floating-point, but not `bool`.
template <typename T>
concept numeric = std::is_arithmetic_v<T> && !std::is_same_v<T, bool>;

// clang-format off

template <typename T>
concept has_value_type = requires
{
  typename T::value_type;
};

// clang-format on

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CORE_CONCEPTS_HPP

namespace rune {

/// \addtogroup core
/// \{

/**
 * \brief Returns a string representation of an arithmetic value.
 *
 * \note The default buffer size is guaranteed to work for 64-bit integers and floats.
 *
 * \remark This function just calls `std::to_string()` on GCC, or if the compiler is
 * Clang and the supplied number is floating-point.
 *
 * \tparam BufferSize the size of the stack buffer used, must be big enough to store the
 * characters of the string representation of the value.
 *
 * \tparam T the type of the value that will be converted.
 *
 * \param number the number that will be converted.
 *
 * \return a string representation of the supplied value; `std::nullopt` if something goes
 * wrong.
 */
template <numeric T, std::size_t BufferSize = 24>
[[nodiscard]] auto to_string(const T number) -> std::optional<std::string>
{
  if constexpr (on_gcc() || (on_clang() && std::floating_point<T>))
  {
    return std::to_string(number);
  }
  else
  {
    std::array<char, BufferSize> buffer{};
    const auto [ptr, error] =
        std::to_chars(buffer.data(), buffer.data() + buffer.size(), number);
    if (error == std::errc{})
    {
      return std::string{buffer.data(), ptr};
    }
    else
    {
      return std::nullopt;
    }
  }
}

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CORE_TO_STRING_HPP

// #include "almost_equal.hpp"
#ifndef RUNE_MATH_ALMOST_EQUAL_HPP
#define RUNE_MATH_ALMOST_EQUAL_HPP

#include <cmath>     // abs
#include <concepts>  // floating_point

namespace rune {

/// \addtogroup math
/// \{

// clang-format off

/// The default epsilon value used for floating point comparisons.
inline constexpr double default_epsilon = 0.00001;

/**
 * \brief Indicates whether or not two floating-point values are almost equal.
 *
 * \details The two values are considered equal if the absolute value of their difference
 * is in the range [0, `epsilon`).
 *
 * \param a the first value.
 * \param b the second value.
 * \param epsilon the epsilon value.
 *
 * \return `true` if the values are almost equal; `false` otherwise.
 */
template <std::floating_point T>
[[nodiscard]] auto almost_equal(const T a,
                                const T b,
                                const T epsilon = default_epsilon) noexcept(noexcept(std::abs(a)))
    -> bool
{
  return std::abs(a - b) < epsilon;
}

// clang-format on

/// \} End of group math

}  // namespace rune

#endif  // RUNE_MATH_ALMOST_EQUAL_HPP


namespace rune {

/// \addtogroup math
/// \{

template <std::floating_point T>
class basic_vector2 final
{
 public:
  using value_type = T;
  using vector_type = basic_vector2;

  value_type x{};  ///< The x-coordinate.
  value_type y{};  ///< The y-coordinate.

  /// \name Construction
  /// \{

  /// Creates a zero vector.
  constexpr basic_vector2() noexcept = default;

  /**
   * \brief Creates a vector with the specified components.
   *
   * \param x the x-coordinate of the vector.
   * \param y the y-coordinate of the vector.
   */
  constexpr basic_vector2(const value_type x, const value_type y) noexcept : x{x}, y{y}
  {}

  /// \} End of construction

  /// \name Mutators
  /// \{

  /// Turns the vector into the zero vector.
  constexpr void reset() noexcept
  {
    x = 0;
    y = 0;
  }

  /**
   * \brief Negates the coordinates of the vector.
   *
   * \details Negating a vector with components (20, 30) results in (-20, -30).
   */
  constexpr void negate() noexcept
  {
    x = -x;
    y = -y;
  }

  /**
   * \brief Normalizes the vector, i.e. the vector will be made a unit vector.
   *
   * \note If the vector is the zero vector, then this function has no effect.
   */
  constexpr void normalize()
  {
    const auto currentMagnitude = magnitude();
    if (currentMagnitude != 0) [[likely]]
    {
      x /= currentMagnitude;
      y /= currentMagnitude;
    }
  }

  /**
   * \brief Scales the coordinates of the vector by the specified factor.
   *
   * \param factor the scale factor, may be negative.
   */
  constexpr void scale(const value_type factor) noexcept
  {
    x *= factor;
    y *= factor;
  }

  /**
   * \brief Linearly interpolates the vector with the supplied target vector.
   *
   * \param target the target vector of the interpolation.
   * \param alpha the interpolation alpha, in the interval [0, 1].
   */
  constexpr void lerp(const vector_type target, const value_type alpha) noexcept
  {
    x = std::lerp(x, target.x, alpha);
    y = std::lerp(y, target.y, alpha);
  }

  /**
   * \brief Makes the vector "look" at the supplied point.
   *
   * \note A negative length value will turn the vector into the zero vector.
   *
   * \param target the point that the vector will look at.
   * \param length the length of the vector after the operation.
   *
   * \since 0.1.0
   */
  constexpr void look_at(const vector_type target, const value_type length)
  {
    if (length >= 0) [[likely]]
    {
      x = target.x - x;
      y = target.y - y;
      normalize();
      scale(length);
    }
    else
    {
      reset();
    }
  }

  /**
   * \brief Makes the vector "look" at the supplied point.
   *
   * \note The vector will maintain its current magnitude.
   *
   * \param target the point that the vector will look at.
   */
  constexpr void look_at(const vector_type target)
  {
    look_at(target, magnitude());
  }

  /// \} End of mutators

  /// \name Queries
  /// \{

  /// Returns the magnitude, i.e. length, of the vector.
  [[nodiscard]] auto magnitude() const -> value_type
  {
    return std::sqrt((x * x) + (y * y));
  }

  /// Returns the squared magnitude of the vector.
  [[nodiscard]] constexpr auto magnitude2() const noexcept -> value_type
  {
    return (x * x) + (y * y);
  }

  /// Indicates whether or not the vector is a unit vector.
  [[nodiscard]] auto is_unit() const -> bool
  {
    return almost_equal(magnitude(), value_type{1});
  }

  /// Indicates whether or not the vector is the zero vector.
  [[nodiscard]] auto is_zero() const -> bool
  {
    return almost_equal(x, value_type{0}) && almost_equal(y, value_type{0});
  }

  /// \} End of queries

  /// \name Serialization
  /// \{

  /// Serializes the vector.
  void serialize(auto& archive)
  {
    archive(x, y);
  }

  /// \} End of serialization

  /// \name Comparisons
  /// \{

  /// Indicates whether or not two vectors are exactly equal.
  [[nodiscard]] constexpr bool operator==(const vector_type&) const noexcept = default;

  /// \} End of comparisons
};

/// A two-dimensional vector using `float` precision.
using float2 = basic_vector2<float>;

/// A two-dimensional vector using `double` precision.
using double2 = basic_vector2<double>;

/// Indicates whether or not two vectors are almost equal.
template <std::floating_point T>
[[nodiscard]] auto almost_equal(const basic_vector2<T>& a,
                                const basic_vector2<T>& b,
                                const T epsilon = default_epsilon) -> bool
{
  return almost_equal(a.x, b.x, epsilon) && almost_equal(a.y, b.y, epsilon);
}

/// \name Vector operators
/// \{

template <std::floating_point T>
constexpr void operator+=(basic_vector2<T>& a, const basic_vector2<T>& b) noexcept
{
  a.x += b.x;
  a.y += b.y;
}

template <std::floating_point T>
constexpr void operator-=(basic_vector2<T>& a, const basic_vector2<T>& b) noexcept
{
  a.x -= b.x;
  a.y -= b.y;
}

template <std::floating_point T>
constexpr void operator*=(basic_vector2<T>& vector, const T factor) noexcept
{
  vector.scale(factor);
}

template <std::floating_point T>
[[nodiscard]] constexpr auto operator+(const basic_vector2<T>& lhs,
                                       const basic_vector2<T>& rhs) noexcept
    -> basic_vector2<T>
{
  return basic_vector2{lhs.x + rhs.x, lhs.y + rhs.y};
}

template <std::floating_point T>
[[nodiscard]] constexpr auto operator-(const basic_vector2<T>& lhs,
                                       const basic_vector2<T>& rhs) noexcept
    -> basic_vector2<T>
{
  return basic_vector2{lhs.x - rhs.x, lhs.y - rhs.y};
}

/// \} End of vector operators

template <std::floating_point T>
[[nodiscard]] auto to_string(const basic_vector2<T> vec) -> std::string
{
  return "vector2{x: " + to_string(vec.x).value() + ", y: " + to_string(vec.y).value() +
         "}";
}

template <std::floating_point T>
auto operator<<(std::ostream& stream, const basic_vector2<T> vec) -> std::ostream&
{
  return stream << to_string(vec);
}

/// \} End of group math

}  // namespace rune

#endif  // RUNE_MATH_VECTOR2_HPP

// #include "rune/tmx/parse_tileset.hpp"
#ifndef RUNE_TMX_PARSE_TILESET_HPP
#define RUNE_TMX_PARSE_TILESET_HPP

#include <filesystem>  // path
#include <json.hpp>    // json
#include <string>      // string

// #include "../io/json_utils.hpp"
#ifndef RUNE_IO_JSON_UTILS_HPP
#define RUNE_IO_JSON_UTILS_HPP

#include <cassert>      // assert
#include <filesystem>   // path
#include <fstream>      // ifstream
#include <json.hpp>     // json
#include <optional>     // optional
#include <string_view>  // string_view
#include <variant>      // variant

// #include "../core/concepts.hpp"
#ifndef RUNE_CORE_CONCEPTS_HPP
#define RUNE_CORE_CONCEPTS_HPP

#include <type_traits>  // is_arithmetic_v, is_same_v

namespace rune {

/// \addtogroup core
/// \{

/// Concept for a type that is either integral or floating-point, but not `bool`.
template <typename T>
concept numeric = std::is_arithmetic_v<T> && !std::is_same_v<T, bool>;

// clang-format off

template <typename T>
concept has_value_type = requires
{
  typename T::value_type;
};

// clang-format on

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CORE_CONCEPTS_HPP

namespace rune {

/// \addtogroup io
/// \{

/// \name JSON
/// \{

// clang-format off

template <typename T>
concept json_type = requires (const nlohmann::json& json)
{
  { json.get<T>() };
};

// clang-format on

/**
 * \brief Parses the JSON file at the specified path, and returns the contents.
 *
 * \pre `file` must refer to a JSON file.
 *
 * \param file the file path of the JSON file.
 *
 * \return the parsed JSON data.
 */
[[nodiscard]] inline auto read_json(const std::filesystem::path& file) -> nlohmann::json
{
  assert(file.extension() == ".json");
  std::ifstream stream{file};

  nlohmann::json json;
  stream >> json;

  return json;
}

/**
 * \brief Writes the data associated with the specified key to the specified value, as
 * long as the key exists in the JSON object.
 *
 * \details This function requires that values of type `T` can be obtained from JSON
 * objects, i.e. the type needs to provide an overload of the `from_json()` function.
 *
 * \note This function has no effect if there is no element associated with the specified
 * key.
 *
 * \tparam T the deduced the type of the value that might be assigned.
 *
 * \param json the JSON object.
 * \param key the element to look for.
 * \param[out] value a reference to the value that will be assigned with the data
 * associated with `key`, if it exists.
 */
template <json_type T>
void get_if_exists(const nlohmann::json& json, const std::string_view key, T& value)
{
  if (const auto it = json.find(key); it != json.end())
  {
    value = it->get<T>();
  }
}

/// \copydoc get_if_exists()
template <json_type T>
void get_if_exists(const nlohmann::json& json,
                   const std::string_view key,
                   std::optional<T>& value)
{
  if (const auto it = json.find(key); it != json.end())
  {
    value = it->get<T>();
  }
}

template <has_value_type T>
void emplace(const nlohmann::json& json, const std::string_view key, T& value)
{
  static_assert(json_type<typename T::value_type>);

  const auto it = json.find(key);
  assert(it != json.end());

  value = T{it->get<typename T::value_type>()};
}

template <has_value_type T>
void emplace(const nlohmann::json& json,
             const std::string_view key,
             std::optional<T>& value)
{
  static_assert(json_type<typename T::value_type>);

  const auto it = json.find(key);
  assert(it != json.end());

  value = T{it->get<typename T::value_type>()};
}

template <has_value_type T>
void emplace_if_exists(const nlohmann::json& json, const std::string_view key, T& value)
{
  static_assert(json_type<typename T::value_type>);

  if (const auto it = json.find(key); it != json.end())
  {
    value = T{it->get<typename T::value_type>()};
  }
}

template <has_value_type T>
void emplace_if_exists(const nlohmann::json& json,
                       const std::string_view key,
                       std::optional<T>& value)
{
  static_assert(json_type<typename T::value_type>);

  if (const auto it = json.find(key); it != json.end())
  {
    value.emplace(it->get<typename T::value_type>());
  }
}

/**
 * \brief Writes the data associated with the specified key to the specified variant, as
 * long as the key exists in the JSON object.
 *
 * \details This function requires that values of type `T` can be obtained from JSON
 * objects, i.e. the type needs to provide an overload of the `from_json()` function.
 *
 * \note This function has no effect if there is no element associated with the specified
 * key.
 *
 * \tparam T the type of the data that will be extracted from the JSON object.
 * \tparam Types the types used by the variant.
 *
 * \param json the JSON object.
 * \param key the element to look for.
 * \param[out] variant the variant that the data will be written to.
 */
template <json_type T, typename... Types>
void emplace_if_exists(const nlohmann::json& json,
                       const std::string_view key,
                       std::variant<Types...>& variant)
{
  if (const auto it = json.find(key); it != json.end())
  {
    variant.template emplace<T>(it->get<T>());
  }
}

/**
 * \brief Fills a container with values from a JSON array.
 *
 * \details This function requires that values of type `Container::value_type` can be
 * obtained from JSON objects, i.e. the type needs to provide an overload of the
 * `from_json()` function.
 *
 * \pre `array` must represent a JSON array.
 *
 * \tparam Container the container type, e.g. `std::vector` or `std::array`.
 *
 * \param array the JSON array that provides the source data.
 * \param[out] container the container that will be filled.
 */
template <has_value_type Container>
void fill(const nlohmann::json& array, Container& container)
{
  static_assert(json_type<typename Container::value_type>);
  assert(array.is_array());

  container.reserve(array.size());
  for (const auto& [key, value] : array.items())
  {
    container.push_back(value.template get<typename Container::value_type>());
  }
}

/**
 * \brief Fills a container with values from a JSON array.
 *
 * \details This function requires that values of type `Container::value_type` can be
 * obtained from JSON objects, i.e. the type needs to provide an overload of the
 * `from_json()` function.
 *
 * \pre `json` must contain the specified key.
 * \pre The JSON element associated with the specified key must be an array.
 *
 * \tparam Container the container type, e.g. `std::vector` or `std::array`.
 *
 * \param json the JSON object that contains an array associated with the specified key.
 * \param key the key of the JSON array element.
 * \param[out] container the container that will be filled.
 */
template <has_value_type Container>
void fill(const nlohmann::json& json, const std::string_view key, Container& container)
{
  static_assert(json_type<typename Container::value_type>);

  const auto it = json.find(key);
  assert(it != json.end());
  assert(it->is_array());

  container.reserve(it->size());
  for (const auto& [key, value] : it->items())
  {
    container.push_back(value.template get<typename Container::value_type>());
  }
}

/**
 * \brief Fills a container with values from a JSON array, if it exists.
 *
 * \details This function requires that values of type `Container::value_type` can be
 * obtained from JSON objects, i.e. the type needs to provide an overload of the
 * `from_json()` function.
 *
 * \note This function has no effect if there is no element associated with the specified
 * key.
 *
 * \pre The JSON element associated with the specified key must be an array.
 *
 * \tparam Container the container type, e.g. `std::vector` or `std::array`.
 *
 * \param json the JSON object that contains an array associated with the specified key.
 * \param key the key of the JSON array element.
 * \param[out] container the container that will be filled.
 */
template <has_value_type Container>
void fill_if_exists(const nlohmann::json& json,
                    const std::string_view key,
                    Container& container)
{
  static_assert(json_type<typename Container::value_type>);

  if (const auto it = json.find(key); it != json.end())
  {
    assert(it->is_array());
    container.reserve(it->size());
    for (const auto& [key, value] : it->items())
    {
      container.push_back(value.template get<typename Container::value_type>());
    }
  }
}

/// \} End of JSON

/// \} End of group io

}  // namespace rune

#endif  // RUNE_IO_JSON_UTILS_HPP

// #include "tmx_global_id.hpp"
#ifndef RUNE_TMX_GLOBAL_ID_HPP
#define RUNE_TMX_GLOBAL_ID_HPP

#include <nenya.hpp>  // strong_type

// #include "../aliases/integers.hpp"
#ifndef RUNE_ALIASES_INTEGERS_HPP
#define RUNE_ALIASES_INTEGERS_HPP

#include <centurion.hpp>  // ...

namespace rune {

/// \addtogroup core
/// \{

/// Unsigned integer.
using uint = cen::uint;

/// Used as the argument type to integral literal operators.
using ulonglong = cen::ulonglong;

/// 8-bit signed integer.
using int8 = cen::i8;

/// 16-bit signed integer.
using int16 = cen::i16;

/// 32-bit signed integer.
using int32 = cen::i32;

/// 64-bit signed integer.
using int64 = cen::i64;

/// 8-bit unsigned integer.
using uint8 = cen::u8;

/// 16-bit unsigned integer.
using uint16 = cen::u16;

/// 32-bit unsigned integer.
using uint32 = cen::u32;

/// 64-bit unsigned integer.
using uint64 = cen::u64;

/// \} End of group core

}  // namespace rune

#endif  // RUNE_ALIASES_INTEGERS_HPP


namespace rune {

/// \cond FALSE
namespace tags {
struct tmx_global_id_tag;
}
/// \endcond

/// \addtogroup tmx
/// \{

using tmx_global_id = nenya::strong_type<uint, tags::tmx_global_id_tag>;

/// \} End of group tmx

namespace tmx_literals {

/// \addtogroup tmx
/// \{

/// \name Literal operators
/// \{

[[nodiscard]] constexpr auto operator""_global(const ulonglong value) noexcept
    -> tmx_global_id
{
  return tmx_global_id{static_cast<tmx_global_id::value_type>(value)};
}

/// \} End of literal operators
/// \} End of group tmx

}  // namespace tmx_literals
}  // namespace rune

#endif  // RUNE_TMX_GLOBAL_ID_HPP

// #include "tmx_tileset.hpp"
#ifndef RUNE_TMX_TILESET_HPP
#define RUNE_TMX_TILESET_HPP

#include <json.hpp>  // json
#include <optional>  // optional
#include <string>    // string
#include <vector>    // vector

// #include "tmx_color.hpp"
#ifndef RUNE_TMX_COLOR_HPP
#define RUNE_TMX_COLOR_HPP

#include <cassert>       // assert
#include <charconv>      // from_chars
#include <json.hpp>      // json
#include <string_view>   // string_view
#include <system_error>  // errc

// #include "../aliases/integers.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_color final
{
  uint8 red{};
  uint8 green{};
  uint8 blue{};
  uint8 alpha{0xFF};

  [[nodiscard]] constexpr bool operator==(const tmx_color&) const noexcept = default;
};

void from_json(const nlohmann::json& json, tmx_color& color);

/// \} End of group tmx

namespace tmx {

/// \addtogroup tmx
/// \{

inline constexpr tmx_color black{0, 0, 0, 0xFF};

[[nodiscard]] inline auto from_hex(const std::string_view str) -> uint8
{
  assert(str.size() == 2);

  uint8 value{};
  const auto [ptr, error] =
      std::from_chars(str.data(), str.data() + str.size(), value, 16);
  assert(error != std::errc::invalid_argument);
  assert(error != std::errc::result_out_of_range);

  return value;
}

[[nodiscard]] inline auto make_color(const std::string_view str) -> tmx_color
{
  assert(str.size() == 7 || str.size() == 9);
  assert(str.at(0) == '#');

  const auto noHash = str.substr(1);
  const auto length = noHash.size();

  tmx_color result;

  if (length == 8)
  {
    // ARGB
    result.alpha = from_hex(noHash.substr(0, 2));
    result.red = from_hex(noHash.substr(2, 2));
    result.green = from_hex(noHash.substr(4, 2));
    result.blue = from_hex(noHash.substr(6, 2));
  }
  else
  {
    // RGB
    result.red = from_hex(noHash.substr(0, 2));
    result.green = from_hex(noHash.substr(2, 2));
    result.blue = from_hex(noHash.substr(4, 2));
  }

  return result;
}

/// \} End of group tmx

}  // namespace tmx
}  // namespace rune

#endif  // RUNE_TMX_COLOR_TEST

// #include "tmx_global_id.hpp"

// #include "tmx_grid.hpp"
#ifndef RUNE_TMX_GRID_HPP
#define RUNE_TMX_GRID_HPP

#include <json.hpp>  // json, NLOHMANN_JSON_SERIALIZE_ENUM

namespace rune {

/// \addtogroup tmx
/// \{

enum class tmx_grid_orientation
{
  orthogonal,
  isometric
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_grid_orientation,
                             {{tmx_grid_orientation::orthogonal, "orthogonal"},
                              {tmx_grid_orientation::isometric, "isometric"}})

struct tmx_grid final
{
  int cell_width{};
  int cell_height{};
  tmx_grid_orientation orientation{tmx_grid_orientation::orthogonal};
};

void from_json(const nlohmann::json& json, tmx_grid& grid);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_GRID_HPP

// #include "tmx_property.hpp"
#ifndef RUNE_TMX_PROPERTY_HPP
#define RUNE_TMX_PROPERTY_HPP

#include <cassert>      // assert
#include <concepts>     // same_as
#include <json.hpp>     // json
#include <nenya.hpp>    // strong_type
#include <ranges>       // any_of, find_if
#include <string>       // string
#include <string_view>  // string_view
#include <variant>      // variant, get, get_if, holds_alternative
#include <vector>       // vector

// #include "../core/rune_error.hpp"
#ifndef RUNE_CORE_RUNE_ERROR_HPP
#define RUNE_CORE_RUNE_ERROR_HPP

#include <exception>  // exception

// #include "../aliases/czstring.hpp"


namespace rune {

/// \addtogroup core
/// \{

using czstring = const char*;

/// \} End of group

}  // namespace rune


namespace rune {

/// \addtogroup core
/// \{

class rune_error final : public std::exception
{
 public:
  explicit rune_error(const czstring what) noexcept : m_what{what}
  {}

  [[nodiscard]] auto what() const -> czstring override
  {
    return m_what;
  }

 private:
  czstring m_what{"n/a"};
};

/// \} End of group core

}  // namespace rune

#endif  // RUNE_CORE_RUNE_ERROR_HPP

// #include "tmx_color.hpp"


namespace rune {

/// \cond FALSE
namespace tags {
struct tmx_file_tag;
struct tmx_object_tag;
}  // namespace tags
/// \endcond

/// \addtogroup tmx
/// \{

using tmx_file = nenya::strong_type<std::string, tags::tmx_file_tag>;
using tmx_object_id = nenya::strong_type<int, tags::tmx_object_tag>;

enum class tmx_property_type
{
  string,    ///< For string values, such as `"foo"`.
  integer,   ///< For integer values, e.g. `27`.
  floating,  ///< For floating-point values, e.g. `182.4`.
  boolean,   ///< For the boolean values `true`/`false`.
  color,     ///< For ARGB/RGB colors, i.e. `"#AARRGGBB"` and `"#RRGGBB"`.
  file,      ///< For file paths, e.g. `"some/path/abc.png"`.
  object     ///< For referencing other objects, really just an integer ID.
};

/**
 * \brief Represents a property, with an associated name and value.
 */
struct tmx_property final
{
  using data_type =
      std::variant<std::string, tmx_file, tmx_object_id, tmx_color, int, float, bool>;

  std::string name;
  tmx_property_type type{tmx_property_type::string};
  data_type value;
};

using tmx_properties = std::vector<tmx_property>;

void from_json(const nlohmann::json& json, tmx_property& property);

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_property_type,
                             {{tmx_property_type::string, "string"},
                              {tmx_property_type::integer, "int"},
                              {tmx_property_type::floating, "float"},
                              {tmx_property_type::boolean, "bool"},
                              {tmx_property_type::color, "color"},
                              {tmx_property_type::object, "object"},
                              {tmx_property_type::file, "file"}})

/// \} End of group tmx

namespace tmx {

/// \addtogroup tmx
/// \{

/// \name Non-throwing property value casts
/// \brief Property cast functions that return null pointers upon type mismatches.
/// \{

[[nodiscard]] inline auto try_get(const tmx_properties& properties,
                                  const std::string_view name)
    -> tmx_properties::const_iterator
{
  return std::ranges::find_if(properties, [name](const tmx_property& property) noexcept {
    return property.name == name;
  });
}

[[nodiscard]] inline auto try_get_string(const tmx_property& property) noexcept
    -> const std::string*
{
  return std::get_if<std::string>(&property.value);
}

[[nodiscard]] inline auto try_get_string(const tmx_properties& properties,
                                         const std::string_view name)
    -> const std::string*
{
  if (const auto it = try_get(properties, name); it != properties.end())
  {
    return std::get_if<std::string>(&it->value);
  }
  else
  {
    return nullptr;
  }
}

[[nodiscard]] inline auto try_get_int(const tmx_property& property) noexcept -> const int*
{
  return std::get_if<int>(&property.value);
}

[[nodiscard]] inline auto try_get_int(const tmx_properties& properties,
                                      const std::string_view name) -> const int*
{
  if (const auto it = try_get(properties, name); it != properties.end())
  {
    return std::get_if<int>(&it->value);
  }
  else
  {
    return nullptr;
  }
}

[[nodiscard]] inline auto try_get_float(const tmx_property& property) noexcept -> const
    float*
{
  return std::get_if<float>(&property.value);
}

[[nodiscard]] inline auto try_get_float(const tmx_properties& properties,
                                        const std::string_view name) -> const float*
{
  if (const auto it = try_get(properties, name); it != properties.end())
  {
    return std::get_if<float>(&it->value);
  }
  else
  {
    return nullptr;
  }
}

[[nodiscard]] inline auto try_get_bool(const tmx_property& property) noexcept -> const
    bool*
{
  return std::get_if<bool>(&property.value);
}

[[nodiscard]] inline auto try_get_bool(const tmx_properties& properties,
                                       const std::string_view name) -> const bool*
{
  if (const auto it = try_get(properties, name); it != properties.end())
  {
    return std::get_if<bool>(&it->value);
  }
  else
  {
    return nullptr;
  }
}

[[nodiscard]] inline auto try_get_color(const tmx_property& property) noexcept
    -> const tmx_color*
{
  return std::get_if<tmx_color>(&property.value);
}

[[nodiscard]] inline auto try_get_color(const tmx_properties& properties,
                                        const std::string_view name) -> const tmx_color*
{
  if (const auto it = try_get(properties, name); it != properties.end())
  {
    return std::get_if<tmx_color>(&it->value);
  }
  else
  {
    return nullptr;
  }
}

[[nodiscard]] inline auto try_get_file(const tmx_property& property) noexcept
    -> const tmx_file*
{
  return std::get_if<tmx_file>(&property.value);
}

[[nodiscard]] inline auto try_get_file(const tmx_properties& properties,
                                       const std::string_view name) -> const tmx_file*
{
  if (const auto it = try_get(properties, name); it != properties.end())
  {
    return std::get_if<tmx_file>(&it->value);
  }
  else
  {
    return nullptr;
  }
}

[[nodiscard]] inline auto try_get_object(const tmx_property& property) noexcept
    -> const tmx_object_id*
{
  return std::get_if<tmx_object_id>(&property.value);
}

[[nodiscard]] inline auto try_get_object(const tmx_properties& properties,
                                         const std::string_view name)
    -> const tmx_object_id*
{
  if (const auto it = try_get(properties, name); it != properties.end())
  {
    return std::get_if<tmx_object_id>(&it->value);
  }
  else
  {
    return nullptr;
  }
}

/// \} End of non-throwing property value casts

/// \name Property type indicators
/// \{

// clang-format off

template <typename T>
concept property_value_type = std::same_as<T, int> ||
                              std::same_as<T, float> ||
                              std::same_as<T, bool> ||
                              std::same_as<T, std::string> ||
                              std::same_as<T, tmx_color> ||
                              std::same_as<T, tmx_file> ||
                              std::same_as<T, tmx_object_id>;

// clang-format on

template <property_value_type T>
[[nodiscard]] auto is(const tmx_property& property) noexcept -> bool
{
  return std::holds_alternative<T>(property.value);
}

template <property_value_type T>
[[nodiscard]] auto is(const tmx_properties& properties, const std::string_view name)
    -> bool
{
  if (const auto it = try_get(properties, name); it != properties.end())
  {
    return is<T>(*it);
  }
  else
  {
    return false;
  }
}

[[nodiscard]] inline auto is_string(const tmx_property& property) noexcept -> bool
{
  return is<std::string>(property);
}

[[nodiscard]] inline auto is_string(const tmx_properties& properties,
                                    const std::string_view name) -> bool
{
  return is<std::string>(properties, name);
}

[[nodiscard]] inline auto is_int(const tmx_property& property) noexcept -> bool
{
  return is<int>(property);
}

[[nodiscard]] inline auto is_int(const tmx_properties& properties,
                                 const std::string_view name) -> bool
{
  return is<int>(properties, name);
}

[[nodiscard]] inline auto is_float(const tmx_property& property) noexcept -> bool
{
  return is<float>(property);
}

[[nodiscard]] inline auto is_float(const tmx_properties& properties,
                                   const std::string_view name) -> bool
{
  return is<float>(properties, name);
}

[[nodiscard]] inline auto is_bool(const tmx_property& property) noexcept -> bool
{
  return is<bool>(property);
}

[[nodiscard]] inline auto is_bool(const tmx_properties& properties,
                                  const std::string_view name) -> bool
{
  return is<bool>(properties, name);
}

[[nodiscard]] inline auto is_color(const tmx_property& property) noexcept -> bool
{
  return is<tmx_color>(property);
}

[[nodiscard]] inline auto is_color(const tmx_properties& properties,
                                   const std::string_view name) -> bool
{
  return is<tmx_color>(properties, name);
}

[[nodiscard]] inline auto is_file(const tmx_property& property) noexcept -> bool
{
  return is<tmx_file>(property);
}

[[nodiscard]] inline auto is_file(const tmx_properties& properties,
                                  const std::string_view name) -> bool
{
  return is<tmx_file>(properties, name);
}

[[nodiscard]] inline auto is_object(const tmx_property& property) noexcept -> bool
{
  return is<tmx_object_id>(property);
}

[[nodiscard]] inline auto is_object(const tmx_properties& properties,
                                    const std::string_view name) -> bool
{
  return is<tmx_object_id>(properties, name);
}

/// \} End of property type indicators

/// \name Property value casts
/// \brief Type-safe cast functions for properties, that throw on type mismatches.
/// \{

template <property_value_type T>
[[nodiscard]] auto get(const tmx_property& property) -> const T&
{
  return std::get<T>(property.value);
}

template <property_value_type T>
[[nodiscard]] auto get(const tmx_properties& properties, const std::string_view name)
    -> const T&
{
  if (const auto it = try_get(properties, name); it != properties.end())
  {
    return get<T>(*it);
  }
  else
  {
    throw rune_error{"Could not find property with the specified name!"};
  }
}

[[nodiscard]] inline auto get_string(const tmx_property& property) -> const std::string&
{
  return get<std::string>(property);
}

[[nodiscard]] inline auto get_string(const tmx_properties& properties,
                                     const std::string_view name) -> const std::string&
{
  return get<std::string>(properties, name);
}

[[nodiscard]] inline auto get_int(const tmx_property& property) -> int
{
  return get<int>(property);
}

[[nodiscard]] inline auto get_int(const tmx_properties& properties,
                                  const std::string_view name) -> int
{
  return get<int>(properties, name);
}

[[nodiscard]] inline auto get_float(const tmx_property& property) -> float
{
  return get<float>(property);
}

[[nodiscard]] inline auto get_float(const tmx_properties& properties,
                                    const std::string_view name) -> float
{
  return get<float>(properties, name);
}

[[nodiscard]] inline auto get_bool(const tmx_property& property) -> bool
{
  return get<bool>(property);
}

[[nodiscard]] inline auto get_bool(const tmx_properties& properties,
                                   const std::string_view name) -> bool
{
  return get<bool>(properties, name);
}

[[nodiscard]] inline auto get_color(const tmx_property& property) -> const tmx_color&
{
  return get<tmx_color>(property);
}

[[nodiscard]] inline auto get_color(const tmx_properties& properties,
                                    const std::string_view name) -> const tmx_color&
{
  return get<tmx_color>(properties, name);
}

[[nodiscard]] inline auto get_file(const tmx_property& property) -> const tmx_file&
{
  return get<tmx_file>(property);
}

[[nodiscard]] inline auto get_file(const tmx_properties& properties,
                                   const std::string_view name) -> const tmx_file&
{
  return get<tmx_file>(properties, name);
}

[[nodiscard]] inline auto get_object(const tmx_property& property) -> tmx_object_id
{
  return get<tmx_object_id>(property);
}

[[nodiscard]] inline auto get_object(const tmx_properties& properties,
                                     const std::string_view name) -> tmx_object_id
{
  return get<tmx_object_id>(properties, name);
}

/// \} End of property value casts

/**
 * \brief Indicates whether or not a property with the specified name exists in a vector
 * of properties.
 *
 * \param properties the vector of properties that will be searched.
 * \param name the name of the property to look for.
 *
 * \return `true` if the properties contains a property with the specified name; `false`
 * otherwise.
 */
[[nodiscard]] inline auto contains(const tmx_properties& properties,
                                   const std::string_view name) -> bool
{
  return std::ranges::any_of(properties, [name](const tmx_property& property) noexcept {
    return property.name == name;
  });
}

/**
 * \brief Attempts to find and return a property with the specified name.
 *
 * \param properties the properties that will be searched.
 * \param name the name of the desired property.
 *
 * \return the property with the specified name.
 *
 * \throws rune_error if there is no property with the specified name.
 */
[[nodiscard]] inline auto find(const tmx_properties& properties,
                               const std::string_view name) -> const tmx_property&
{
  if (const auto it = try_get(properties, name); it != properties.end())
  {
    return *it;
  }
  else
  {
    throw rune_error{"Could not find property with specified name!"};
  }
}

/// \} End of group tmx

}  // namespace tmx

}  // namespace rune

#endif  // RUNE_TMX_PROPERTY_HPP

// #include "tmx_terrain.hpp"
#ifndef RUNE_TMX_TERRAIN_HPP
#define RUNE_TMX_TERRAIN_HPP

#include <json.hpp>  // json
#include <string>    // string

// #include "tmx_local_id.hpp"
#ifndef RUNE_TMX_LOCAL_ID_HPP
#define RUNE_TMX_LOCAL_ID_HPP

#include <nenya.hpp>  // strong_type

// #include "../aliases/integers.hpp"


namespace rune {

/// \cond FALSE
namespace tags {
struct tmx_local_id_tag;
}  // namespace tags
/// \endcond

/// \addtogroup tmx
/// \{

using tmx_local_id = nenya::strong_type<int, tags::tmx_local_id_tag>;

/// \} End of group tmx

namespace tmx_literals {

/// \addtogroup tmx
/// \{

/// \name Literal operators
/// \{

[[nodiscard]] constexpr auto operator""_local(const ulonglong value) noexcept
    -> tmx_local_id
{
  return tmx_local_id{static_cast<tmx_local_id::value_type>(value)};
}

/// \} End of literal operators

/// \} End of group tmx

}  // namespace tmx_literals
}  // namespace rune

#endif  // RUNE_TMX_LOCAL_ID_HPP

// #include "tmx_property.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_terrain final
{
  tmx_local_id tile{};
  std::string name;
  tmx_properties properties;
};

void from_json(const nlohmann::json& json, tmx_terrain& terrain);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_TERRAIN_HPP

// #include "tmx_tile.hpp"
#ifndef RUNE_TMX_TILE_HPP
#define RUNE_TMX_TILE_HPP

#include <array>     // array
#include <json.hpp>  // json
#include <optional>  // optional
#include <string>    // string, stoi

// #include "tmx_animation.hpp"
#ifndef RUNE_TMX_ANIMATION_HPP
#define RUNE_TMX_ANIMATION_HPP

#include <chrono>    // milliseconds
#include <json.hpp>  // json
#include <vector>    // vector

// #include "tmx_local_id.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_frame final
{
  tmx_local_id tile{};
  std::chrono::milliseconds duration{};
};

struct tmx_animation final
{
  std::vector<tmx_frame> frames;
};

void from_json(const nlohmann::json& json, tmx_frame& frame);
void from_json(const nlohmann::json& json, tmx_animation& animation);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_ANIMATION_HPP

// #include "tmx_layer.hpp"
#ifndef RUNE_TMX_LAYER_HPP
#define RUNE_TMX_LAYER_HPP

#include <cassert>   // assert
#include <concepts>  // same_as
#include <json.hpp>  // json
#include <memory>    // unique_ptr
#include <optional>  // optional
#include <string>    // string
#include <variant>   // variant, monostate
#include <vector>    // vector

// #include "../aliases/integers.hpp"

// #include "../io/json_utils.hpp"

// #include "tmx_color.hpp"

// #include "tmx_image_layer.hpp"
#ifndef RUNE_TMX_IMAGE_LAYER_HPP
#define RUNE_TMX_IMAGE_LAYER_HPP

#include <json.hpp>  // json
#include <optional>  // optional
#include <string>    // string

// #include "tmx_color.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_image_layer final
{
  std::string image;
  std::optional<tmx_color> transparent;
};

void from_json(const nlohmann::json& json, tmx_image_layer& layer);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_IMAGE_LAYER_HPP

// #include "tmx_layer_type.hpp"
#ifndef RUNE_TMX_LAYER_TYPE_HPP
#define RUNE_TMX_LAYER_TYPE_HPP

#include <json.hpp>  // NLOHMANN_JSON_SERIALIZE_ENUM

namespace rune {

/// \addtogroup tmx
/// \{

enum class tmx_layer_type
{
  tile_layer,
  object_layer,
  image_layer,
  group
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_layer_type,
                             {{tmx_layer_type::tile_layer, "tilelayer"},
                              {tmx_layer_type::image_layer, "imagelayer"},
                              {tmx_layer_type::object_layer, "objectgroup"},
                              {tmx_layer_type::group, "group"}})

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_LAYER_TYPE_HPP

// #include "tmx_object.hpp"
#ifndef RUNE_TMX_OBJECT_HPP
#define RUNE_TMX_OBJECT_HPP

#include <memory>    // unique_ptr
#include <optional>  // optional
#include <string>    // string
#include <variant>   // variant, monostate
#include <vector>    // vector

// #include "../aliases/integers.hpp"

// #include "../io/json_utils.hpp"

// #include "tmx_global_id.hpp"

// #include "tmx_point.hpp"
#ifndef RUNE_TMX_POINT_HPP
#define RUNE_TMX_POINT_HPP

#include <json.hpp>  // json

namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_point final
{
  float x{};
  float y{};
};

void from_json(const nlohmann::json& json, tmx_point& point);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_POINT_HPP

// #include "tmx_property.hpp"

// #include "tmx_text.hpp"
#ifndef RUNE_TMX_TEXT_HPP
#define RUNE_TMX_TEXT_HPP

#include <json.hpp>  // json
#include <string>    // string

// #include "tmx_color.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

enum class tmx_halign
{
  center,
  right,
  left,
  justify
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_halign,
                             {{tmx_halign::center, "center"},
                              {tmx_halign::right, "right"},
                              {tmx_halign::left, "left"},
                              {tmx_halign::justify, "justify"}})

enum class tmx_valign
{
  center,
  top,
  bottom
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_valign,
                             {{tmx_valign::center, "center"},
                              {tmx_valign::top, "top"},
                              {tmx_valign::bottom, "bottom"}})

struct tmx_text final
{
  std::string text;
  std::string family{"sans-serif"};
  tmx_color color;
  tmx_halign horizontal_alignment{tmx_halign::left};
  tmx_valign vertical_alignment{tmx_valign::top};
  int pixel_size{16};
  bool bold{};
  bool italic{};
  bool kerning{true};
  bool strikeout{};
  bool underline{};
  bool wrap{};
};

void from_json(const nlohmann::json& json, tmx_text& text);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_TEXT_HPP


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_object;

struct tmx_polygon final
{
  std::vector<tmx_point> points;
};

struct tmx_polyline final
{
  std::vector<tmx_point> points;
};

struct tmx_template_object final
{
  std::string template_file;
  std::unique_ptr<tmx_object> object;
  std::optional<std::string> tileset_source;
  std::optional<tmx_global_id> tileset_first_id;
};

struct tmx_object final
{
  using data_type = std::variant<std::monostate,
                                 tmx_polygon,
                                 tmx_polyline,
                                 tmx_text,
                                 tmx_template_object,
                                 tmx_global_id>;

  int id{};
  float x{};
  float y{};
  float width{};
  float height{};
  float rotation{};
  std::string name;
  std::string type;
  tmx_properties properties;
  data_type data;
  bool is_ellipse{};
  bool is_point{};
  bool visible{true};
};

void from_json(const nlohmann::json& json, tmx_polygon& polygon);
void from_json(const nlohmann::json& json, tmx_polyline& line);
void from_json(const nlohmann::json& json, tmx_template_object& object);
void from_json(const nlohmann::json& json, tmx_object& object);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_OBJECT_HPP

// #include "tmx_object_layer.hpp"
#ifndef RUNE_TMX_OBJECT_LAYER_HPP
#define RUNE_TMX_OBJECT_LAYER_HPP

#include <cassert>   // assert
#include <json.hpp>  // json, NLOHMANN_JSON_SERIALIZE_ENUM
#include <vector>    // vector

// #include "tmx_object.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

enum class tmx_object_layer_draw_order
{
  top_down,
  index
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_object_layer_draw_order,
                             {{tmx_object_layer_draw_order::top_down, "topdown"},
                              {tmx_object_layer_draw_order::index, "index"}})

struct tmx_object_layer final  // Note, referred to as "object group" by tiled
{
  tmx_object_layer_draw_order draw_order{tmx_object_layer_draw_order::top_down};
  std::vector<tmx_object> objects;
};

void from_json(const nlohmann::json& json, tmx_object_layer& layer);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_OBJECT_LAYER_HPP

// #include "tmx_property.hpp"

// #include "tmx_tile_layer.hpp"
#ifndef RUNE_TMX_TILE_LAYER_HPP
#define RUNE_TMX_TILE_LAYER_HPP

#include <json.hpp>  // json, NLOHMANN_JSON_SERIALIZE_ENUM
#include <optional>  // optional

// #include "tmx_data.hpp"
#ifndef RUNE_TMX_DATA_HPP
#define RUNE_TMX_DATA_HPP

#include <cassert>   // assert
#include <json.hpp>  // json
#include <string>    // string
#include <variant>   // variant
#include <vector>    // vector

// #include "../aliases/integers.hpp"

// #include "tmx_global_id.hpp"


namespace rune {

struct tmx_data final
{
  using gid_data = std::vector<tmx_global_id>;
  using base64_data = std::string;
  using data_type = std::variant<gid_data, base64_data>;

  data_type tile_data;
};

void from_json(const nlohmann::json& json, tmx_data& data);

}  // namespace rune

#endif  // RUNE_TMX_DATA_HPP


namespace rune {

/// \addtogroup tmx
/// \{

enum class tmx_tile_layer_compression
{
  none,
  gzip,
  zlib
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_tile_layer_compression,
                             {{tmx_tile_layer_compression::none, ""},
                              {tmx_tile_layer_compression::gzip, "gzip"},
                              {tmx_tile_layer_compression::zlib, "zlib"}})

enum class tmx_tile_layer_encoding
{
  csv,
  base64
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_tile_layer_encoding,
                             {{tmx_tile_layer_encoding::csv, "csv"},
                              {tmx_tile_layer_encoding::base64, "base64"}})

struct tmx_tile_layer final
{
  tmx_tile_layer_compression compression{tmx_tile_layer_compression::none};
  tmx_tile_layer_encoding encoding{tmx_tile_layer_encoding::csv};
  std::optional<tmx_data> data;
  // TODO std::vector<chunk> m_chunks;
};

void from_json(const nlohmann::json& json, tmx_tile_layer& layer);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_TILE_LAYER_HPP


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_layer;

struct tmx_group final
{
  std::vector<std::unique_ptr<tmx_layer>> layers;
};

struct tmx_layer final
{
  using data_type = std::variant<std::monostate,
                                 tmx_tile_layer,
                                 tmx_image_layer,
                                 tmx_object_layer,
                                 tmx_group>;

  tmx_layer_type type{tmx_layer_type::tile_layer};
  int id{};
  int width{};
  int height{};
  int start_x{};
  int start_y{};
  float parallax_x{1};
  float parallax_y{1};
  float offset_x{};
  float offset_y{};
  float opacity{1};

  std::optional<tmx_color> tint;
  tmx_properties properties;

  data_type data;

  std::string name;
  bool visible{true};
};

using tmx_layers = std::vector<tmx_layer>;

void from_json(const nlohmann::json& json, tmx_group& group);
void from_json(const nlohmann::json& json, tmx_layer& layer);

/// \} End of group tmx

namespace tmx {

/// \addtogroup tmx
/// \{

// clang-format off

template <typename T>
concept layer_value_type = std::same_as<T, tmx_tile_layer> ||
                           std::same_as<T, tmx_object_layer> ||
                           std::same_as<T, tmx_image_layer> ||
                           std::same_as<T, tmx_group>;

// clang-format on

/// \name Layer type casts
/// \{

template <layer_value_type T>
[[nodiscard]] auto get(const tmx_layer& layer) -> const T&
{
  return std::get<T>(layer.data);
}

[[nodiscard]] inline auto get_tile_layer(const tmx_layer& layer) -> const tmx_tile_layer&
{
  return get<tmx_tile_layer>(layer);
}

[[nodiscard]] inline auto get_image_layer(const tmx_layer& layer)
    -> const tmx_image_layer&
{
  return get<tmx_image_layer>(layer);
}

[[nodiscard]] inline auto get_object_layer(const tmx_layer& layer)
    -> const tmx_object_layer&
{
  return get<tmx_object_layer>(layer);
}

[[nodiscard]] inline auto get_group(const tmx_layer& layer) -> const tmx_group&
{
  return get<tmx_group>(layer);
}

template <layer_value_type T>
[[nodiscard]] auto try_get(const tmx_layer& layer) noexcept -> const T*
{
  return std::get_if<T>(&layer.data);
}

[[nodiscard]] inline auto try_get_tile_layer(const tmx_layer& layer) noexcept
    -> const tmx_tile_layer*
{
  return try_get<tmx_tile_layer>(layer);
}

[[nodiscard]] inline auto try_get_object_layer(const tmx_layer& layer) noexcept
    -> const tmx_object_layer*
{
  return try_get<tmx_object_layer>(layer);
}

[[nodiscard]] inline auto try_get_image_layer(const tmx_layer& layer) noexcept
    -> const tmx_image_layer*
{
  return try_get<tmx_image_layer>(layer);
}

[[nodiscard]] inline auto try_get_group(const tmx_layer& layer) noexcept
    -> const tmx_group*
{
  return try_get<tmx_group>(layer);
}

/// \} End of layer type casts

/// \name Layer type indicators
/// \{

template <layer_value_type T>
[[nodiscard]] auto is(const tmx_layer& layer) noexcept -> bool
{
  return std::holds_alternative<T>(layer.data);
}

[[nodiscard]] inline auto is_tile_layer(const tmx_layer& layer) noexcept -> bool
{
  return is<tmx_tile_layer>(layer);
}

[[nodiscard]] inline auto is_object_layer(const tmx_layer& layer) noexcept -> bool
{
  return is<tmx_object_layer>(layer);
}

[[nodiscard]] inline auto is_image_layer(const tmx_layer& layer) noexcept -> bool
{
  return is<tmx_image_layer>(layer);
}

[[nodiscard]] inline auto is_group(const tmx_layer& layer) noexcept -> bool
{
  return is<tmx_group>(layer);
}

/// \} End of layer type indicators

/// \} End of group tmx

}  // namespace tmx
}  // namespace rune

#endif  // RUNE_TMX_LAYER_HPP

// #include "tmx_local_id.hpp"

// #include "tmx_property.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_tile final
{
  tmx_local_id id{};
  std::optional<tmx_animation> animation;
  std::optional<std::array<int, 4>> terrain;
  std::optional<std::string> type;
  std::optional<std::string> image;
  std::optional<int> image_width;
  std::optional<int> image_height;
  std::optional<float> probability;
  std::optional<tmx_layer> object_layer;
  tmx_properties properties;
};

void from_json(const nlohmann::json& json, tmx_tile& tile);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_TILE_HPP

// #include "tmx_tile_offset.hpp"
#ifndef RUNE_TMX_TILE_OFFSET_HPP
#define RUNE_TMX_TILE_OFFSET_HPP

#include <json.hpp>  // json

namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_tile_offset final
{
  int x{};
  int y{};
};

void from_json(const nlohmann::json& json, tmx_tile_offset& offset);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_TILE_OFFSET_HPP

// #include "tmx_wang_set.hpp"
#ifndef RUNE_TMX_WANG_SET_HPP
#define RUNE_TMX_WANG_SET_HPP

#include <json.hpp>  // json
#include <string>    // string
#include <vector>    // vector

// #include "tmx_local_id.hpp"

// #include "tmx_property.hpp"

// #include "tmx_wang_color.hpp"
#ifndef RUNE_TMX_WANG_COLOR_HPP
#define RUNE_TMX_WANG_COLOR_HPP

#include <json.hpp>  // json
#include <string>    // string

// #include "tmx_color.hpp"

// #include "tmx_local_id.hpp"

// #include "tmx_property.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_wang_color final
{
  tmx_local_id tile{};
  tmx_color color;
  std::string name;
  float probability{};
  tmx_properties properties;
};

void from_json(const nlohmann::json& json, tmx_wang_color& color);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_WANG_COLOR_HPP

// #include "tmx_wang_tile.hpp"
#ifndef RUNE_TMX_WANG_TILE_HPP
#define RUNE_TMX_WANG_TILE_HPP

#include <array>     // array
#include <json.hpp>  // json

// #include "../aliases/integers.hpp"

// #include "tmx_local_id.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_wang_tile final
{
  tmx_local_id tile{};
  std::array<uint8, 8> indices{};
};

void from_json(const nlohmann::json& json, tmx_wang_tile& tile);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_WANG_TILE_HPP


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_wang_set final
{
  tmx_local_id tile{};
  std::string name;
  std::vector<tmx_wang_tile> wang_tiles;
  std::vector<tmx_wang_color> colors;
  tmx_properties properties;
};

void from_json(const nlohmann::json& json, tmx_wang_set& set);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_WANG_SET_HPP


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_tileset final
{
  tmx_global_id first_id{1};
  int tile_width{};
  int tile_height{};
  int tile_count{};
  int column_count{};
  int image_width{};
  int image_height{};
  int margin{};
  int spacing{};
  float json_version{};

  std::string name;
  std::string image;
  std::string external_source;
  std::string tiled_version;

  std::optional<tmx_color> background;
  std::optional<tmx_color> transparent;
  std::optional<tmx_tile_offset> tile_offset;
  std::optional<tmx_grid> grid;

  std::vector<tmx_tile> tiles;
  std::vector<tmx_terrain> terrains;
  std::vector<tmx_wang_set> wang_sets;
  tmx_properties properties;
};

using tmx_tilesets = std::vector<tmx_tileset>;

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_TILESET_HPP


namespace rune::tmx {

/// \cond FALSE
namespace detail {

inline void parse_tileset(const nlohmann::json& json, tmx_tileset& tileset)
{
  json.at("tilewidth").get_to(tileset.tile_width);
  json.at("tileheight").get_to(tileset.tile_height);
  json.at("tilecount").get_to(tileset.tile_count);
  json.at("columns").get_to(tileset.column_count);
  json.at("imagewidth").get_to(tileset.image_width);
  json.at("imageheight").get_to(tileset.image_height);
  json.at("margin").get_to(tileset.margin);
  json.at("spacing").get_to(tileset.spacing);
  json.at("image").get_to(tileset.image);
  json.at("name").get_to(tileset.name);

  get_if_exists(json, "tiledversion", tileset.tiled_version);
  get_if_exists(json, "version", tileset.json_version);
  get_if_exists(json, "backgroundcolor", tileset.background);
  get_if_exists(json, "transparentcolor", tileset.transparent);
  get_if_exists(json, "tileoffset", tileset.tile_offset);
  get_if_exists(json, "grid", tileset.grid);

  fill_if_exists(json, "tiles", tileset.tiles);
  fill_if_exists(json, "terrains", tileset.terrains);
  fill_if_exists(json, "wangsets", tileset.wang_sets);
  fill_if_exists(json, "properties", tileset.properties);
}

}  // namespace detail
/// \endcond

/// \addtogroup tmx
/// \{

[[nodiscard]] inline auto parse_tileset(const std::filesystem::path& directory,
                                        const nlohmann::json& json) -> tmx_tileset
{
  tmx_tileset tileset;

  tileset.first_id = tmx_global_id{json.at("firstgid").get<tmx_global_id::value_type>()};
  if (const auto it = json.find("source"); it != json.end())
  {
    // External
    tileset.external_source = it->get<std::string>();

    const auto source = directory / tileset.external_source;
    const auto external = read_json(source);

    detail::parse_tileset(external, tileset);
  }
  else
  {
    // Embedded
    detail::parse_tileset(json, tileset);
  }

  return tileset;
}

/// \} End of group tmx

}  // namespace rune::tmx

#endif  // RUNE_TMX_PARSE_TILESET_HPP

// #include "rune/tmx/tmx.hpp"
#ifndef RUNE_TMX_TMX_HPP
#define RUNE_TMX_TMX_HPP

#include <cassert>     // assert
#include <filesystem>  // path
#include <string>      // string

// #include "../aliases/integers.hpp"

// #include "../io/json_utils.hpp"

// #include "parse_tileset.hpp"
#ifndef RUNE_TMX_PARSE_TILESET_HPP
#define RUNE_TMX_PARSE_TILESET_HPP

#include <filesystem>  // path
#include <json.hpp>    // json
#include <string>      // string

// #include "../io/json_utils.hpp"

// #include "tmx_global_id.hpp"

// #include "tmx_tileset.hpp"


namespace rune::tmx {

/// \cond FALSE
namespace detail {

inline void parse_tileset(const nlohmann::json& json, tmx_tileset& tileset)
{
  json.at("tilewidth").get_to(tileset.tile_width);
  json.at("tileheight").get_to(tileset.tile_height);
  json.at("tilecount").get_to(tileset.tile_count);
  json.at("columns").get_to(tileset.column_count);
  json.at("imagewidth").get_to(tileset.image_width);
  json.at("imageheight").get_to(tileset.image_height);
  json.at("margin").get_to(tileset.margin);
  json.at("spacing").get_to(tileset.spacing);
  json.at("image").get_to(tileset.image);
  json.at("name").get_to(tileset.name);

  get_if_exists(json, "tiledversion", tileset.tiled_version);
  get_if_exists(json, "version", tileset.json_version);
  get_if_exists(json, "backgroundcolor", tileset.background);
  get_if_exists(json, "transparentcolor", tileset.transparent);
  get_if_exists(json, "tileoffset", tileset.tile_offset);
  get_if_exists(json, "grid", tileset.grid);

  fill_if_exists(json, "tiles", tileset.tiles);
  fill_if_exists(json, "terrains", tileset.terrains);
  fill_if_exists(json, "wangsets", tileset.wang_sets);
  fill_if_exists(json, "properties", tileset.properties);
}

}  // namespace detail
/// \endcond

/// \addtogroup tmx
/// \{

[[nodiscard]] inline auto parse_tileset(const std::filesystem::path& directory,
                                        const nlohmann::json& json) -> tmx_tileset
{
  tmx_tileset tileset;

  tileset.first_id = tmx_global_id{json.at("firstgid").get<tmx_global_id::value_type>()};
  if (const auto it = json.find("source"); it != json.end())
  {
    // External
    tileset.external_source = it->get<std::string>();

    const auto source = directory / tileset.external_source;
    const auto external = read_json(source);

    detail::parse_tileset(external, tileset);
  }
  else
  {
    // Embedded
    detail::parse_tileset(json, tileset);
  }

  return tileset;
}

/// \} End of group tmx

}  // namespace rune::tmx

#endif  // RUNE_TMX_PARSE_TILESET_HPP

// #include "tmx_global_id.hpp"

// #include "tmx_local_id.hpp"

// #include "tmx_map.hpp"
#ifndef RUNE_TMX_MAP_HPP
#define RUNE_TMX_MAP_HPP

#include <json.hpp>  // NLOHMANN_JSON_SERIALIZE_ENUM
#include <optional>  // optional
#include <string>    // string
#include <vector>    // vector

// #include "tmx_color.hpp"

// #include "tmx_layer.hpp"

// #include "tmx_property.hpp"

// #include "tmx_tileset.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

enum class tmx_map_orientation
{
  orthogonal,
  isometric,
  staggered,
  hexagonal
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_map_orientation,
                             {{tmx_map_orientation::orthogonal, "orthogonal"},
                              {tmx_map_orientation::isometric, "isometric"},
                              {tmx_map_orientation::staggered, "staggered"},
                              {tmx_map_orientation::hexagonal, "hexagonal"}})

enum class tmx_map_render_order
{
  right_down,
  right_up,
  left_down,
  left_up
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_map_render_order,
                             {{tmx_map_render_order::right_down, "right-down"},
                              {tmx_map_render_order::right_up, "right-up"},
                              {tmx_map_render_order::left_down, "left-down"},
                              {tmx_map_render_order::left_up, "left-up"}})

enum class tmx_stagger_axis
{
  x,
  y
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_stagger_axis,
                             {{tmx_stagger_axis::x, "x"}, {tmx_stagger_axis::y, "y"}})

enum class tmx_stagger_index
{
  odd,
  even
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_stagger_index,
                             {{tmx_stagger_index::odd, "odd"},
                              {tmx_stagger_index::even, "even"}})

struct tmx_map final
{
  int width{};   ///< Number of columns.
  int height{};  ///< Number of rows.

  int next_layer_id{1};
  int next_object_id{1};

  int tile_height{};
  int tile_width{};

  int compression_level{-1};
  int hex_side_length{};

  tmx_map_orientation orientation{tmx_map_orientation::orthogonal};
  tmx_map_render_order render_order{tmx_map_render_order::right_down};

  std::optional<tmx_color> background;
  std::optional<tmx_stagger_axis> stagger_axis;
  std::optional<tmx_stagger_index> stagger_index;

  std::vector<tmx_layer> layers;
  std::vector<tmx_tileset> tilesets;
  tmx_properties properties;

  std::string tiled_version;
  std::string json_version;
  bool infinite{};
};

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_MAP_HPP


namespace rune {

/// \addtogroup tmx
/// \{

/**
 * \brief Parses a Tiled JSON map file, and returns the contents.
 *
 * \details This function will not validate the specified JSON file. An invalid map file
 * will likely result in an exception being thrown due to parsing errors. However, there
 * are debug assertions that try to make it easier to detect errors and their cause,
 * compared to the generic exceptions from the JSON parser.
 *
 * \note The Tiled XML format is not supported.
 *
 * \param path the file path to the Tiled JSON map file.
 *
 * \return the parsed Tiled map.
 */
[[nodiscard]] inline auto parse_tmx(const std::filesystem::path& path) -> tmx_map
{
  assert(path.extension() == ".json");

  const auto json = read_json(path);
  assert(json.contains("type") && "Map file requires \"type\" element!");
  assert(json.at("type").get<std::string>() == "map");

  tmx_map map;

  json.at("width").get_to(map.width);
  json.at("height").get_to(map.height);
  json.at("nextlayerid").get_to(map.next_layer_id);
  json.at("nextobjectid").get_to(map.next_object_id);
  json.at("tilewidth").get_to(map.tile_width);
  json.at("tileheight").get_to(map.tile_height);
  json.at("infinite").get_to(map.infinite);
  json.at("orientation").get_to(map.orientation);
  json.at("renderorder").get_to(map.render_order);
  json.at("tiledversion").get_to(map.tiled_version);
  json.at("version").get_to(map.json_version);

  get_if_exists(json, "backgroundcolor", map.background);
  get_if_exists(json, "compressionlevel", map.compression_level);
  get_if_exists(json, "hexsidelength", map.hex_side_length);
  get_if_exists(json, "staggeraxis", map.stagger_axis);
  get_if_exists(json, "staggerindex", map.stagger_index);

  fill_if_exists(json, "layers", map.layers);
  fill_if_exists(json, "properties", map.properties);

  if (const auto it = json.find("tilesets"); it != json.end())
  {
    const auto directory = path.parent_path();

    map.tilesets.reserve(it->size());
    for (const auto& [key, value] : it->items())
    {
      map.tilesets.push_back(tmx::parse_tileset(directory, value));
    }
  }

  return map;
}

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_TMX_HPP

// #include "rune/tmx/tmx_animation.hpp"
#ifndef RUNE_TMX_ANIMATION_HPP
#define RUNE_TMX_ANIMATION_HPP

#include <chrono>    // milliseconds
#include <json.hpp>  // json
#include <vector>    // vector

// #include "tmx_local_id.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_frame final
{
  tmx_local_id tile{};
  std::chrono::milliseconds duration{};
};

struct tmx_animation final
{
  std::vector<tmx_frame> frames;
};

void from_json(const nlohmann::json& json, tmx_frame& frame);
void from_json(const nlohmann::json& json, tmx_animation& animation);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_ANIMATION_HPP

// #include "rune/tmx/tmx_color.hpp"
#ifndef RUNE_TMX_COLOR_HPP
#define RUNE_TMX_COLOR_HPP

#include <cassert>       // assert
#include <charconv>      // from_chars
#include <json.hpp>      // json
#include <string_view>   // string_view
#include <system_error>  // errc

// #include "../aliases/integers.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_color final
{
  uint8 red{};
  uint8 green{};
  uint8 blue{};
  uint8 alpha{0xFF};

  [[nodiscard]] constexpr bool operator==(const tmx_color&) const noexcept = default;
};

void from_json(const nlohmann::json& json, tmx_color& color);

/// \} End of group tmx

namespace tmx {

/// \addtogroup tmx
/// \{

inline constexpr tmx_color black{0, 0, 0, 0xFF};

[[nodiscard]] inline auto from_hex(const std::string_view str) -> uint8
{
  assert(str.size() == 2);

  uint8 value{};
  const auto [ptr, error] =
      std::from_chars(str.data(), str.data() + str.size(), value, 16);
  assert(error != std::errc::invalid_argument);
  assert(error != std::errc::result_out_of_range);

  return value;
}

[[nodiscard]] inline auto make_color(const std::string_view str) -> tmx_color
{
  assert(str.size() == 7 || str.size() == 9);
  assert(str.at(0) == '#');

  const auto noHash = str.substr(1);
  const auto length = noHash.size();

  tmx_color result;

  if (length == 8)
  {
    // ARGB
    result.alpha = from_hex(noHash.substr(0, 2));
    result.red = from_hex(noHash.substr(2, 2));
    result.green = from_hex(noHash.substr(4, 2));
    result.blue = from_hex(noHash.substr(6, 2));
  }
  else
  {
    // RGB
    result.red = from_hex(noHash.substr(0, 2));
    result.green = from_hex(noHash.substr(2, 2));
    result.blue = from_hex(noHash.substr(4, 2));
  }

  return result;
}

/// \} End of group tmx

}  // namespace tmx
}  // namespace rune

#endif  // RUNE_TMX_COLOR_TEST

// #include "rune/tmx/tmx_data.hpp"
#ifndef RUNE_TMX_DATA_HPP
#define RUNE_TMX_DATA_HPP

#include <cassert>   // assert
#include <json.hpp>  // json
#include <string>    // string
#include <variant>   // variant
#include <vector>    // vector

// #include "../aliases/integers.hpp"

// #include "tmx_global_id.hpp"


namespace rune {

struct tmx_data final
{
  using gid_data = std::vector<tmx_global_id>;
  using base64_data = std::string;
  using data_type = std::variant<gid_data, base64_data>;

  data_type tile_data;
};

void from_json(const nlohmann::json& json, tmx_data& data);

}  // namespace rune

#endif  // RUNE_TMX_DATA_HPP

// #include "rune/tmx/tmx_global_id.hpp"
#ifndef RUNE_TMX_GLOBAL_ID_HPP
#define RUNE_TMX_GLOBAL_ID_HPP

#include <nenya.hpp>  // strong_type

// #include "../aliases/integers.hpp"


namespace rune {

/// \cond FALSE
namespace tags {
struct tmx_global_id_tag;
}
/// \endcond

/// \addtogroup tmx
/// \{

using tmx_global_id = nenya::strong_type<uint, tags::tmx_global_id_tag>;

/// \} End of group tmx

namespace tmx_literals {

/// \addtogroup tmx
/// \{

/// \name Literal operators
/// \{

[[nodiscard]] constexpr auto operator""_global(const ulonglong value) noexcept
    -> tmx_global_id
{
  return tmx_global_id{static_cast<tmx_global_id::value_type>(value)};
}

/// \} End of literal operators
/// \} End of group tmx

}  // namespace tmx_literals
}  // namespace rune

#endif  // RUNE_TMX_GLOBAL_ID_HPP

// #include "rune/tmx/tmx_grid.hpp"
#ifndef RUNE_TMX_GRID_HPP
#define RUNE_TMX_GRID_HPP

#include <json.hpp>  // json, NLOHMANN_JSON_SERIALIZE_ENUM

namespace rune {

/// \addtogroup tmx
/// \{

enum class tmx_grid_orientation
{
  orthogonal,
  isometric
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_grid_orientation,
                             {{tmx_grid_orientation::orthogonal, "orthogonal"},
                              {tmx_grid_orientation::isometric, "isometric"}})

struct tmx_grid final
{
  int cell_width{};
  int cell_height{};
  tmx_grid_orientation orientation{tmx_grid_orientation::orthogonal};
};

void from_json(const nlohmann::json& json, tmx_grid& grid);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_GRID_HPP

// #include "rune/tmx/tmx_image_layer.hpp"
#ifndef RUNE_TMX_IMAGE_LAYER_HPP
#define RUNE_TMX_IMAGE_LAYER_HPP

#include <json.hpp>  // json
#include <optional>  // optional
#include <string>    // string

// #include "tmx_color.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_image_layer final
{
  std::string image;
  std::optional<tmx_color> transparent;
};

void from_json(const nlohmann::json& json, tmx_image_layer& layer);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_IMAGE_LAYER_HPP

// #include "rune/tmx/tmx_layer.hpp"
#ifndef RUNE_TMX_LAYER_HPP
#define RUNE_TMX_LAYER_HPP

#include <cassert>   // assert
#include <concepts>  // same_as
#include <json.hpp>  // json
#include <memory>    // unique_ptr
#include <optional>  // optional
#include <string>    // string
#include <variant>   // variant, monostate
#include <vector>    // vector

// #include "../aliases/integers.hpp"

// #include "../io/json_utils.hpp"

// #include "tmx_color.hpp"

// #include "tmx_image_layer.hpp"

// #include "tmx_layer_type.hpp"

// #include "tmx_object.hpp"

// #include "tmx_object_layer.hpp"

// #include "tmx_property.hpp"

// #include "tmx_tile_layer.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_layer;

struct tmx_group final
{
  std::vector<std::unique_ptr<tmx_layer>> layers;
};

struct tmx_layer final
{
  using data_type = std::variant<std::monostate,
                                 tmx_tile_layer,
                                 tmx_image_layer,
                                 tmx_object_layer,
                                 tmx_group>;

  tmx_layer_type type{tmx_layer_type::tile_layer};
  int id{};
  int width{};
  int height{};
  int start_x{};
  int start_y{};
  float parallax_x{1};
  float parallax_y{1};
  float offset_x{};
  float offset_y{};
  float opacity{1};

  std::optional<tmx_color> tint;
  tmx_properties properties;

  data_type data;

  std::string name;
  bool visible{true};
};

using tmx_layers = std::vector<tmx_layer>;

void from_json(const nlohmann::json& json, tmx_group& group);
void from_json(const nlohmann::json& json, tmx_layer& layer);

/// \} End of group tmx

namespace tmx {

/// \addtogroup tmx
/// \{

// clang-format off

template <typename T>
concept layer_value_type = std::same_as<T, tmx_tile_layer> ||
                           std::same_as<T, tmx_object_layer> ||
                           std::same_as<T, tmx_image_layer> ||
                           std::same_as<T, tmx_group>;

// clang-format on

/// \name Layer type casts
/// \{

template <layer_value_type T>
[[nodiscard]] auto get(const tmx_layer& layer) -> const T&
{
  return std::get<T>(layer.data);
}

[[nodiscard]] inline auto get_tile_layer(const tmx_layer& layer) -> const tmx_tile_layer&
{
  return get<tmx_tile_layer>(layer);
}

[[nodiscard]] inline auto get_image_layer(const tmx_layer& layer)
    -> const tmx_image_layer&
{
  return get<tmx_image_layer>(layer);
}

[[nodiscard]] inline auto get_object_layer(const tmx_layer& layer)
    -> const tmx_object_layer&
{
  return get<tmx_object_layer>(layer);
}

[[nodiscard]] inline auto get_group(const tmx_layer& layer) -> const tmx_group&
{
  return get<tmx_group>(layer);
}

template <layer_value_type T>
[[nodiscard]] auto try_get(const tmx_layer& layer) noexcept -> const T*
{
  return std::get_if<T>(&layer.data);
}

[[nodiscard]] inline auto try_get_tile_layer(const tmx_layer& layer) noexcept
    -> const tmx_tile_layer*
{
  return try_get<tmx_tile_layer>(layer);
}

[[nodiscard]] inline auto try_get_object_layer(const tmx_layer& layer) noexcept
    -> const tmx_object_layer*
{
  return try_get<tmx_object_layer>(layer);
}

[[nodiscard]] inline auto try_get_image_layer(const tmx_layer& layer) noexcept
    -> const tmx_image_layer*
{
  return try_get<tmx_image_layer>(layer);
}

[[nodiscard]] inline auto try_get_group(const tmx_layer& layer) noexcept
    -> const tmx_group*
{
  return try_get<tmx_group>(layer);
}

/// \} End of layer type casts

/// \name Layer type indicators
/// \{

template <layer_value_type T>
[[nodiscard]] auto is(const tmx_layer& layer) noexcept -> bool
{
  return std::holds_alternative<T>(layer.data);
}

[[nodiscard]] inline auto is_tile_layer(const tmx_layer& layer) noexcept -> bool
{
  return is<tmx_tile_layer>(layer);
}

[[nodiscard]] inline auto is_object_layer(const tmx_layer& layer) noexcept -> bool
{
  return is<tmx_object_layer>(layer);
}

[[nodiscard]] inline auto is_image_layer(const tmx_layer& layer) noexcept -> bool
{
  return is<tmx_image_layer>(layer);
}

[[nodiscard]] inline auto is_group(const tmx_layer& layer) noexcept -> bool
{
  return is<tmx_group>(layer);
}

/// \} End of layer type indicators

/// \} End of group tmx

}  // namespace tmx
}  // namespace rune

#endif  // RUNE_TMX_LAYER_HPP

// #include "rune/tmx/tmx_layer_type.hpp"
#ifndef RUNE_TMX_LAYER_TYPE_HPP
#define RUNE_TMX_LAYER_TYPE_HPP

#include <json.hpp>  // NLOHMANN_JSON_SERIALIZE_ENUM

namespace rune {

/// \addtogroup tmx
/// \{

enum class tmx_layer_type
{
  tile_layer,
  object_layer,
  image_layer,
  group
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_layer_type,
                             {{tmx_layer_type::tile_layer, "tilelayer"},
                              {tmx_layer_type::image_layer, "imagelayer"},
                              {tmx_layer_type::object_layer, "objectgroup"},
                              {tmx_layer_type::group, "group"}})

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_LAYER_TYPE_HPP

// #include "rune/tmx/tmx_local_id.hpp"
#ifndef RUNE_TMX_LOCAL_ID_HPP
#define RUNE_TMX_LOCAL_ID_HPP

#include <nenya.hpp>  // strong_type

// #include "../aliases/integers.hpp"


namespace rune {

/// \cond FALSE
namespace tags {
struct tmx_local_id_tag;
}  // namespace tags
/// \endcond

/// \addtogroup tmx
/// \{

using tmx_local_id = nenya::strong_type<int, tags::tmx_local_id_tag>;

/// \} End of group tmx

namespace tmx_literals {

/// \addtogroup tmx
/// \{

/// \name Literal operators
/// \{

[[nodiscard]] constexpr auto operator""_local(const ulonglong value) noexcept
    -> tmx_local_id
{
  return tmx_local_id{static_cast<tmx_local_id::value_type>(value)};
}

/// \} End of literal operators

/// \} End of group tmx

}  // namespace tmx_literals
}  // namespace rune

#endif  // RUNE_TMX_LOCAL_ID_HPP

// #include "rune/tmx/tmx_map.hpp"
#ifndef RUNE_TMX_MAP_HPP
#define RUNE_TMX_MAP_HPP

#include <json.hpp>  // NLOHMANN_JSON_SERIALIZE_ENUM
#include <optional>  // optional
#include <string>    // string
#include <vector>    // vector

// #include "tmx_color.hpp"

// #include "tmx_layer.hpp"

// #include "tmx_property.hpp"

// #include "tmx_tileset.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

enum class tmx_map_orientation
{
  orthogonal,
  isometric,
  staggered,
  hexagonal
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_map_orientation,
                             {{tmx_map_orientation::orthogonal, "orthogonal"},
                              {tmx_map_orientation::isometric, "isometric"},
                              {tmx_map_orientation::staggered, "staggered"},
                              {tmx_map_orientation::hexagonal, "hexagonal"}})

enum class tmx_map_render_order
{
  right_down,
  right_up,
  left_down,
  left_up
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_map_render_order,
                             {{tmx_map_render_order::right_down, "right-down"},
                              {tmx_map_render_order::right_up, "right-up"},
                              {tmx_map_render_order::left_down, "left-down"},
                              {tmx_map_render_order::left_up, "left-up"}})

enum class tmx_stagger_axis
{
  x,
  y
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_stagger_axis,
                             {{tmx_stagger_axis::x, "x"}, {tmx_stagger_axis::y, "y"}})

enum class tmx_stagger_index
{
  odd,
  even
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_stagger_index,
                             {{tmx_stagger_index::odd, "odd"},
                              {tmx_stagger_index::even, "even"}})

struct tmx_map final
{
  int width{};   ///< Number of columns.
  int height{};  ///< Number of rows.

  int next_layer_id{1};
  int next_object_id{1};

  int tile_height{};
  int tile_width{};

  int compression_level{-1};
  int hex_side_length{};

  tmx_map_orientation orientation{tmx_map_orientation::orthogonal};
  tmx_map_render_order render_order{tmx_map_render_order::right_down};

  std::optional<tmx_color> background;
  std::optional<tmx_stagger_axis> stagger_axis;
  std::optional<tmx_stagger_index> stagger_index;

  std::vector<tmx_layer> layers;
  std::vector<tmx_tileset> tilesets;
  tmx_properties properties;

  std::string tiled_version;
  std::string json_version;
  bool infinite{};
};

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_MAP_HPP

// #include "rune/tmx/tmx_object.hpp"
#ifndef RUNE_TMX_OBJECT_HPP
#define RUNE_TMX_OBJECT_HPP

#include <memory>    // unique_ptr
#include <optional>  // optional
#include <string>    // string
#include <variant>   // variant, monostate
#include <vector>    // vector

// #include "../aliases/integers.hpp"

// #include "../io/json_utils.hpp"

// #include "tmx_global_id.hpp"

// #include "tmx_point.hpp"

// #include "tmx_property.hpp"

// #include "tmx_text.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_object;

struct tmx_polygon final
{
  std::vector<tmx_point> points;
};

struct tmx_polyline final
{
  std::vector<tmx_point> points;
};

struct tmx_template_object final
{
  std::string template_file;
  std::unique_ptr<tmx_object> object;
  std::optional<std::string> tileset_source;
  std::optional<tmx_global_id> tileset_first_id;
};

struct tmx_object final
{
  using data_type = std::variant<std::monostate,
                                 tmx_polygon,
                                 tmx_polyline,
                                 tmx_text,
                                 tmx_template_object,
                                 tmx_global_id>;

  int id{};
  float x{};
  float y{};
  float width{};
  float height{};
  float rotation{};
  std::string name;
  std::string type;
  tmx_properties properties;
  data_type data;
  bool is_ellipse{};
  bool is_point{};
  bool visible{true};
};

void from_json(const nlohmann::json& json, tmx_polygon& polygon);
void from_json(const nlohmann::json& json, tmx_polyline& line);
void from_json(const nlohmann::json& json, tmx_template_object& object);
void from_json(const nlohmann::json& json, tmx_object& object);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_OBJECT_HPP

// #include "rune/tmx/tmx_object_layer.hpp"
#ifndef RUNE_TMX_OBJECT_LAYER_HPP
#define RUNE_TMX_OBJECT_LAYER_HPP

#include <cassert>   // assert
#include <json.hpp>  // json, NLOHMANN_JSON_SERIALIZE_ENUM
#include <vector>    // vector

// #include "tmx_object.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

enum class tmx_object_layer_draw_order
{
  top_down,
  index
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_object_layer_draw_order,
                             {{tmx_object_layer_draw_order::top_down, "topdown"},
                              {tmx_object_layer_draw_order::index, "index"}})

struct tmx_object_layer final  // Note, referred to as "object group" by tiled
{
  tmx_object_layer_draw_order draw_order{tmx_object_layer_draw_order::top_down};
  std::vector<tmx_object> objects;
};

void from_json(const nlohmann::json& json, tmx_object_layer& layer);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_OBJECT_LAYER_HPP

// #include "rune/tmx/tmx_parsers.hpp"
#ifndef RUNE_TMX_PARSERS_HPP
#define RUNE_TMX_PARSERS_HPP

#include <cassert>   // assert
#include <json.hpp>  // json
#include <memory>    // make_unique
#include <string>    // string

// #include "../io/json_utils.hpp"

// #include "tmx_animation.hpp"

// #include "tmx_color.hpp"

// #include "tmx_data.hpp"

// #include "tmx_grid.hpp"

// #include "tmx_image_layer.hpp"

// #include "tmx_layer.hpp"

// #include "tmx_local_id.hpp"

// #include "tmx_object.hpp"

// #include "tmx_object_layer.hpp"

// #include "tmx_point.hpp"

// #include "tmx_terrain.hpp"

// #include "tmx_text.hpp"

// #include "tmx_tile.hpp"

// #include "tmx_tile_layer.hpp"

// #include "tmx_tile_offset.hpp"

// #include "tmx_tileset.hpp"

// #include "tmx_wang_color.hpp"

// #include "tmx_wang_set.hpp"

// #include "tmx_wang_tile.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

/// \name JSON conversions
/// \{

inline void from_json(const nlohmann::json& json, tmx_point& point)
{
  json.at("x").get_to(point.x);
  json.at("y").get_to(point.y);
}

inline void from_json(const nlohmann::json& json, tmx_color& color)
{
  color = tmx::make_color(json.get<std::string>());
}

inline void from_json(const nlohmann::json& json, tmx_grid& grid)
{
  json.at("width").get_to(grid.cell_width);
  json.at("height").get_to(grid.cell_height);
  json.at("orientation").get_to(grid.orientation);
}

inline void from_json(const nlohmann::json& json, tmx_tile_offset& offset)
{
  json.at("x").get_to(offset.x);
  json.at("y").get_to(offset.y);
}

inline void from_json(const nlohmann::json& json, tmx_wang_color& color)
{
  json.at("name").get_to(color.name);
  json.at("color").get_to(color.color);
  json.at("probability").get_to(color.probability);
  emplace(json, "tile", color.tile);

  fill_if_exists(json, "properties", color.properties);
}

inline void from_json(const nlohmann::json& json, tmx_wang_tile& tile)
{
  emplace(json, "tileid", tile.tile);
  json.at("wangid").get_to(tile.indices);
}

inline void from_json(const nlohmann::json& json, tmx_wang_set& set)
{
  emplace(json, "tile", set.tile);
  json.at("name").get_to(set.name);

  // TODO check if colors or wangtiles are required
  fill_if_exists(json, "colors", set.colors);
  fill_if_exists(json, "wangtiles", set.wang_tiles);
  fill_if_exists(json, "properties", set.properties);
}

inline void from_json(const nlohmann::json& json, tmx_property& property)
{
  json.at("name").get_to(property.name);
  json.at("type").get_to(property.type);

  switch (property.type)
  {
    default:
      assert(false && "from_json() for tmx_property has missing branch!");

    case tmx_property_type::string:
      property.value.emplace<std::string>(json.at("value").get<std::string>());
      break;

    case tmx_property_type::integer:
      property.value.emplace<int>(json.at("value").get<int>());
      break;

    case tmx_property_type::floating:
      property.value.emplace<float>(json.at("value").get<float>());
      break;

    case tmx_property_type::boolean:
      property.value.emplace<bool>(json.at("value").get<bool>());
      break;

    case tmx_property_type::color:
      property.value.emplace<tmx_color>(json.at("value").get<tmx_color>());
      break;

    case tmx_property_type::file:
      property.value.emplace<tmx_file>(json.at("value").get<std::string>());
      break;

    case tmx_property_type::object:
      property.value.emplace<tmx_object_id>(json.at("value").get<int>());
      break;
  }
}

inline void from_json(const nlohmann::json& json, tmx_terrain& terrain)
{
  terrain.tile = tmx_local_id{json.at("tile").get<tmx_local_id::value_type>()};
  json.at("name").get_to(terrain.name);
  fill_if_exists(json, "properties", terrain.properties);
}

inline void from_json(const nlohmann::json& json, tmx_text& text)
{
  json.at("text").get_to(text.text);

  get_if_exists(json, "fontfamily", text.family);
  get_if_exists(json, "halign", text.horizontal_alignment);
  get_if_exists(json, "valign", text.vertical_alignment);
  get_if_exists(json, "pixelsize", text.pixel_size);
  get_if_exists(json, "bold", text.bold);
  get_if_exists(json, "italic", text.italic);
  get_if_exists(json, "kerning", text.kerning);
  get_if_exists(json, "strikeout", text.strikeout);
  get_if_exists(json, "underline", text.underline);
  get_if_exists(json, "wrap", text.wrap);

  if (const auto it = json.find("color"); it != json.end())
  {
    text.color = tmx::make_color(it->get<std::string>());
  }
}

inline void from_json(const nlohmann::json& json, tmx_frame& frame)
{
  using ms_t = std::chrono::milliseconds;

  emplace(json, "tileid", frame.tile);
  frame.duration = ms_t{json.at("duration").get<ms_t::rep>()};
}

inline void from_json(const nlohmann::json& json, tmx_animation& animation)
{
  fill(json, animation.frames);
}

inline void from_json(const nlohmann::json& json, tmx_data& data)
{
  assert(json.is_array() || json.is_string());

  if (json.is_array())
  {
    auto& gidData = data.tile_data.emplace<tmx_data::gid_data>();
    for (const auto& [key, value] : json.items())
    {
      gidData.emplace_back(value.get<uint>());
    }
  }
  else if (json.is_string())
  {
    data.tile_data.emplace<tmx_data::base64_data>(json.get<tmx_data::base64_data>());
  }
}

inline void from_json(const nlohmann::json& json, tmx_polygon& polygon)
{
  fill(json, polygon.points);
}

inline void from_json(const nlohmann::json& json, tmx_polyline& line)
{
  fill(json, line.points);
}

inline void from_json(const nlohmann::json& json, tmx_template_object& object)
{
  json.at("template").get_to(object.template_file);
  object.object = std::make_unique<tmx_object>(json.at("object").get<tmx_object>());

  if (const auto it = json.find("tileset"); it != json.end())
  {
    emplace(json, "firstgid", object.tileset_first_id);
    object.tileset_source = json.at("source").get<std::string>();
  }
}

inline void from_json(const nlohmann::json& json, tmx_object& object)
{
  json.at("id").get_to(object.id);
  json.at("x").get_to(object.x);
  json.at("y").get_to(object.y);
  json.at("width").get_to(object.width);
  json.at("height").get_to(object.height);
  json.at("rotation").get_to(object.rotation);
  json.at("name").get_to(object.name);
  json.at("type").get_to(object.type);
  json.at("visible").get_to(object.visible);

  get_if_exists(json, "ellipse", object.is_ellipse);
  get_if_exists(json, "point", object.is_point);

  fill_if_exists(json, "properties", object.properties);

  if (const auto it = json.find("gid"); it != json.end())
  {
    object.data.emplace<tmx_global_id>(it->get<tmx_global_id::value_type>());
  }

  emplace_if_exists<tmx_text>(json, "text", object.data);
  emplace_if_exists<tmx_polygon>(json, "polygon", object.data);
  emplace_if_exists<tmx_polyline>(json, "polyline", object.data);
  emplace_if_exists<tmx_template_object>(json, "template", object.data);
}

inline void from_json(const nlohmann::json& json, tmx_tile_layer& layer)
{
  get_if_exists(json, "compression", layer.compression);
  get_if_exists(json, "encoding", layer.encoding);
  get_if_exists(json, "data", layer.data);

  // TODO
  //  if (json.contains("chunks")) {
  //    m_chunks = detail::fill<std::vector<chunk>>(json, "chunks");
  //  }
}

inline void from_json(const nlohmann::json& json, tmx_image_layer& layer)
{
  json.at("image").get_to(layer.image);
  get_if_exists(json, "transparentcolor", layer.transparent);
}

inline void from_json(const nlohmann::json& json, tmx_object_layer& layer)
{
  fill(json, "objects", layer.objects);
}

inline void from_json(const nlohmann::json& json, tmx_layer& layer)
{
  json.at("type").get_to(layer.type);

  get_if_exists(json, "name", layer.name);
  get_if_exists(json, "opacity", layer.opacity);
  get_if_exists(json, "visible", layer.visible);
  get_if_exists(json, "id", layer.id);
  get_if_exists(json, "width", layer.width);
  get_if_exists(json, "height", layer.height);
  get_if_exists(json, "startx", layer.start_x);
  get_if_exists(json, "starty", layer.start_y);
  get_if_exists(json, "parallaxx", layer.parallax_x);
  get_if_exists(json, "parallaxy", layer.parallax_y);
  get_if_exists(json, "offsetx", layer.offset_x);
  get_if_exists(json, "offsety", layer.offset_y);
  get_if_exists(json, "tintcolor", layer.tint);

  fill_if_exists(json, "properties", layer.properties);

  switch (layer.type)
  {
    default:
      assert(false && "from_json() for tmx_layer is missing branch!");

    case tmx_layer_type::tile_layer:
      layer.data = json.get<tmx_tile_layer>();
      break;

    case tmx_layer_type::object_layer:
      layer.data = json.get<tmx_object_layer>();
      break;

    case tmx_layer_type::image_layer:
      layer.data = json.get<tmx_image_layer>();
      break;

    case tmx_layer_type::group:
      layer.data = json.get<tmx_group>();
      break;
  }
}

inline void from_json(const nlohmann::json& json, tmx_group& group)
{
  const auto& layers = json.at("layers");
  group.layers.reserve(layers.size());
  for (const auto& [key, value] : layers.items())
  {
    group.layers.push_back(std::make_unique<tmx_layer>(value.get<tmx_layer>()));
  }
}

inline void from_json(const nlohmann::json& json, tmx_tile& tile)
{
  emplace(json, "id", tile.id);

  get_if_exists(json, "animation", tile.animation);
  get_if_exists(json, "type", tile.type);
  get_if_exists(json, "image", tile.image);
  get_if_exists(json, "imagewidth", tile.image_width);
  get_if_exists(json, "imageheight", tile.image_height);
  get_if_exists(json, "probability", tile.probability);
  get_if_exists(json, "objectgroup", tile.object_layer);
  fill_if_exists(json, "properties", tile.properties);

  if (const auto it = json.find("terrain"); it != json.end())
  {
    auto& terrain = tile.terrain.emplace();
    for (const auto& [key, value] : it->items())
    {
      terrain.at(std::stoi(key)) = value.get<int>();  // TODO don't use stoi
    }
  }
}

/// \} End of JSON conversions

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_PARSERS_HPP

// #include "rune/tmx/tmx_point.hpp"
#ifndef RUNE_TMX_POINT_HPP
#define RUNE_TMX_POINT_HPP

#include <json.hpp>  // json

namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_point final
{
  float x{};
  float y{};
};

void from_json(const nlohmann::json& json, tmx_point& point);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_POINT_HPP

// #include "rune/tmx/tmx_property.hpp"
#ifndef RUNE_TMX_PROPERTY_HPP
#define RUNE_TMX_PROPERTY_HPP

#include <cassert>      // assert
#include <concepts>     // same_as
#include <json.hpp>     // json
#include <nenya.hpp>    // strong_type
#include <ranges>       // any_of, find_if
#include <string>       // string
#include <string_view>  // string_view
#include <variant>      // variant, get, get_if, holds_alternative
#include <vector>       // vector

// #include "../core/rune_error.hpp"

// #include "tmx_color.hpp"


namespace rune {

/// \cond FALSE
namespace tags {
struct tmx_file_tag;
struct tmx_object_tag;
}  // namespace tags
/// \endcond

/// \addtogroup tmx
/// \{

using tmx_file = nenya::strong_type<std::string, tags::tmx_file_tag>;
using tmx_object_id = nenya::strong_type<int, tags::tmx_object_tag>;

enum class tmx_property_type
{
  string,    ///< For string values, such as `"foo"`.
  integer,   ///< For integer values, e.g. `27`.
  floating,  ///< For floating-point values, e.g. `182.4`.
  boolean,   ///< For the boolean values `true`/`false`.
  color,     ///< For ARGB/RGB colors, i.e. `"#AARRGGBB"` and `"#RRGGBB"`.
  file,      ///< For file paths, e.g. `"some/path/abc.png"`.
  object     ///< For referencing other objects, really just an integer ID.
};

/**
 * \brief Represents a property, with an associated name and value.
 */
struct tmx_property final
{
  using data_type =
      std::variant<std::string, tmx_file, tmx_object_id, tmx_color, int, float, bool>;

  std::string name;
  tmx_property_type type{tmx_property_type::string};
  data_type value;
};

using tmx_properties = std::vector<tmx_property>;

void from_json(const nlohmann::json& json, tmx_property& property);

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_property_type,
                             {{tmx_property_type::string, "string"},
                              {tmx_property_type::integer, "int"},
                              {tmx_property_type::floating, "float"},
                              {tmx_property_type::boolean, "bool"},
                              {tmx_property_type::color, "color"},
                              {tmx_property_type::object, "object"},
                              {tmx_property_type::file, "file"}})

/// \} End of group tmx

namespace tmx {

/// \addtogroup tmx
/// \{

/// \name Non-throwing property value casts
/// \brief Property cast functions that return null pointers upon type mismatches.
/// \{

[[nodiscard]] inline auto try_get(const tmx_properties& properties,
                                  const std::string_view name)
    -> tmx_properties::const_iterator
{
  return std::ranges::find_if(properties, [name](const tmx_property& property) noexcept {
    return property.name == name;
  });
}

[[nodiscard]] inline auto try_get_string(const tmx_property& property) noexcept
    -> const std::string*
{
  return std::get_if<std::string>(&property.value);
}

[[nodiscard]] inline auto try_get_string(const tmx_properties& properties,
                                         const std::string_view name)
    -> const std::string*
{
  if (const auto it = try_get(properties, name); it != properties.end())
  {
    return std::get_if<std::string>(&it->value);
  }
  else
  {
    return nullptr;
  }
}

[[nodiscard]] inline auto try_get_int(const tmx_property& property) noexcept -> const int*
{
  return std::get_if<int>(&property.value);
}

[[nodiscard]] inline auto try_get_int(const tmx_properties& properties,
                                      const std::string_view name) -> const int*
{
  if (const auto it = try_get(properties, name); it != properties.end())
  {
    return std::get_if<int>(&it->value);
  }
  else
  {
    return nullptr;
  }
}

[[nodiscard]] inline auto try_get_float(const tmx_property& property) noexcept -> const
    float*
{
  return std::get_if<float>(&property.value);
}

[[nodiscard]] inline auto try_get_float(const tmx_properties& properties,
                                        const std::string_view name) -> const float*
{
  if (const auto it = try_get(properties, name); it != properties.end())
  {
    return std::get_if<float>(&it->value);
  }
  else
  {
    return nullptr;
  }
}

[[nodiscard]] inline auto try_get_bool(const tmx_property& property) noexcept -> const
    bool*
{
  return std::get_if<bool>(&property.value);
}

[[nodiscard]] inline auto try_get_bool(const tmx_properties& properties,
                                       const std::string_view name) -> const bool*
{
  if (const auto it = try_get(properties, name); it != properties.end())
  {
    return std::get_if<bool>(&it->value);
  }
  else
  {
    return nullptr;
  }
}

[[nodiscard]] inline auto try_get_color(const tmx_property& property) noexcept
    -> const tmx_color*
{
  return std::get_if<tmx_color>(&property.value);
}

[[nodiscard]] inline auto try_get_color(const tmx_properties& properties,
                                        const std::string_view name) -> const tmx_color*
{
  if (const auto it = try_get(properties, name); it != properties.end())
  {
    return std::get_if<tmx_color>(&it->value);
  }
  else
  {
    return nullptr;
  }
}

[[nodiscard]] inline auto try_get_file(const tmx_property& property) noexcept
    -> const tmx_file*
{
  return std::get_if<tmx_file>(&property.value);
}

[[nodiscard]] inline auto try_get_file(const tmx_properties& properties,
                                       const std::string_view name) -> const tmx_file*
{
  if (const auto it = try_get(properties, name); it != properties.end())
  {
    return std::get_if<tmx_file>(&it->value);
  }
  else
  {
    return nullptr;
  }
}

[[nodiscard]] inline auto try_get_object(const tmx_property& property) noexcept
    -> const tmx_object_id*
{
  return std::get_if<tmx_object_id>(&property.value);
}

[[nodiscard]] inline auto try_get_object(const tmx_properties& properties,
                                         const std::string_view name)
    -> const tmx_object_id*
{
  if (const auto it = try_get(properties, name); it != properties.end())
  {
    return std::get_if<tmx_object_id>(&it->value);
  }
  else
  {
    return nullptr;
  }
}

/// \} End of non-throwing property value casts

/// \name Property type indicators
/// \{

// clang-format off

template <typename T>
concept property_value_type = std::same_as<T, int> ||
                              std::same_as<T, float> ||
                              std::same_as<T, bool> ||
                              std::same_as<T, std::string> ||
                              std::same_as<T, tmx_color> ||
                              std::same_as<T, tmx_file> ||
                              std::same_as<T, tmx_object_id>;

// clang-format on

template <property_value_type T>
[[nodiscard]] auto is(const tmx_property& property) noexcept -> bool
{
  return std::holds_alternative<T>(property.value);
}

template <property_value_type T>
[[nodiscard]] auto is(const tmx_properties& properties, const std::string_view name)
    -> bool
{
  if (const auto it = try_get(properties, name); it != properties.end())
  {
    return is<T>(*it);
  }
  else
  {
    return false;
  }
}

[[nodiscard]] inline auto is_string(const tmx_property& property) noexcept -> bool
{
  return is<std::string>(property);
}

[[nodiscard]] inline auto is_string(const tmx_properties& properties,
                                    const std::string_view name) -> bool
{
  return is<std::string>(properties, name);
}

[[nodiscard]] inline auto is_int(const tmx_property& property) noexcept -> bool
{
  return is<int>(property);
}

[[nodiscard]] inline auto is_int(const tmx_properties& properties,
                                 const std::string_view name) -> bool
{
  return is<int>(properties, name);
}

[[nodiscard]] inline auto is_float(const tmx_property& property) noexcept -> bool
{
  return is<float>(property);
}

[[nodiscard]] inline auto is_float(const tmx_properties& properties,
                                   const std::string_view name) -> bool
{
  return is<float>(properties, name);
}

[[nodiscard]] inline auto is_bool(const tmx_property& property) noexcept -> bool
{
  return is<bool>(property);
}

[[nodiscard]] inline auto is_bool(const tmx_properties& properties,
                                  const std::string_view name) -> bool
{
  return is<bool>(properties, name);
}

[[nodiscard]] inline auto is_color(const tmx_property& property) noexcept -> bool
{
  return is<tmx_color>(property);
}

[[nodiscard]] inline auto is_color(const tmx_properties& properties,
                                   const std::string_view name) -> bool
{
  return is<tmx_color>(properties, name);
}

[[nodiscard]] inline auto is_file(const tmx_property& property) noexcept -> bool
{
  return is<tmx_file>(property);
}

[[nodiscard]] inline auto is_file(const tmx_properties& properties,
                                  const std::string_view name) -> bool
{
  return is<tmx_file>(properties, name);
}

[[nodiscard]] inline auto is_object(const tmx_property& property) noexcept -> bool
{
  return is<tmx_object_id>(property);
}

[[nodiscard]] inline auto is_object(const tmx_properties& properties,
                                    const std::string_view name) -> bool
{
  return is<tmx_object_id>(properties, name);
}

/// \} End of property type indicators

/// \name Property value casts
/// \brief Type-safe cast functions for properties, that throw on type mismatches.
/// \{

template <property_value_type T>
[[nodiscard]] auto get(const tmx_property& property) -> const T&
{
  return std::get<T>(property.value);
}

template <property_value_type T>
[[nodiscard]] auto get(const tmx_properties& properties, const std::string_view name)
    -> const T&
{
  if (const auto it = try_get(properties, name); it != properties.end())
  {
    return get<T>(*it);
  }
  else
  {
    throw rune_error{"Could not find property with the specified name!"};
  }
}

[[nodiscard]] inline auto get_string(const tmx_property& property) -> const std::string&
{
  return get<std::string>(property);
}

[[nodiscard]] inline auto get_string(const tmx_properties& properties,
                                     const std::string_view name) -> const std::string&
{
  return get<std::string>(properties, name);
}

[[nodiscard]] inline auto get_int(const tmx_property& property) -> int
{
  return get<int>(property);
}

[[nodiscard]] inline auto get_int(const tmx_properties& properties,
                                  const std::string_view name) -> int
{
  return get<int>(properties, name);
}

[[nodiscard]] inline auto get_float(const tmx_property& property) -> float
{
  return get<float>(property);
}

[[nodiscard]] inline auto get_float(const tmx_properties& properties,
                                    const std::string_view name) -> float
{
  return get<float>(properties, name);
}

[[nodiscard]] inline auto get_bool(const tmx_property& property) -> bool
{
  return get<bool>(property);
}

[[nodiscard]] inline auto get_bool(const tmx_properties& properties,
                                   const std::string_view name) -> bool
{
  return get<bool>(properties, name);
}

[[nodiscard]] inline auto get_color(const tmx_property& property) -> const tmx_color&
{
  return get<tmx_color>(property);
}

[[nodiscard]] inline auto get_color(const tmx_properties& properties,
                                    const std::string_view name) -> const tmx_color&
{
  return get<tmx_color>(properties, name);
}

[[nodiscard]] inline auto get_file(const tmx_property& property) -> const tmx_file&
{
  return get<tmx_file>(property);
}

[[nodiscard]] inline auto get_file(const tmx_properties& properties,
                                   const std::string_view name) -> const tmx_file&
{
  return get<tmx_file>(properties, name);
}

[[nodiscard]] inline auto get_object(const tmx_property& property) -> tmx_object_id
{
  return get<tmx_object_id>(property);
}

[[nodiscard]] inline auto get_object(const tmx_properties& properties,
                                     const std::string_view name) -> tmx_object_id
{
  return get<tmx_object_id>(properties, name);
}

/// \} End of property value casts

/**
 * \brief Indicates whether or not a property with the specified name exists in a vector
 * of properties.
 *
 * \param properties the vector of properties that will be searched.
 * \param name the name of the property to look for.
 *
 * \return `true` if the properties contains a property with the specified name; `false`
 * otherwise.
 */
[[nodiscard]] inline auto contains(const tmx_properties& properties,
                                   const std::string_view name) -> bool
{
  return std::ranges::any_of(properties, [name](const tmx_property& property) noexcept {
    return property.name == name;
  });
}

/**
 * \brief Attempts to find and return a property with the specified name.
 *
 * \param properties the properties that will be searched.
 * \param name the name of the desired property.
 *
 * \return the property with the specified name.
 *
 * \throws rune_error if there is no property with the specified name.
 */
[[nodiscard]] inline auto find(const tmx_properties& properties,
                               const std::string_view name) -> const tmx_property&
{
  if (const auto it = try_get(properties, name); it != properties.end())
  {
    return *it;
  }
  else
  {
    throw rune_error{"Could not find property with specified name!"};
  }
}

/// \} End of group tmx

}  // namespace tmx

}  // namespace rune

#endif  // RUNE_TMX_PROPERTY_HPP

// #include "rune/tmx/tmx_terrain.hpp"
#ifndef RUNE_TMX_TERRAIN_HPP
#define RUNE_TMX_TERRAIN_HPP

#include <json.hpp>  // json
#include <string>    // string

// #include "tmx_local_id.hpp"

// #include "tmx_property.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_terrain final
{
  tmx_local_id tile{};
  std::string name;
  tmx_properties properties;
};

void from_json(const nlohmann::json& json, tmx_terrain& terrain);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_TERRAIN_HPP

// #include "rune/tmx/tmx_text.hpp"
#ifndef RUNE_TMX_TEXT_HPP
#define RUNE_TMX_TEXT_HPP

#include <json.hpp>  // json
#include <string>    // string

// #include "tmx_color.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

enum class tmx_halign
{
  center,
  right,
  left,
  justify
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_halign,
                             {{tmx_halign::center, "center"},
                              {tmx_halign::right, "right"},
                              {tmx_halign::left, "left"},
                              {tmx_halign::justify, "justify"}})

enum class tmx_valign
{
  center,
  top,
  bottom
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_valign,
                             {{tmx_valign::center, "center"},
                              {tmx_valign::top, "top"},
                              {tmx_valign::bottom, "bottom"}})

struct tmx_text final
{
  std::string text;
  std::string family{"sans-serif"};
  tmx_color color;
  tmx_halign horizontal_alignment{tmx_halign::left};
  tmx_valign vertical_alignment{tmx_valign::top};
  int pixel_size{16};
  bool bold{};
  bool italic{};
  bool kerning{true};
  bool strikeout{};
  bool underline{};
  bool wrap{};
};

void from_json(const nlohmann::json& json, tmx_text& text);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_TEXT_HPP

// #include "rune/tmx/tmx_tile.hpp"
#ifndef RUNE_TMX_TILE_HPP
#define RUNE_TMX_TILE_HPP

#include <array>     // array
#include <json.hpp>  // json
#include <optional>  // optional
#include <string>    // string, stoi

// #include "tmx_animation.hpp"

// #include "tmx_layer.hpp"

// #include "tmx_local_id.hpp"

// #include "tmx_property.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_tile final
{
  tmx_local_id id{};
  std::optional<tmx_animation> animation;
  std::optional<std::array<int, 4>> terrain;
  std::optional<std::string> type;
  std::optional<std::string> image;
  std::optional<int> image_width;
  std::optional<int> image_height;
  std::optional<float> probability;
  std::optional<tmx_layer> object_layer;
  tmx_properties properties;
};

void from_json(const nlohmann::json& json, tmx_tile& tile);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_TILE_HPP

// #include "rune/tmx/tmx_tile_layer.hpp"
#ifndef RUNE_TMX_TILE_LAYER_HPP
#define RUNE_TMX_TILE_LAYER_HPP

#include <json.hpp>  // json, NLOHMANN_JSON_SERIALIZE_ENUM
#include <optional>  // optional

// #include "tmx_data.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

enum class tmx_tile_layer_compression
{
  none,
  gzip,
  zlib
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_tile_layer_compression,
                             {{tmx_tile_layer_compression::none, ""},
                              {tmx_tile_layer_compression::gzip, "gzip"},
                              {tmx_tile_layer_compression::zlib, "zlib"}})

enum class tmx_tile_layer_encoding
{
  csv,
  base64
};

NLOHMANN_JSON_SERIALIZE_ENUM(tmx_tile_layer_encoding,
                             {{tmx_tile_layer_encoding::csv, "csv"},
                              {tmx_tile_layer_encoding::base64, "base64"}})

struct tmx_tile_layer final
{
  tmx_tile_layer_compression compression{tmx_tile_layer_compression::none};
  tmx_tile_layer_encoding encoding{tmx_tile_layer_encoding::csv};
  std::optional<tmx_data> data;
  // TODO std::vector<chunk> m_chunks;
};

void from_json(const nlohmann::json& json, tmx_tile_layer& layer);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_TILE_LAYER_HPP

// #include "rune/tmx/tmx_tile_offset.hpp"
#ifndef RUNE_TMX_TILE_OFFSET_HPP
#define RUNE_TMX_TILE_OFFSET_HPP

#include <json.hpp>  // json

namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_tile_offset final
{
  int x{};
  int y{};
};

void from_json(const nlohmann::json& json, tmx_tile_offset& offset);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_TILE_OFFSET_HPP

// #include "rune/tmx/tmx_tileset.hpp"
#ifndef RUNE_TMX_TILESET_HPP
#define RUNE_TMX_TILESET_HPP

#include <json.hpp>  // json
#include <optional>  // optional
#include <string>    // string
#include <vector>    // vector

// #include "tmx_color.hpp"

// #include "tmx_global_id.hpp"

// #include "tmx_grid.hpp"

// #include "tmx_property.hpp"

// #include "tmx_terrain.hpp"

// #include "tmx_tile.hpp"

// #include "tmx_tile_offset.hpp"

// #include "tmx_wang_set.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_tileset final
{
  tmx_global_id first_id{1};
  int tile_width{};
  int tile_height{};
  int tile_count{};
  int column_count{};
  int image_width{};
  int image_height{};
  int margin{};
  int spacing{};
  float json_version{};

  std::string name;
  std::string image;
  std::string external_source;
  std::string tiled_version;

  std::optional<tmx_color> background;
  std::optional<tmx_color> transparent;
  std::optional<tmx_tile_offset> tile_offset;
  std::optional<tmx_grid> grid;

  std::vector<tmx_tile> tiles;
  std::vector<tmx_terrain> terrains;
  std::vector<tmx_wang_set> wang_sets;
  tmx_properties properties;
};

using tmx_tilesets = std::vector<tmx_tileset>;

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_TILESET_HPP

// #include "rune/tmx/tmx_wang_color.hpp"
#ifndef RUNE_TMX_WANG_COLOR_HPP
#define RUNE_TMX_WANG_COLOR_HPP

#include <json.hpp>  // json
#include <string>    // string

// #include "tmx_color.hpp"

// #include "tmx_local_id.hpp"

// #include "tmx_property.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_wang_color final
{
  tmx_local_id tile{};
  tmx_color color;
  std::string name;
  float probability{};
  tmx_properties properties;
};

void from_json(const nlohmann::json& json, tmx_wang_color& color);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_WANG_COLOR_HPP

// #include "rune/tmx/tmx_wang_set.hpp"
#ifndef RUNE_TMX_WANG_SET_HPP
#define RUNE_TMX_WANG_SET_HPP

#include <json.hpp>  // json
#include <string>    // string
#include <vector>    // vector

// #include "tmx_local_id.hpp"

// #include "tmx_property.hpp"

// #include "tmx_wang_color.hpp"

// #include "tmx_wang_tile.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_wang_set final
{
  tmx_local_id tile{};
  std::string name;
  std::vector<tmx_wang_tile> wang_tiles;
  std::vector<tmx_wang_color> colors;
  tmx_properties properties;
};

void from_json(const nlohmann::json& json, tmx_wang_set& set);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_WANG_SET_HPP

// #include "rune/tmx/tmx_wang_tile.hpp"
#ifndef RUNE_TMX_WANG_TILE_HPP
#define RUNE_TMX_WANG_TILE_HPP

#include <array>     // array
#include <json.hpp>  // json

// #include "../aliases/integers.hpp"

// #include "tmx_local_id.hpp"


namespace rune {

/// \addtogroup tmx
/// \{

struct tmx_wang_tile final
{
  tmx_local_id tile{};
  std::array<uint8, 8> indices{};
};

void from_json(const nlohmann::json& json, tmx_wang_tile& tile);

/// \} End of group tmx

}  // namespace rune

#endif  // RUNE_TMX_WANG_TILE_HPP

