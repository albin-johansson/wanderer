#include "parse_layers.hpp"

#include "io/map/parse_object_layer.hpp"
#include "io/map/parse_tile_layer.hpp"

namespace wanderer {

void parse_layers(const rune::tmx_map& map, ir::level& data)
{
  int index{0};
  for (const auto& layer : map.layers)
  {
    const auto& properties = layer.properties;

    // TODO rune::tmx::try_as_tile_layer(layer)

    if (rune::tmx::is_tile_layer(layer))
    {
      const auto& tileLayer = rune::tmx::get_tile_layer(layer);
      parse_tile_layer(data, map, tileLayer, properties, index);
    }
    else if (rune::tmx::is_object_layer(layer))
    {
      const auto& objectLayer = rune::tmx::get_object_layer(layer);
      parse_object_layer(data, map, objectLayer);
    }

    ++index;
  }
}

}  // namespace wanderer
