#include "parse_layers.hpp"

#include "io/parsing/objects/parse_object_layer.hpp"
#include "io/parsing/tiles/parse_tile_layer.hpp"

namespace wanderer::io {

void parse_layers(const rune::tmx_map& map, ir::level& data)
{
  /* We parse tile layers and objects layers separately in order to guarantee that the
     tile data is available once the objects are parsed, since that makes our life a
     little easier. */

  int index = 0;

  for (const auto& layer : map.layers)
  {
    if (const auto* tileLayer = rune::tmx::try_get_tile_layer(layer))
    {
      parse_tile_layer(data, map, *tileLayer, layer.properties, index);
    }

    ++index;
  }

  for (const auto& layer : map.layers)
  {
    if (const auto* objectLayer = rune::tmx::try_get_object_layer(layer))
    {
      parse_object_layer(data, map, *objectLayer);
    }

    ++index;
  }
}

}  // namespace wanderer::io
