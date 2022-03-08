#include "json.hpp"

#include <fstream>  // ifstream
#include <ios>      // ios

#include "wanderer/misc/exception.hpp"

namespace wanderer {

auto read_json(const std::filesystem::path& path) -> nlohmann::json
{
  try {
    std::ifstream stream{path, std::ios::in};

    nlohmann::json json;
    stream >> json;

    return json;
  }
  catch (const std::exception& e) {
    throw_traced(WandererError{e.what()});
  }
}

}  // namespace wanderer