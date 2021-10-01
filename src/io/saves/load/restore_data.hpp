#pragma once

#include <centurion.hpp>
#include <entt.hpp>  // registry, entity

#include "common/float2.hpp"
#include "components/ctx/time_of_day.hpp"
#include "components/physics/float3.hpp"

namespace wanderer {
namespace proto {

class float2;
class float3;
class farea;
class frect;
class irect;
class color;
class time_of_day;
class level;

}  // namespace proto

[[nodiscard]] auto restore(const proto::float2& data) -> float2;

[[nodiscard]] auto restore(const proto::float3& data) -> comp::float3;

[[nodiscard]] auto restore(const proto::irect& data) -> cen::irect;

[[nodiscard]] auto restore(const proto::frect& data) -> cen::frect;

[[nodiscard]] auto restore(const proto::farea& data) -> cen::farea;

[[nodiscard]] auto restore(const proto::color& data) -> cen::color;

[[nodiscard]] auto restore(const proto::time_of_day& data) -> ctx::time_of_day;

void restore_movable(const proto::level& level,
                     entt::registry& registry,
                     entt::entity entity);

void restore_drawable(const proto::level& level,
                      entt::registry& registry,
                      entt::entity entity);

void restore_animation(const proto::level& level,
                       entt::registry& registry,
                       entt::entity entity);

void restore_plant(const proto::level& level,
                   entt::registry& registry,
                   entt::entity entity);

void restore_tile(const proto::level& level,
                  entt::registry& registry,
                  entt::entity entity);

void restore_tilemap(const proto::level& level,
                     entt::registry& registry,
                     entt::entity entity);

void restore_tile_animations(const proto::level& level,
                             entt::registry& registry,
                             entt::entity entity);

void restore_chase(const proto::level& level,
                   entt::registry& registry,
                   entt::entity entity);

void restore_particle(const proto::level& level,
                      entt::registry& registry,
                      entt::entity entity);

void restore_light(const proto::level& level,
                   entt::registry& registry,
                   entt::entity entity);

void restore_spawnpoint(const proto::level& level,
                        entt::registry& registry,
                        entt::entity entity);

void restore_hitbox(const proto::level& level,
                    entt::registry& registry,
                    entt::entity entity);

void restore_object(const proto::level& level,
                    entt::registry& registry,
                    entt::entity entity);

void restore_portal(const proto::level& level,
                    entt::registry& registry,
                    entt::entity entity);

void restore_tile_layer(const proto::level& level,
                        entt::registry& registry,
                        entt::entity entity);

void restore_tileset(const proto::level& level,
                     entt::registry& registry,
                     entt::entity entity);

void restore_inventory(const proto::level& level,
                       entt::registry& registry,
                       entt::entity entity);

void restore_tile_object(const proto::level& level,
                         entt::registry& registry,
                         entt::entity entity);

void restore_trigger(const proto::level& level,
                     entt::registry& registry,
                     entt::entity entity);

void restore_association(const proto::level& level,
                         entt::registry& registry,
                         entt::entity entity);

}  // namespace wanderer
