#pragma once

#include <string_view>  // string_view

#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/ostream.h>

#include "fmt_specializations.hpp"
#include "wanderer/meta/build.hpp"

namespace wanderer {
namespace logging {

void log_debug(std::string_view fmt, fmt::format_args args);
void log_info(std::string_view fmt, fmt::format_args args);
void log_warn(std::string_view fmt, fmt::format_args args);
void log_error(std::string_view fmt, fmt::format_args args);

}  // namespace logging

template <typename... Args>
void print([[maybe_unused]] const fmt::color color,
           const std::string_view fmt,
           const Args&... args)
{
  if constexpr (is_windows) {
    fmt::print(fmt::runtime(fmt), args...);
  }
  else {
    fmt::print(fmt::fg(color), fmt, args...);
  }
}

template <typename... Args>
void debug(const std::string_view fmt, const Args&... args)
{
  if constexpr (is_debug_build) {
    logging::log_debug(fmt, fmt::make_format_args(args...));
  }
}

template <typename... Args>
void info(const std::string_view fmt, const Args&... args)
{
  logging::log_info(fmt, fmt::make_format_args(args...));
}

template <typename... Args>
void warn(const std::string_view fmt, const Args&... args)
{
  logging::log_warn(fmt, fmt::make_format_args(args...));
}

template <typename... Args>
void error(const std::string_view fmt, const Args&... args)
{
  logging::log_error(fmt, fmt::make_format_args(args...));
}

}  // namespace wanderer
