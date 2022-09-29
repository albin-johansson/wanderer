#pragma once

#include <exception>  // exception

namespace wanderer {

class Error final : public std::exception {
 public:
  explicit Error(const char* what);

  [[nodiscard]] auto what() const noexcept -> const char* override;

 private:
  const char* mWhat {};
};

}  // namespace wanderer
