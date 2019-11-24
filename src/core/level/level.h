#pragma once
#include "renderer.h"
#include "viewport.h"
#include <memory>
#include <string>

namespace albinjohansson::wanderer {

class IPlayer;

class ILevel {
 protected:
  ILevel() = default;

 public:
  virtual ~ILevel() = default;

  virtual void Update(float delta) = 0;

  virtual void Render(Renderer& renderer, const Viewport& viewport, float alpha) = 0;

  virtual void PlaySound(const std::string& name) const = 0;

  virtual int GetTile(int row, int col) = 0;

  [[nodiscard]] virtual int GetWidth() const noexcept = 0;

  [[nodiscard]] virtual int GetHeight() const noexcept = 0;

  [[nodiscard]] virtual const IPlayer& GetPlayer() const noexcept = 0;
};

using ILevel_uptr = std::unique_ptr<ILevel>;
using ILevel_sptr = std::shared_ptr<ILevel>;
using ILevel_wptr = std::weak_ptr<ILevel>;

}
