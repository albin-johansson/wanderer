#pragma once
#include "wanderer_core.h"
#include "vector_2.h"
#include "player.h"
#include "tile_map.h"
#include "viewport.h"

namespace wanderer::core {

/**
 * The WandererCoreImpl class is an implementation of the IWandererCore interface.
 *
 * @since 0.1.0
 */
class WandererCoreImpl final : public IWandererCore {
 private:
  TileMap_uptr tileMap = nullptr;
  IEntity_uptr player = nullptr;
  Viewport viewport;

  WandererCoreImpl();

 public:
  ~WandererCoreImpl() override;

  /**
   * Creates and returns a unique pointer to an IWandererCore instance.
   *
   * @return a unique pointer to an IWandererCore instance.
   * @since 0.1.0
   */
  friend IWandererCore_uptr CreateCore();

  void Update() override;

  void Render(visuals::Renderer& renderer) override;

  void SavePositions() override;

  void Interpolate(double alpha) override;

  void UpdateViewport() override;

  void SetViewportWidth(int width) override;

  void SetViewportHeight(int height) override;

  void MovePlayer(Direction direction) override;

  void StopPlayer(Direction direction) override;
};

}
