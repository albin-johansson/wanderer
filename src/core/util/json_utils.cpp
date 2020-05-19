#include "json_utils.h"

namespace albinjohansson::wanderer {

Json parse_json(CZString file)
{
  std::ifstream stream{file};
  Json json;
  stream >> json;
  return json;
}

}  // namespace albinjohansson::wanderer