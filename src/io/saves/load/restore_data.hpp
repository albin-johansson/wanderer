#pragma once

#include <centurion.hpp>
#include <entt.hpp>  // registry, entity

#include "components/physics/vector3.hpp"
#include "components/time_of_day.hpp"
#include "wanderer_std.hpp"

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

[[nodiscard]] auto Restore(const proto::float2& data) -> float2;

[[nodiscard]] auto Restore(const proto::float3& data) -> comp::Vector3;

[[nodiscard]] auto Restore(const proto::irect& data) -> cen::irect;

[[nodiscard]] auto Restore(const proto::frect& data) -> cen::frect;

[[nodiscard]] auto Restore(const proto::farea& data) -> cen::farea;

[[nodiscard]] auto Restore(const proto::color& data) -> cen::color;

[[nodiscard]] auto Restore(const proto::time_of_day& data) -> ctx::TimeOfDay;

void RestoreMovable(const proto::level& level,
                    entt::registry& registry,
                    entt::entity entity);

void RestoreDrawable(const proto::level& level,
                     entt::registry& registry,
                     entt::entity entity);

void RestoreAnimation(const proto::level& level,
                      entt::registry& registry,
                      entt::entity entity);

void RestorePlant(const proto::level& level,
                  entt::registry& registry,
                  entt::entity entity);

void RestoreTile(const proto::level& level,
                 entt::registry& registry,
                 entt::entity entity);

void RestoreTilemap(const proto::level& level,
                    entt::registry& registry,
                    entt::entity entity);

void RestoreTileAnimations(const proto::level& level,
                           entt::registry& registry,
                           entt::entity entity);

void RestoreChase(const proto::level& level,
                  entt::registry& registry,
                  entt::entity entity);

void RestoreParticle(const proto::level& level,
                     entt::registry& registry,
                     entt::entity entity);

void RestoreLight(const proto::level& level,
                  entt::registry& registry,
                  entt::entity entity);

void RestoreSpawnpoint(const proto::level& level,
                       entt::registry& registry,
                       entt::entity entity);

void RestoreHitbox(const proto::level& level,
                   entt::registry& registry,
                   entt::entity entity);

void RestoreObject(const proto::level& level,
                   entt::registry& registry,
                   entt::entity entity);

void RestorePortal(const proto::level& level,
                   entt::registry& registry,
                   entt::entity entity);

void RestoreTileLayer(const proto::level& level,
                      entt::registry& registry,
                      entt::entity entity);

void RestoreTileset(const proto::level& level,
                    entt::registry& registry,
                    entt::entity entity);

void RestoreInventory(const proto::level& level,
                      entt::registry& registry,
                      entt::entity entity);

void RestoreTileObject(const proto::level& level,
                       entt::registry& registry,
                       entt::entity entity);

void RestoreTrigger(const proto::level& level,
                    entt::registry& registry,
                    entt::entity entity);

void RestoreAssociation(const proto::level& level,
                        entt::registry& registry,
                        entt::entity entity);

}  // namespace wanderer
