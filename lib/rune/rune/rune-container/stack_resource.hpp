#ifndef RUNE_STACK_RESOURCE_HPP_
#define RUNE_STACK_RESOURCE_HPP_

#include <array>            // array
#include <cstddef>          // byte, size_t
#include <memory_resource>  // memory_resource, monotonic_buffer_resource

namespace rune {

/// \addtogroup containers
/// \{

/**
 * \brief Represents a buffer of stack memory, for avoiding dynamic memory allocations.
 *
 * \details The following is an example of you can use this class.
 * \code{cpp}
 *   rune::stack_resource<128> resource;
 *   std::pmr::vector<int> vector{resource.get()};
 * \endcode
 *
 * \tparam size the size of the stack buffer.
 */
template <std::size_t Size>
class stack_resource final
{
 public:
  /// \brief Returns the associated memory resource
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
  std::pmr::monotonic_buffer_resource m_resource{m_buffer.data(), m_buffer.size()};
};

/// \} End of group containers

}  // namespace rune

#endif  // RUNE_STACK_RESOURCE_HPP_
