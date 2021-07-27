#include "load_objects.hpp"

#include "core/aliases/maybe.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto find_inventory(entt::registry& registry, const int id)
    -> maybe<comp::inventory::entity>
{
  maybe<comp::inventory::entity> result;

  for (auto&& [entity, inventory, object] :
       registry.view<comp::inventory, comp::object>().each())
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
    if (const auto result = find_inventory(registry, trigger.inventory_id))
    {
      trigger.inventory_entity = comp::inventory::entity{*result};
    }
  }
}

}  // namespace

void load_objects(entt::registry& registry,
                  graphics_context& graphics,
                  const ir::level& level)
{
  for (const auto& data : level.objects)
  {
    const auto entity = comp::object::entity{registry.create()};

    auto& object = registry.emplace<comp::object>(entity);
    object.id = data.id;

    if (data.drawable)
    {
      auto& drawable = registry.emplace<comp::depth_drawable>(entity);
      drawable.texture = graphics.to_index(data.drawable->texture);
      drawable.depth = data.drawable->depth;
      drawable.layer = data.drawable->layer;
      drawable.src = data.drawable->src;
      drawable.dst = data.drawable->dst;
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

    if (data.inventory_ref)
    {
      auto& trigger = registry.emplace<comp::container_trigger>(entity);
      trigger.inventory_id = *data.inventory_ref;
      trigger.inventory_entity = null<comp::inventory>();  // Set up later
    }

    if (data.bed_trigger)
    {
      registry.emplace<comp::bed_trigger>(entity, *data.bed_trigger);
    }

    if (data.spawnpoint)
    {
      registry.emplace<comp::spawnpoint>(entity, *data.spawnpoint);
    }

    if (data.light)
    {
      registry.emplace<comp::point_light>(entity, *data.light);
    }

    if (data.plant)
    {
      registry.emplace<comp::plant>(entity, *data.plant);
    }
  }

  set_up_container_triggers(registry);
}

}  // namespace wanderer::sys
