#pragma once
#include <stdexcept>
#include <string>

namespace albinjohansson::wanderer {

/**
 * The BadStateException class is a subclass of std::exception that represents an exception caused
 * by some kind of bad state.
 *
 * @since 0.1.0
 */
class BadStateException final : public std::exception {
 private:
  const char* message = nullptr;

 public:
  /**
   * @since 0.1.0
   */
  BadStateException();

  /**
   * @param what the error message.
   * @since 0.1.0
   */
  explicit BadStateException(const std::string& what);

  /**
   * @param what the error message.
   * @since 0.1.0
   */
  explicit BadStateException(const char* what);

  ~BadStateException() override;

  [[nodiscard]] const char* what() const noexcept override;
};

}
