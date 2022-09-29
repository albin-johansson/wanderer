#include "string.hpp"

namespace wanderer {

auto from_std(std::string_view str) -> String
{
  String res;
  res.reserve(str.size());

  for (const auto ch : str) {
    res.push_back(ch);
  }

  return res;
}

}  // namespace wanderer