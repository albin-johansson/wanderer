#include "wanderer_core_impl.h"

using namespace wanderer::view;

namespace wanderer::core {

WandererCoreImpl::WandererCoreImpl() {
  velocity.SetX(speed);
  velocity.SetY(speed);
  velocity.Norm();
  velocity.Scale(speed);
}

WandererCoreImpl::~WandererCoreImpl() = default;

void WandererCoreImpl::Update() {
  position.Add(velocity.GetX() * TIME_STEP, velocity.GetY() * TIME_STEP);
}

void WandererCoreImpl::Render(Renderer& renderer) {
  static int x = 0;

  renderer.SetColor(0, 0, 0);
  renderer.Clear();
  renderer.SetColor(0xFF, 0, 0);

  renderer.RenderFillRect(oldPosition.GetX(), oldPosition.GetY(), 250, 250);

  renderer.Present();

  ++x;
}

void WandererCoreImpl::SavePositions() {
  oldPosition.Set(position);
}

void WandererCoreImpl::Interpolate(float alpha) {
  oldPosition.Interpolate(position, alpha);
}

}