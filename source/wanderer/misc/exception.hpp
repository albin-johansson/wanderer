#pragma once

#include <exception>  // exception

#include "boost.hpp"
#include "wanderer/meta/build.hpp"

namespace wanderer {

class WandererError : public std::exception
{
 public:
  WandererError() noexcept = default;

  explicit WandererError(const char* msg) noexcept : mWhat{msg} {}

  [[nodiscard]] auto what() const noexcept -> const char* override { return mWhat; }

 private:
  const char* mWhat{};
};

using TraceInfo = boost::error_info<struct trace_info_tag, boost::stacktrace::stacktrace>;

template <typename Exception>
[[noreturn]] void throw_traced(const Exception& e)
{
  throw boost::enable_error_info(e) << TraceInfo{boost::stacktrace::stacktrace()};
}

}  // namespace wanderer