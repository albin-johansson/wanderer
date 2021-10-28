#ifndef RUNE_FROM_STRING_HPP_
#define RUNE_FROM_STRING_HPP_

#include <charconv>      // from_chars
#include <concepts>      // floating_point, integral
#include <optional>      // optional, nullopt
#include <string_view>   // string_view
#include <system_error>  // errc

namespace rune {

/// \addtogroup core
/// \{

template <std::integral T>
[[nodiscard]] auto from_string(const std::string_view str, const int base = 10)
    -> std::optional<T>
{
  T value{};

  const auto [ptr, error] =
      std::from_chars(str.data(), str.data() + str.size(), value, base);
  if (error == std::errc{})
  {
    return value;
  }
  else
  {
    return std::nullopt;
  }
}

template <std::floating_point T>
[[nodiscard]] auto from_string(const std::string_view str) -> std::optional<T>
{
  T value{};

  const auto [ptr, error] = std::from_chars(str.data(), str.data() + str.size(), value);
  if (error == std::errc{})
  {
    return value;
  }
  else
  {
    return std::nullopt;
  }
}

/// \} End of group core

}  // namespace rune

#endif  // RUNE_FROM_STRING_HPP_
