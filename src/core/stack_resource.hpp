#pragma once

#include <array>            // array
#include <cstddef>          // byte, size_t
#include <memory_resource>  // monotonic_buffer_resource

namespace wanderer {

/**
 * \brief Represents a buffer of stack memory, for avoiding dynamic memory allocations.
 *
 * \ingroup core
 *
 * \tparam size the size of the stack buffer.
 */
template <std::size_t Size>
class stack_resource final
{
 public:
  /// Returns the associated memory resource
  [[nodiscard]] auto get() noexcept -> std::pmr::memory_resource*
  {
    return &m_resource;
  }

  /// \copydoc get()
  [[nodiscard]] auto get() const noexcept -> const std::pmr::memory_resource*
  {
    return &m_resource;
  }

 private:
  std::array<std::byte, Size> m_buffer;
  std::pmr::monotonic_buffer_resource m_resource{m_buffer.data(), sizeof m_buffer};
};

}  // namespace wanderer
