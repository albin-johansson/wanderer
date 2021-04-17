#include "core/levels/add_objects.hpp"

#include "components/inventory/inventory.hpp"

namespace wanderer {
namespace {

[[nodiscard]] auto find_inventory(entt::registry& registry, const int id)
    -> maybe<comp::inventory::entity>
{
  maybe<comp::inventory::entity> result;

  const auto view = registry.view<comp::inventory, comp::object>();
  for (auto&& [entity, inventory, object] : view.each())
  {
    if (object.id == id)
    {
      result.emplace(entity);
    }
  }

  return result;
}

void set_up_container_triggers(entt::registry& registry)
{
  for (auto&& [entity, trigger] : registry.view<comp::container_trigger>().each())
  {
    if (const auto result = find_inventory(registry, trigger.inventoryId))
    {
      trigger.inventoryEntity = comp::inventory::entity{*result};
    }
  }
}

}  // namespace

void add_objects(entt::registry& registry, const ir::level& level)
{
  for (const auto& data : level.objects)
  {
    const auto entity = comp::object::entity{registry.create()};

    auto& object = registry.emplace<comp::object>(entity);
    object.id = data.id;

    if (data.drawable)
    {
      registry.emplace<comp::depth_drawable>(entity, *data.drawable);
    }

    if (data.hitbox)
    {
      registry.emplace<comp::hitbox>(entity, *data.hitbox);
    }

    if (data.portal)
    {
      registry.emplace<comp::portal>(entity, *data.portal);
    }

    if (data.inventory)
    {
      registry.emplace<comp::inventory>(entity, *data.inventory);
    }

    if (data.inventoryRef)
    {
      auto& trigger = registry.emplace<comp::container_trigger>(entity);
      trigger.inventoryId = *data.inventoryRef;
      trigger.inventoryEntity = null<comp::inventory>();  // Set up later
    }

    if (data.spawnpoint)
    {
      registry.emplace<comp::spawnpoint>(entity, *data.spawnpoint);
    }

    if (data.light)
    {
      registry.emplace<comp::point_light>(entity, *data.light);
    }
  }

  set_up_container_triggers(registry);
}

}  // namespace wanderer
