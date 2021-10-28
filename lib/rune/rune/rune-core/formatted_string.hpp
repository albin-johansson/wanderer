#ifndef RUNE_FORMATTED_STRING_HPP_
#define RUNE_FORMATTED_STRING_HPP_

#include <array>        // array
#include <cstddef>      // size_t
#include <format>       // format_to_n
#include <string_view>  // string_view

namespace rune {

template <std::size_t Capacity>
class formatted_string final
{
 public:
  template <typename... Args>
  explicit formatted_string(const std::string_view fmt, const Args&... args)
  {
    const auto res = std::format_to_n(m_buffer.data(), m_buffer.size() - 1, fmt, args...);
    *res.out = '\0';
    m_view = std::string_view{m_buffer.data(), res.out};
  }

  [[nodiscard]] auto data() const noexcept -> const char*
  {
    return m_buffer.data();
  }

  [[nodiscard]] auto view() const noexcept -> std::string_view
  {
    return m_view;
  }

  [[nodiscard]] auto size() const noexcept -> std::size_t
  {
    return m_view.size();
  }

  [[nodiscard]] constexpr auto capacity() const noexcept -> std::size_t
  {
    return Capacity;
  }

 private:
  std::array<char, Capacity + 1> m_buffer;  // NOLINT
  std::string_view m_view;
};

using fmt_string = formatted_string<128>;

}  // namespace rune

#endif  // RUNE_FORMATTED_STRING_HPP_
