#pragma once

#include <centurion.hpp>
#include <fmt/format.h>
#include <glm/glm.hpp>

namespace fmt {

template <typename T>
struct formatter<cen::basic_point<T>>
{
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx) -> decltype(ctx.begin())
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const cen::basic_point<T>& point, FormatContext& ctx) -> decltype(ctx.out())
  {
    return format_to(ctx.out(), "({}, {})", point.x(), point.y());
  }
};

template <typename T>
struct formatter<cen::basic_area<T>>
{
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx) -> decltype(ctx.begin())
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const cen::basic_area<T>& area, FormatContext& ctx) -> decltype(ctx.out())
  {
    return format_to(ctx.out(), "({}, {})", area.width, area.height);
  }
};

template <typename T>
struct formatter<cen::basic_rect<T>>
{
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx) -> decltype(ctx.begin())
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const cen::basic_rect<T>& rect, FormatContext& ctx) -> decltype(ctx.out())
  {
    return format_to(ctx.out(),
                     "({}, {}, {}, {})",
                     rect.x(),
                     rect.y(),
                     rect.width(),
                     rect.height());
  }
};

template <typename T>
struct formatter<glm::vec<2, T>>
{
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx) -> decltype(ctx.begin())
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const glm::vec<2, T>& vec, FormatContext& ctx) -> decltype(ctx.out())
  {
    return format_to(ctx.out(), "({}, {})", vec.x, vec.y);
  }
};

template <typename T>
struct formatter<glm::vec<3, T>>
{
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx) -> decltype(ctx.begin())
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const glm::vec<3, T>& vec, FormatContext& ctx) -> decltype(ctx.out())
  {
    return format_to(ctx.out(), "({}, {}, {})", vec.x, vec.y, vec.z);
  }
};

template <typename T>
struct formatter<glm::vec<4, T>>
{
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx) -> decltype(ctx.begin())
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const glm::vec<4, T>& vec, FormatContext& ctx) -> decltype(ctx.out())
  {
    return format_to(ctx.out(), "({}, {}, {}, {})", vec.x, vec.y, vec.z, vec.w);
  }
};

}  // namespace fmt
