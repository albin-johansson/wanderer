#include "parse_tile_layer.hpp"

#include <cassert>  // assert
#include <variant>  // get

#include <rune/everything.hpp>  // index_to_matrix

#include "core/utils/centurion_utils.hpp"
#include "io/tmx/common.hpp"
#include "io/tmx/tiles/parse_ground_layer.hpp"
#include "io/tmx/tiles/parse_tile_objects.hpp"
#include "systems/physics/hitbox_system.hpp"

namespace wanderer::io {

void parse_tile_layer(ir::level& data,
                      const rune::tmx_map& map,
                      const rune::tmx_tile_layer& layer,
                      const rune::tmx_properties& properties,
                      const int layerIndex)
{
  assert(rune::tmx::is_bool(properties, "ground"));
  if (rune::tmx::get_bool(properties, "ground")) {
    data.ground_layers.push_back(
        parse_ground_layer(layer, map.height, map.width, layerIndex));
  }
  else if (layer.data) {
    parse_tile_objects(data, std::get<tile_data>(layer.data->tile_data), layerIndex);
  }
}

}  // namespace wanderer::io
