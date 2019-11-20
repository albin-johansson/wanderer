#pragma once
#include "vector_2.h"
#include "renderer.h"
#include "viewport.h"
#include "input.h"
#include <string>
#include <memory>

namespace wanderer::core {

class IGame {
 protected:
  IGame() = default;

 public:
  virtual ~IGame() = default;

  virtual void PlayerHandleInput(const Input& input) = 0;

  virtual void Update(float delta) = 0;

  virtual void Render(visuals::Renderer& renderer, const Viewport& viewport, float alpha) = 0;

  virtual void PlaySound(const std::string& name) const = 0;

  [[nodiscard]] virtual int GetLevelWidth() const noexcept = 0;

  [[nodiscard]] virtual int GetLevelHeight() const noexcept = 0;

  [[nodiscard]] virtual Vector2 GetPlayerPosition() const noexcept = 0;

  [[nodiscard]] virtual Vector2 GetPlayerInterpolatedPosition() const noexcept = 0;

  [[nodiscard]] virtual float GetPlayerWidth() const noexcept = 0;

  [[nodiscard]] virtual float GetPlayerHeight() const noexcept = 0;
};

using IGame_uptr = std::unique_ptr<IGame>;
using IGame_sptr = std::shared_ptr<IGame>;
using IGame_wptr = std::weak_ptr<IGame>;

}
