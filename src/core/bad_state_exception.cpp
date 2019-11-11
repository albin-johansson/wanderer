#include "bad_state_exception.h"

namespace wanderer::core {

BadStateException::BadStateException() : std::exception() {}

BadStateException::~BadStateException() = default;

}
