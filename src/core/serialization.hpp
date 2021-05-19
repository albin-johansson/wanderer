#pragma once

#include <cereal/archives/binary.hpp>  // BinaryOutputArchive, BinaryInputArchive

// Include some common type serializers
#include <cereal/types/array.hpp>
#include <cereal/types/chrono.hpp>
#include <cereal/types/optional.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/vector.hpp>

namespace wanderer {

/// \addtogroup core
/// \{

using input_archive = cereal::BinaryInputArchive;
using output_archive = cereal::BinaryOutputArchive;

template <typename T, typename Archive>
[[nodiscard]] auto restore(Archive& archive) -> T
{
  T obj;
  archive(obj);
  return obj;
}

/// \} End of group core

}  // namespace wanderer
