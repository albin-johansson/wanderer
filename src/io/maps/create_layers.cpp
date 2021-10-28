#include "create_layers.hpp"

#include "create_object_layer.hpp"
#include "create_tile_layer.hpp"

namespace wanderer {

void CreateLayers(const Tactile::IO::Map& irMap,
                  comp::Level& level,
                  GraphicsContext& graphics)
{
  /* We parse tile layers and objects layers separately in order to guarantee that the
     tile data is available once the objects are parsed, since that makes our lives a
     little easier. */

  Tactile::IO::EachLayer(irMap,
                         [&, index = 0](const Tactile::IO::Layer& irLayer) mutable {
                           if (Tactile::IO::IsTileLayer(irLayer)) {
                             CreateTileLayer(irMap, irLayer, level, index);
                             ++index;
                           }
                         });

  const float2 ratio = {
      glob::tile_width<float> / static_cast<float>(Tactile::IO::GetTileWidth(irMap)),
      glob::tile_height<float> / static_cast<float>(Tactile::IO::GetTileHeight(irMap))};

  Tactile::IO::EachLayer(irMap, [&](const Tactile::IO::Layer& irLayer) {
    if (Tactile::IO::IsObjectLayer(irLayer)) {
      CreateObjectLayer(irMap, irLayer, level, graphics, ratio);
    }
  });
}

}  // namespace wanderer