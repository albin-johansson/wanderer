#include "parse_layers.hpp"

#include "parse_object_layer.hpp"
#include "parse_tile_layer.hpp"

namespace wanderer {

void parse_layers(const step::map& stepMap, ir::level& data)
{
  int index{0};
  for (const auto& stepLayer : stepMap.layers()) {
    const auto* props = stepLayer.get_properties();

    if (const auto* tileLayer = stepLayer.try_as<step::tile_layer>()) {
      parse_tile_layer(data, stepMap, *tileLayer, props, index);

    } else if (const auto* objLayer = stepLayer.try_as<step::object_group>()) {
      parse_object_layer(data, stepMap, *objLayer);
    }

    ++index;
  }
}

}  // namespace wanderer
