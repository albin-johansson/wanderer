#pragma once

#include <centurion.hpp>
#include <entt.hpp>  // registry, entity

#include "components/time_of_day.hpp"
#include "components/vector3.hpp"
#include "wanderer_std.hpp"

namespace wanderer {
namespace proto {

class float2;
class float3;
class frect;
class irect;
class Color;
class TimeOfDay;
class Level;

}  // namespace proto

[[nodiscard]] auto Restore(const proto::float2& data) -> float2;

[[nodiscard]] auto Restore(const proto::float3& data) -> comp::Vector3;

[[nodiscard]] auto Restore(const proto::irect& data) -> cen::irect;

[[nodiscard]] auto Restore(const proto::frect& data) -> cen::frect;

[[nodiscard]] auto Restore(const proto::Color& data) -> cen::color;

[[nodiscard]] auto Restore(const proto::TimeOfDay& data) -> ctx::TimeOfDay;

void RestoreMovable(const proto::Level& level,
                    entt::registry& registry,
                    entt::entity entity);

void RestoreDrawable(const proto::Level& level,
                     entt::registry& registry,
                     entt::entity entity);

void RestoreAnimation(const proto::Level& level,
                      entt::registry& registry,
                      entt::entity entity);

void RestorePlant(const proto::Level& level,
                  entt::registry& registry,
                  entt::entity entity);

void RestoreTile(const proto::Level& level,
                 entt::registry& registry,
                 entt::entity entity);

void RestoreTileAnimations(const proto::Level& level,
                           entt::registry& registry,
                           entt::entity entity);

void RestoreChase(const proto::Level& level,
                  entt::registry& registry,
                  entt::entity entity);

void RestoreParticle(const proto::Level& level,
                     entt::registry& registry,
                     entt::entity entity);

void RestoreLight(const proto::Level& level,
                  entt::registry& registry,
                  entt::entity entity);

void RestoreSpawnpoint(const proto::Level& level,
                       entt::registry& registry,
                       entt::entity entity);

void RestoreHitbox(const proto::Level& level,
                   entt::registry& registry,
                   entt::entity entity);

void RestoreObject(const proto::Level& level,
                   entt::registry& registry,
                   entt::entity entity);

void RestorePortal(const proto::Level& level,
                   entt::registry& registry,
                   entt::entity entity);

void RestoreTileLayer(const proto::Level& level,
                      entt::registry& registry,
                      entt::entity entity);

void RestoreTileset(const proto::Level& level,
                    entt::registry& registry,
                    entt::entity entity);

void RestoreInventory(const proto::Level& level,
                      entt::registry& registry,
                      entt::entity entity);

void RestoreTileObject(const proto::Level& level,
                       entt::registry& registry,
                       entt::entity entity);

void RestoreTrigger(const proto::Level& level,
                    entt::registry& registry,
                    entt::entity entity);

void RestoreAssociation(const proto::Level& level,
                        entt::registry& registry,
                        entt::entity entity);

}  // namespace wanderer
