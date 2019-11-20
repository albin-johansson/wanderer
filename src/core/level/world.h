#pragma once
#include "tickable.h"
#include "renderer.h"
#include "viewport.h"
#include "direction.h"
#include "vector_2.h"
#include "input.h"
#include <memory>
#include <string>

namespace wanderer::core {

class IWorld : public ITickable {
 protected:
  IWorld() = default;

 public:
  ~IWorld() override = default;

  virtual void PlayerHandleInput(const Input& input, const IGame& game) = 0;

  virtual void Render(visuals::Renderer& renderer, const Viewport& viewport, float alpha) = 0;

  [[nodiscard]] virtual int GetWidth() const noexcept = 0;

  [[nodiscard]] virtual int GetHeight() const noexcept = 0;

  [[nodiscard]] virtual float GetPlayerWidth() const noexcept = 0;

  [[nodiscard]] virtual float GetPlayerHeight() const noexcept = 0;

  [[nodiscard]] virtual Vector2 GetPlayerPosition() const noexcept = 0;

  [[nodiscard]] virtual Vector2 GetPlayerInterpolatedPosition() const noexcept = 0;
};

using IWorld_uptr = std::unique_ptr<IWorld>;
using IWorld_sptr = std::shared_ptr<IWorld>;
using IWorld_wptr = std::weak_ptr<IWorld>;

}
