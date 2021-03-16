#include "add_objects.hpp"

#include "inventory.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto find_inventory(entt::registry& registry, const int id)
    -> maybe<comp::inventory::entity>
{
  maybe<comp::inventory::entity> result;

  const auto view = registry.view<comp::inventory, comp::object>();
  view.each([&](const entt::entity entity,
                const comp::inventory&,
                const comp::object& object) {
    if (object.id == id) {
      result.emplace(entity);
    }
  });

  return result;
}

void set_up_container_triggers(entt::registry& registry)
{
  const auto view = registry.view<comp::container_trigger>();
  view.each([&](comp::container_trigger& trigger) {
    if (const auto result = find_inventory(registry, trigger.inventoryId)) {
      trigger.inventoryEntity = comp::inventory::entity{*result};
    }
  });
}

}  // namespace

void add_objects(entt::registry& registry,
                 const graphics_context& graphics,
                 const ir::level& level)
{
  for (const auto& data : level.objects) {
    const auto entity = comp::object::entity{registry.create()};

    auto& object = registry.emplace<comp::object>(entity);
    object.id = data.id;

    if (data.drawable) {
      const auto& drawable = *data.drawable;
      auto& dd = registry.emplace<comp::depth_drawable>(entity);
      dd.texture = graphics.to_index(drawable.texture);
      dd.src = drawable.src;
      dd.dst = drawable.dst;
      dd.layer = drawable.layer;
      dd.depth = drawable.depth;
      dd.centerY = drawable.centerY;
    }

    if (data.hitbox) {
      registry.emplace<comp::hitbox>(entity, *data.hitbox);
    }

    if (data.portal) {
      registry.emplace<comp::portal>(entity, *data.portal);
    }

    if (data.inventory) {
      registry.emplace<comp::inventory>(entity, *data.inventory);
    }

    if (data.inventoryRef) {
      auto& trigger = registry.emplace<comp::container_trigger>(entity);
      trigger.inventoryId = *data.inventoryRef;
      trigger.inventoryEntity = null<comp::inventory>();  // Set up later
    }

    if (data.spawnpoint) {
      registry.emplace<comp::spawnpoint>(entity, *data.spawnpoint);
    }
  }

  set_up_container_triggers(registry);
}

}  // namespace wanderer
