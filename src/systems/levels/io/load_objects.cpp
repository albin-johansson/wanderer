#include "load_objects.hpp"

#include <map>  // map

#include "common/ints.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto find_object(entt::registry& registry, const int32 id) -> entt::entity
{
  for (auto&& [entity, object] : registry.view<comp::object>().each()) {
    if (object.id == id) {
      return entity;
    }
  }

  return entt::null;
}

}  // namespace

void load_objects(entt::registry& registry,
                  graphics_context& graphics,
                  const ir::level& level)
{
  std::map<entt::entity, int32> associations;

  for (const auto& data : level.objects) {
    const auto entity = registry.create();

    auto& object = registry.emplace<comp::object>(entity);
    object.id = data.id;

    if (data.drawable) {
      auto& drawable = registry.emplace<comp::drawable>(entity);
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

    if (data.object_ref) {
      associations[entity] = *data.object_ref;
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

  for (const auto& [entity, id] : associations) {
    auto& association = registry.emplace<comp::associated_entity>(entity);
    association.entity = find_object(registry, id);
  }
}

}  // namespace wanderer::sys
