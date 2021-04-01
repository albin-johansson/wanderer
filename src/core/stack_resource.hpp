#pragma once

#include <array>            // array
#include <cstddef>          // byte
#include <memory_resource>  // monotonic_buffer_resource

namespace wanderer {

template <std::size_t size>
class stack_resource final
{
 public:
  [[nodiscard]] auto get() noexcept -> std::pmr::memory_resource*
  {
    return &m_resource;
  }

  [[nodiscard]] auto get() const noexcept -> const std::pmr::memory_resource*
  {
    return &m_resource;
  }

 private:
  std::array<std::byte, size> m_buffer;
  std::pmr::monotonic_buffer_resource m_resource{m_buffer.data(), sizeof m_buffer};
};

}  // namespace wanderer
