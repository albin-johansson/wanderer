#include "bad_state_exception.h"
#include <utility>

namespace albinjohansson::wanderer {

BadStateException::BadStateException() : BadStateException("N/A") {}

BadStateException::BadStateException(const std::string& what) : message(what) {}

BadStateException::BadStateException(std::string&& what) : message(what) {}

BadStateException::BadStateException(const char* what) : message(what) {}

const char* BadStateException::what() const noexcept {
  return message.c_str();
}

BadStateException::~BadStateException() = default;

}
