#pragma once

#include <fstream>

#include "wanderer_stdinc.h"

namespace wanderer {

JSON parse_json(CZString file);

template <typename T>
Maybe<T> maybe_get(const JSONValue& json, CZString key) noexcept
{
  if (key && json.count(key)) {
    return json.at(key).get<T>();
  } else {
    return nothing;
  }
}

}  // namespace wanderer