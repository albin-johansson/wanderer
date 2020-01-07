#pragma once
#include "vector_2.h"
#include "entity_id.h"

namespace albinjohansson::wanderer {

class Spawnpoint final {
 private:
  EntityID entity_id;
  Vector2 position;

 public:
  Spawnpoint(EntityID id, const Vector2& position) noexcept;

  ~Spawnpoint() noexcept;

  [[nodiscard]]
  EntityID get_entity_id() const noexcept;

  [[nodiscard]]
  const Vector2& get_position() const noexcept;
};

}
