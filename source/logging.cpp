#include "logging.hpp"

#include <ctime>  // time

#include <fmt/chrono.h>

namespace wanderer::logging {
namespace {

void log_impl(const fmt::color color,
              const std::string_view category,
              const std::string_view fmt,
              const fmt::format_args args)
{
  const auto msg = fmt::vformat(fmt, args);

  const auto time = fmt::localtime(std::time(nullptr));
  const auto full = fmt::vformat("{:>9} {:%H:%M:%S} > {}\n",
                                 fmt::make_format_args(category, time, msg));

  fmt::print(fmt::fg(color), "{}", full);
}

}  // namespace

void log_debug(const std::string_view fmt, const fmt::format_args args)
{
  log_impl(fmt::color::aquamarine, "[debug]", fmt, args);
}

void log_info(const std::string_view fmt, const fmt::format_args args)
{
  log_impl(fmt::color::floral_white, "[info]", fmt, args);
}

void log_warn(const std::string_view fmt, const fmt::format_args args)
{
  log_impl(fmt::color::yellow, "[warn]", fmt, args);
}

void log_error(const std::string_view fmt, const fmt::format_args args)
{
  log_impl(fmt::color::orange_red, "[error]", fmt, args);
}

}  // namespace wanderer::logging