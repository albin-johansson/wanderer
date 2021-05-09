#include "parse_layers.hpp"

#include "io/map/parse_object_layer.hpp"
#include "io/map/parse_tile_layer.hpp"

namespace wanderer {

void parse_layers(const rune::tmx_map& map, ir::level& data)
{
  int index{0};
  for (const auto& layer : map.layers)
  {
    if (const auto* tileLayer = rune::tmx::try_get_tile_layer(layer))
    {
      parse_tile_layer(data, map, *tileLayer, layer.properties, index);
    }
    else if (const auto* objectLayer = rune::tmx::try_get_object_layer(layer))
    {
      parse_object_layer(data, map, *objectLayer);
    }

    ++index;
  }
}

}  // namespace wanderer
