#pragma once

#include <exception>  // exception

#include "boost.hpp"
#include "wanderer/meta/build.hpp"

namespace wanderer {

class wanderer_error : public std::exception
{
 public:
  wanderer_error() noexcept = default;

  explicit wanderer_error(const char* msg) noexcept : mWhat{msg} {}

  [[nodiscard]] auto what() const noexcept -> const char* override { return mWhat; }

 private:
  const char* mWhat{};
};

using trace_info =
    boost::error_info<struct trace_info_tag, boost::stacktrace::stacktrace>;

template <typename Exception>
[[noreturn]] void throw_traced(const Exception& e)
{
  throw boost::enable_error_info(e) << trace_info{boost::stacktrace::stacktrace()};
}

}  // namespace wanderer