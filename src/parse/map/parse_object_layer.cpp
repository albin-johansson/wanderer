#include "parse_object_layer.hpp"

#include <stdexcept>  // runtime_error

#include "container_trigger.hpp"
#include "hitbox.hpp"
#include "hitbox_system.hpp"
#include "object.hpp"
#include "portal.hpp"
#include "spawnpoint.hpp"
#include "vector2.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto get_spawnpoint_entity(const step::properties& props)
{
  if (props.is("entity", "player")) {
    return comp::spawnpoint_type::player;
  } else if (props.is("entity", "skeleton")) {
    return comp::spawnpoint_type::skeleton;
  } else {
    throw std::runtime_error{"Did not recognize spawnpoint type!"};
  }
}

[[nodiscard]] auto make_simple_hitbox(const step::object& object)
    -> comp::hitbox
{
  const cen::farea size{static_cast<float>(object.width()),
                        static_cast<float>(object.height())};
  const comp::subhitbox subhitbox{{}, size};

  auto hitbox = sys::hitbox::create({subhitbox});
  hitbox.enabled = false;

  const vector2f pos{static_cast<float>(object.x()),
                     static_cast<float>(object.y())};
  sys::hitbox::set_position(hitbox, pos);

  return hitbox;
}

void parse_spawnpoint(entt::registry& registry,
                      const comp::object::entity entity,
                      const step::object& object)
{
  const auto* props = object.get_properties();
  assert(props);
  assert(props->has("entity"));
  assert(props->get("entity").is<std::string>());

  const vector2f position{static_cast<float>(object.x()),
                          static_cast<float>(object.y())};

  registry.emplace<comp::spawnpoint>(entity,
                                     get_spawnpoint_entity(*props),
                                     position);
}

void parse_portal(entt::registry& registry,
                  const comp::object::entity entity,
                  const step::object& object)
{
  const auto* props = object.get_properties();
  assert(props);
  assert(props->has("target"));
  assert(props->get("target").is<int>());
  assert(props->has("path"));
  assert(props->get("path").is<step::file>());

  auto& portal = registry.emplace<comp::portal>(entity);
  portal.target = map_id{props->get("target").get<int>()};
  portal.path = props->get("path").get<step::file>().get();

  registry.emplace<comp::hitbox>(entity, make_simple_hitbox(object));
}

void parse_container(entt::registry& registry,
                     const comp::object::entity entity,
                     const step::object& object)
{
  const auto* props = object.get_properties();
  assert(props);
  assert(props->has("capacity"));
  assert(props->get("capacity").is<int>());
  assert(props->has("hasRandomLoot"));
  assert(props->get("hasRandomLoot").is<bool>());

  auto& inventory = registry.emplace<comp::inventory>(entity);
  inventory.capacity = props->get("capacity").get<int>();

  if (props->get("hasRandomLoot").get<bool>()) {
    // TODO
  }
}

void parse_container_trigger(entt::registry& registry,
                             const comp::object::entity entity,
                             const step::object& object)
{
  const auto* props = object.get_properties();
  assert(props);
  assert(props->has("container"));
  assert(props->get("container").is<step::object_ref>());

  // The inventoryEntity member is initialized later
  auto& trigger = registry.emplace<comp::container_trigger>(entity);
  trigger.inventoryId = props->get("container").get<step::object_ref>().get();

  registry.emplace<comp::hitbox>(entity, make_simple_hitbox(object));
}

[[nodiscard]] auto make_basic_object(entt::registry& registry,
                                     const step::object& stepObject)
    -> comp::object::entity
{
  const comp::object::entity entity{registry.create()};

  auto& object = registry.emplace<comp::object>(entity);
  object.id = stepObject.id();

  return entity;
}

}  // namespace

void parse_object_layer(entt::registry& registry,
                        const step::object_group& group)
{
  for (const auto& stepObject : group.objects()) {
    const auto entity = make_basic_object(registry, stepObject);
    const auto type = stepObject.type();
    if (type == "Spawnpoint") {
      parse_spawnpoint(registry, entity, stepObject);
    } else if (type == "Portal") {
      parse_portal(registry, entity, stepObject);
    } else if (type == "Container") {
      parse_container(registry, entity, stepObject);
    } else if (type == "ContainerTrigger") {
      parse_container_trigger(registry, entity, stepObject);
    }
  }
}

}  // namespace wanderer
