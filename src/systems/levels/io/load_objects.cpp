#include "load_objects.hpp"

#include "common/maybe.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto find_inventory(entt::registry& registry, const int id)
    -> maybe<entt::entity>
{
  maybe<entt::entity> result;

  for (auto&& [entity, inventory, object] :
       registry.view<comp::inventory, comp::object>().each())
  {
    if (object.id == id) {
      result = entity;
      break;
    }
  }

  return result;
}

void set_up_container_triggers(entt::registry& registry)
{
  for (auto&& [entity, ref] : registry.view<comp::associated_entity>().each()) {
    if (const auto result = find_inventory(registry, ref.inventory_id)) {
      ref.entity = *result;
    }
  }
}

}  // namespace

void load_objects(entt::registry& registry,
                  graphics_context& graphics,
                  const ir::level& level)
{
  for (const auto& data : level.objects) {
    const auto entity = comp::object::entity{registry.create()};

    auto& object = registry.emplace<comp::object>(entity);
    object.id = data.id;

    if (data.drawable) {
      auto& drawable = registry.emplace<comp::depth_drawable>(entity);
      drawable.texture = graphics.to_index(data.drawable->texture);
      drawable.depth = data.drawable->depth;
      drawable.layer = data.drawable->layer;
      drawable.src = data.drawable->src;
      drawable.dst = data.drawable->dst;
    }

    if (data.hitbox) {
      registry.emplace<comp::hitbox>(entity, *data.hitbox);
    }

    if (data.trigger_type) {
      auto& trigger = registry.emplace<comp::trigger>(entity);
      trigger.type = *data.trigger_type;
    }

    if (data.portal) {
      registry.emplace<comp::portal>(entity, *data.portal);
    }

    if (data.inventory) {
      registry.emplace<comp::inventory>(entity, *data.inventory);
    }

    if (data.inventory_ref) {
      auto& ref = registry.emplace<comp::associated_entity>(entity);
      ref.inventory_id = *data.inventory_ref;
    }

    if (data.spawnpoint) {
      registry.emplace<comp::spawnpoint>(entity, *data.spawnpoint);
    }

    if (data.light) {
      registry.emplace<comp::point_light>(entity, *data.light);
    }

    if (data.plant) {
      registry.emplace<comp::plant>(entity, *data.plant);
    }
  }

  set_up_container_triggers(registry);
}

}  // namespace wanderer::sys
