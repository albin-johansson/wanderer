#include "bad_state_exception.h"

namespace wanderer::core {

BadStateException::BadStateException() : BadStateException("N/A") {}

BadStateException::BadStateException(const std::string& w) : BadStateException(w.c_str()) {}

BadStateException::BadStateException(const char* what) {
  message = what;
}

const char* BadStateException::what() const noexcept {
  return message;
}

BadStateException::~BadStateException() = default;

}
