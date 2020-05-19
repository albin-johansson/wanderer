#pragma once
#include "entity_id.h"
#include "vector_2.h"

namespace wanderer {

class Spawnpoint final {
 public:
  Spawnpoint(EntityID id, const Vector2& position) noexcept;

  ~Spawnpoint() noexcept;

  [[nodiscard]] EntityID get_entity_id() const noexcept;

  [[nodiscard]] const Vector2& get_position() const noexcept;

 private:
  EntityID m_entityId;
  Vector2 m_position;
};

}  // namespace wanderer
