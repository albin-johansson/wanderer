#include "parse_object_layer.hpp"

#include <cassert>    // assert
#include <stdexcept>  // runtime_error

#include "systems/movement/hitbox_system.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto make_hitbox(const step::object& object,
                               const float xRatio,
                               const float yRatio) -> comp::hitbox
{
  const cen::farea size{static_cast<float>(object.width()) * xRatio,
                        static_cast<float>(object.height()) * yRatio};
  const comp::subhitbox subhitbox{{}, size};

  auto hitbox = sys::create_hitbox({subhitbox});
  hitbox.enabled = false;

  const float2 pos{static_cast<float>(object.x()) * xRatio,
                   static_cast<float>(object.y()) * yRatio};
  sys::set_position(hitbox, pos);

  return hitbox;
}

[[nodiscard]] auto get_spawnpoint_entity(const step::properties& props)
    -> comp::spawnpoint_type
{
  if (props.is("entity", "player"))
  {
    return comp::spawnpoint_type::player;
  }
  else if (props.is("entity", "skeleton"))
  {
    return comp::spawnpoint_type::skeleton;
  }
  else
  {
    throw std::runtime_error{"Did not recognize spawnpoint type!"};
  }
}

[[nodiscard]] auto parse_spawnpoint(const step::object& stepObject,
                                    const float xRatio,
                                    const float yRatio) -> comp::spawnpoint
{
  const float2 position{static_cast<float>(stepObject.x()) * xRatio,
                        static_cast<float>(stepObject.y()) * yRatio};

  const auto* props = stepObject.get_properties();
  assert(props);
  assert(props->has("entity"));
  assert(props->get("entity").is<std::string>());

  comp::spawnpoint spawnpoint;

  spawnpoint.position = position;
  spawnpoint.type = get_spawnpoint_entity(*props);

  return spawnpoint;
}

[[nodiscard]] auto parse_portal(const step::object& stepObject) -> comp::portal
{
  const auto* props = stepObject.get_properties();
  assert(props);
  assert(props->has("target"));
  assert(props->get("target").is<int>());
  assert(props->has("path"));
  assert(props->get("path").is<step::file>());

  comp::portal portal;

  portal.path = props->get("path").get<step::file>().get();
  portal.target = map_id{props->get("target").get<int>()};

  return portal;
}

[[nodiscard]] auto parse_container(const step::object& stepObject) -> comp::inventory
{
  const auto* props = stepObject.get_properties();
  assert(props);
  assert(props->has("capacity"));
  assert(props->get("capacity").is<int>());
  assert(props->has("hasRandomLoot"));
  assert(props->get("hasRandomLoot").is<bool>());

  comp::inventory inventory;

  inventory.capacity = props->get("capacity").get<int>();
  inventory.items.reserve(inventory.capacity);

  if (props->get("hasRandomLoot").get<bool>())
  {
    // TODO
  }

  return inventory;
}

[[nodiscard]] auto parse_container_trigger(const step::object& object) -> int
{
  const auto* props = object.get_properties();
  assert(props);
  assert(props->has("container"));
  assert(props->get("container").is<step::object_ref>());

  return props->get("container").get<step::object_ref>().get();
}

[[nodiscard]] auto parse_light(const step::object& object,
                               const float xRatio,
                               const float yRatio) -> comp::point_light
{
  assert(object.is_ellipse());

  comp::point_light light;

  light.size = static_cast<float>(object.width()) * xRatio;

  const auto x = static_cast<float>(object.x()) * xRatio;
  const auto y = static_cast<float>(object.y()) * yRatio;

  light.position.x = x + (light.size / 2.0f);
  light.position.y = y + (light.size / 2.0f);

  light.fluctuationLimit = 5;
  light.fluctuationStep = 1;
  light.fluctuation = 0;

  if (const auto* props = object.get_properties())
  {
    if (props->has("fluctuationLimit"))
    {
      light.fluctuationLimit = props->get("fluctuationLimit").get<float>();
    }

    if (props->has("fluctuationStep"))
    {
      light.fluctuationStep = props->get("fluctuationStep").get<float>();
    }
  }

  return light;
}

}  // namespace

void parse_object_layer(ir::level& data,
                        const step::map& stepMap,
                        const step::object_group& group)
{
  for (const auto& stepObject : group.objects())
  {
    auto& objectData = data.objects.emplace_back();
    objectData.id = stepObject.id();

    const auto type = stepObject.type();
    if (type == "Spawnpoint")
    {
      objectData.spawnpoint = parse_spawnpoint(stepObject, data.xRatio, data.yRatio);

      if (objectData.spawnpoint->type == comp::spawnpoint_type::player)
      {
        data.playerSpawnPoint = objectData.spawnpoint->position;
      }
    }
    else if (type == "Portal")
    {
      objectData.portal = parse_portal(stepObject);
      objectData.hitbox = make_hitbox(stepObject, data.xRatio, data.yRatio);
    }
    else if (type == "Container")
    {
      objectData.inventory = parse_container(stepObject);
    }
    else if (type == "ContainerTrigger")
    {
      objectData.inventoryRef = parse_container_trigger(stepObject);
      objectData.hitbox = make_hitbox(stepObject, data.xRatio, data.yRatio);
    }
    else if (type == "Light")
    {
      objectData.light = parse_light(stepObject, data.xRatio, data.yRatio);
    }
  }
}

}  // namespace wanderer
