#include "csv.hpp"

#include <sstream>  // istringstream
#include <utility>  // move

namespace wanderer::io {

auto parse_csv(const std::string& str) -> std::vector<std::string>
{
  std::vector<std::string> tokens;

  std::istringstream stream{str};
  std::string token;
  while (std::getline(stream, token, ',')) {
    tokens.push_back(std::move(token));
    token.clear();
  }

  return tokens;
}

}  // namespace wanderer::io
