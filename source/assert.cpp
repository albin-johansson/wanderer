#include "assert.hpp"

#include <cstdlib>  // abort

#include <boost/stacktrace.hpp>
#include <fmt/ostream.h>

#include "logging.hpp"

namespace boost {

void assertion_failed_msg(const char* expr,
                          const char* msg,
                          const char*,
                          const char* file,
                          const long line)
{
  wanderer::print(fmt::color::orange_red,
                  "{}:{} expression '{}' evaluated to false: {}\n{}",
                  file,
                  line,
                  expr,
                  msg ? msg : "n/a",
                  stacktrace::stacktrace{});
  std::abort();
}

}  // namespace boost