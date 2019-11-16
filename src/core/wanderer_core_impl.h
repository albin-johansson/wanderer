#pragma once
#include "wanderer_core.h"
#include "vector_2.h"
#include "player.h"
#include "tile_map.h"
#include "viewport.h"
#include "image_generator.h"
#include "menu_state_machine.h"
#include "sound_engine.h"

namespace wanderer::core {

/**
 * The WandererCoreImpl class is an implementation of the IWandererCore interface.
 *
 * @since 0.1.0
 */
class WandererCoreImpl final : public IWandererCore {
 private:
  IMenuStateMachine_uptr menuStateMachine = nullptr;
  TileMap_uptr tileMap = nullptr;
  IEntity_uptr player = nullptr;
  Viewport viewport;

  audio::SoundEngine_uptr soundEngine = nullptr;
  visuals::ImageGenerator_sptr imageGenerator = nullptr;

  explicit WandererCoreImpl(visuals::ImageGenerator_sptr imageGenerator);

  /**
   * Saves the positions of all movable game objects.
   *
   * @since 0.1.0
   */
  void SavePositions();

  /**
   * Interpolates the movable game objects.
   *
   * @param alpha the interpolation coefficient.
   * @since 0.1.0
   */
  void Interpolate(float alpha);

 public:
  ~WandererCoreImpl() override;

  /**
   * Creates and returns a unique pointer to an IWandererCore instance.
   *
   * @return a unique pointer to an IWandererCore instance.
   * @since 0.1.0
   */
  friend IWandererCore_uptr CreateCore(visuals::ImageGenerator_sptr imageGenerator);

  void HandleInput(const Input& input) override;

  void Update(float delta) override;

  void Render(visuals::Renderer& renderer, float alpha) override;

  void SetViewportWidth(float width) override;

  void SetViewportHeight(float height) override;

  void MovePlayer(Direction direction) override;

  void StopPlayer(Direction direction) override;

  [[nodiscard]] const Viewport& GetViewport() const noexcept override;
};

}
