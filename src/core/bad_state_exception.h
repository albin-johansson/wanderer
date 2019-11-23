#pragma once
#include <stdexcept>
#include <string>

namespace albinjohansson::wanderer {

/**
 * The BadStateException class is a subclass of std::exception that represents an exception caused
 * by bad state.
 *
 * @since 0.1.0
 */
class BadStateException final : public std::exception {
 private:
  const char* message;

 public:
  BadStateException();

  explicit BadStateException(const std::string& what);

  explicit BadStateException(const char* what);

  ~BadStateException() override;

  const char* what() const noexcept override;
};

}
