#include "json_utils.h"

namespace wanderer {

JSON parse_json(CZString file)
{
  std::ifstream stream{file};
  JSON json;
  stream >> json;
  return json;
}

}  // namespace wanderer