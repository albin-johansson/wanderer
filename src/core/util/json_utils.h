#pragma once

#include <fstream>

#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

Json parse_json(CZString file);

template <typename T>
Maybe<T> maybe_get(const JsonValue& json, CZString key) noexcept
{
  if (key && json.count(key)) {
    return json.at(key).get<T>();
  } else {
    return nothing;
  }
}

}  // namespace albinjohansson::wanderer