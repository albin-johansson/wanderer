#ifndef RUNE_RUNE_ERROR_HPP_
#define RUNE_RUNE_ERROR_HPP_

#include <exception>  // exception

namespace rune {

/**
 * \brief The main exception thrown in the library.
 *
 * \ingroup core
 *
 * \since 0.1.0
 */
class rune_error final : public std::exception
{
 public:
  explicit rune_error(const char* what) noexcept : m_what{what}
  {}

  [[nodiscard]] auto what() const noexcept -> const char* override
  {
    return m_what;
  }

 private:
  const char* m_what{"n/a"};
};

}  // namespace rune

#endif  // RUNE_RUNE_ERROR_HPP_
