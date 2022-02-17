#include "json.hpp"

#include <fstream>  // ifstream
#include <ios>      // ios

namespace wanderer {

auto read_json(const std::filesystem::path& path) -> nlohmann::json
{
  std::ifstream stream{path, std::ios::in};

  nlohmann::json json;
  stream >> json;

  return json;
}

}  // namespace wanderer