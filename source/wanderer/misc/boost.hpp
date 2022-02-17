#pragma once

#include "wanderer/meta/build.hpp"

#if WANDERER_COMPILER_GCC || WANDERER_COMPILER_CLANG
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif  // TACTILE_COMPILER_GCC || TACTILE_COMPILER_CLANG

#include <boost/exception/all.hpp>
#include <boost/stacktrace.hpp>

#if WANDERER_COMPILER_GCC || WANDERER_COMPILER_CLANG
#pragma GCC diagnostic pop
#endif  // TACTILE_COMPILER_GCC || TACTILE_COMPILER_CLANG
