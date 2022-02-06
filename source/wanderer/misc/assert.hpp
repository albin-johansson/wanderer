#pragma once

#include <boost/assert.hpp>

#include "wanderer/meta/build.hpp"

#if WANDERER_DEBUG_BUILD

#define WANDERER_ASSERT(Expr) BOOST_ASSERT(Expr)
#define WANDERER_ASSERT_MSG(Expr, Msg) BOOST_ASSERT_MSG(Expr, Msg)

#else

#define WANDERER_ASSERT(Expr)
#define WANDERER_ASSERT_MSG(Expr, Msg)

#endif  // WANDERER_DEBUG_BUILD

namespace boost {

inline void assertion_failed(const char* expr,
                             const char* function,
                             const char* file,
                             const long line)
{
  assertion_failed_msg(expr, nullptr, function, file, line);
}

}  // namespace boost