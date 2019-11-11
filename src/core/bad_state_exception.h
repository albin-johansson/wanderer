#pragma once
#include <stdexcept>

namespace wanderer::core {

/**
 * The BadStateException class is a subclass of std::exception that represents an exception caused
 * by bad state.
 *
 * @since 0.1.0
 */
class BadStateException final : public std::exception {
 public:
  BadStateException();

  ~BadStateException() override;
};

}
