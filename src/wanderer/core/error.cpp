#include "error.hpp"

namespace wanderer {

Error::Error(const char* what)
    : mWhat {what ? what : "N/A"}
{
}

auto Error::what() const noexcept -> const char*
{
  return mWhat;
}

}  // namespace wanderer