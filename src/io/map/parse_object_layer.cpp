#include "parse_object_layer.hpp"

#include <cassert>    // assert
#include <stdexcept>  // runtime_error

#include "core/game_constants.hpp"
#include "systems/movement/hitbox_system.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto make_hitbox(const rune::tmx_object& object,
                               const float xRatio,
                               const float yRatio) -> comp::hitbox
{
  const cen::farea size{object.width * xRatio, object.height * yRatio};
  const comp::subhitbox subhitbox{{}, size};

  auto hitbox = sys::make_hitbox({subhitbox});
  hitbox.enabled = false;

  const float2 pos{object.x * xRatio, object.y * yRatio};
  sys::set_position(hitbox, pos);

  return hitbox;
}

[[nodiscard]] auto get_spawnpoint_entity(const rune::tmx_properties& properties)
    -> comp::spawnpoint_type
{
  assert(rune::tmx::is_string(properties, "entity"));
  const auto entity = rune::tmx::get_string(properties, "entity");
  if (entity == "player")
  {
    return comp::spawnpoint_type::player;
  }
  else if (entity == "skeleton")
  {
    return comp::spawnpoint_type::skeleton;
  }
  else
  {
    throw std::runtime_error{"Did not recognize spawnpoint type!"};
  }
}

[[nodiscard]] auto parse_spawnpoint(const rune::tmx_object& object,
                                    const float xRatio,
                                    const float yRatio) -> comp::spawnpoint
{
  comp::spawnpoint spawnpoint;

  spawnpoint.position = float2{object.x * xRatio, object.y * yRatio};
  spawnpoint.type = get_spawnpoint_entity(object.properties);

  // TODO only do this for humanoids, when animals are added
  spawnpoint.position.x -= glob::humanoid_draw_width / 2.0f;
  spawnpoint.position.y -= glob::humanoid_draw_height / 2.0f;

  return spawnpoint;
}

[[nodiscard]] auto parse_portal(const rune::tmx_object& object) -> comp::portal
{
  assert(rune::tmx::is_int(object.properties, "target"));
  assert(rune::tmx::is_file(object.properties, "path"));

  comp::portal portal;

  portal.path = rune::tmx::get_file(object.properties, "path").get();
  portal.target = map_id{rune::tmx::get_int(object.properties, "target")};

  return portal;
}

[[nodiscard]] auto parse_container(const rune::tmx_object& object) -> comp::inventory
{
  assert(rune::tmx::is_int(object.properties, "capacity"));
  assert(rune::tmx::is_bool(object.properties, "hasRandomLoot"));

  comp::inventory inventory;

  inventory.capacity = rune::tmx::get_int(object.properties, "capacity");
  inventory.items.reserve(inventory.capacity);

  if (rune::tmx::get_bool(object.properties, "hasRandomLoot"))
  {
    // TODO
  }

  return inventory;
}

[[nodiscard]] auto parse_container_trigger(const rune::tmx_object& object) -> int
{
  assert(rune::tmx::is_object(object.properties, "container"));
  return rune::tmx::get_object(object.properties, "container").get();
}

[[nodiscard]] auto parse_light(const rune::tmx_object& object,
                               const float xRatio,
                               const float yRatio) -> comp::point_light
{
  assert(object.is_ellipse);

  comp::point_light light;

  light.size = object.width * xRatio;

  const auto x = object.x * xRatio;
  const auto y = object.y * yRatio;

  light.position.x = x + (light.size / 2.0f);
  light.position.y = y + (light.size / 2.0f);

  light.fluctuation_limit = 5;
  light.fluctuation_step = 1;
  light.fluctuation = 0;

  if (const auto* limit = rune::tmx::try_get_float(object.properties, "fluctuationLimit"))
  {
    light.fluctuation_limit = *limit;
  }

  if (const auto* step = rune::tmx::try_get_float(object.properties, "fluctuationStep"))
  {
    light.fluctuation_step = *step;
  }

  return light;
}

}  // namespace

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
    else if (type == "Portal")
    {
      objectData.portal = parse_portal(object);
      objectData.hitbox = make_hitbox(object, data.x_ratio, data.y_ratio);
    }
    else if (type == "Container")
    {
      objectData.inventory = parse_container(object);
    }
    else if (type == "ContainerTrigger")
    {
      objectData.inventory_ref = parse_container_trigger(object);
      objectData.hitbox = make_hitbox(object, data.x_ratio, data.y_ratio);
    }
    else if (type == "Light")
    {
      objectData.light = parse_light(object, data.x_ratio, data.y_ratio);
    }
  }
}

}  // namespace wanderer
