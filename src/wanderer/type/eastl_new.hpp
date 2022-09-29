#pragma once

/// This header defines required overloads of operator new[], used by EASTL.

#include <cstddef>  // size_t, byte
#include <new>      // align_val_t

inline auto operator new[](const std::size_t size,
                           const char* /* p_name */,
                           int /* flags */,
                           unsigned /* debug_flags */,
                           const char* /* file */,
                           int /* line */) -> void*
{
  return new std::byte[size];
}

inline auto operator new[](const std::size_t size,
                           const std::size_t alignment,
                           std::size_t /* alignment_offset */,
                           const char* /* p_name */,
                           int /* flags */,
                           unsigned /* debug_flags */,
                           const char* /* file */,
                           int /* line */) -> void*
{
  return new (std::align_val_t {alignment}) std::byte[size];
}
