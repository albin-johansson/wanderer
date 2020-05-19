#pragma once
#include <exception>
#include <string>

namespace albinjohansson::wanderer {

class WandererException : public std::exception {
 public:
  WandererException() noexcept
  {}

  explicit WandererException(std::string what) : m_what{std::move(what)}
  {}

  ~WandererException() override = default;

  const char* what() const noexcept override
  {
    return m_what.c_str();
  }

 private:
  std::string m_what = "N/A";
};

}  // namespace albinjohansson::wanderer