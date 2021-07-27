#include "parse_object_layer.hpp"

#include <cassert>  // assert

#include "core/utils/centurion_utils.hpp"
#include "io/parsing/common.hpp"
#include "io/parsing/objects/parse_container.hpp"
#include "io/parsing/objects/parse_hitbox.hpp"
#include "io/parsing/objects/parse_light.hpp"
#include "io/parsing/objects/parse_plant.hpp"
#include "io/parsing/objects/parse_portal.hpp"
#include "io/parsing/objects/parse_spawnpoint.hpp"

namespace wanderer::io {

void parse_object_layer(ir::level& data,
                        const rune::tmx_map& map,
                        const rune::tmx_object_layer& objectLayer)
{
  for (const auto& object : objectLayer.objects)
  {
    auto& objectData = data.objects.emplace_back();
    objectData.id = object.id;

    const auto type = object.type;
    if (type == "Spawnpoint")
    {
      objectData.spawnpoint = parse_spawnpoint(object, data.x_ratio, data.y_ratio);
      if (objectData.spawnpoint->type == comp::spawnpoint_type::player)
      {
        data.player_spawn_point = objectData.spawnpoint->position;
      }
    }
    else if (type == "Container")
    {
      objectData.inventory = parse_container(object);
    }
    else if (type == "ContainerTrigger")
    {
      assert(rune::tmx::is_object(object.properties, "container"));
      objectData.inventory_ref =
          rune::tmx::get_object(object.properties, "container").get();
      objectData.hitbox = parse_hitbox(object, data.x_ratio, data.y_ratio);
    }
    else if (type == "BedTrigger")
    {
      objectData.bed_trigger.emplace();
      objectData.hitbox = parse_hitbox(object, data.x_ratio, data.y_ratio);
    }
    else if (type == "Portal")
    {
      objectData.portal = parse_portal(object);
      objectData.hitbox = parse_hitbox(object, data.x_ratio, data.y_ratio);
    }
    else if (type == "Light")
    {
      objectData.light = parse_light(object, data.x_ratio, data.y_ratio);
    }
    else if (type == "Plant")
    {
      objectData.plant = parse_plant(data, object);

      const cen::fpoint pos{object.x * data.x_ratio, object.y * data.y_ratio};
      const cen::farea size{object.width * data.x_ratio, object.height * data.y_ratio};

      const auto tileId = objectData.plant->tiles.at(0);
      const auto tile = find_tile(data.tilesets, tileId).value();

      objectData.drawable = make_depth_drawable(tile, pos, size, data.humanoid_layer);
    }
  }
}

}  // namespace wanderer::io
