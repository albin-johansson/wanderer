#include "assert.hpp"

#include <cstdlib>  // abort

#include "boost.hpp"
#include "wanderer/meta/build.hpp"
#include "wanderer/misc/logging.hpp"

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