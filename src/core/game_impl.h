#pragma once
#include "image_generator.h"
#include "player.h"
#include "world.h"
#include "game.h"
#include "sound_engine.h"

namespace wanderer::core {

class GameImpl final : public IGame {
 private:
  IWorld_uptr world = nullptr;
  Player_sptr player = nullptr; // TODO this should probably be stored in GameImpl
  audio::SoundEngine_uptr soundEngine = nullptr;

  void LoadSoundEffects();

 public:
  explicit GameImpl(visuals::ImageGenerator& imageGenerator);

  ~GameImpl() override;

  static IGame_uptr Create(visuals::ImageGenerator& imageGenerator);

  void PlayerHandleInput(const Input& input) override;

  void Render(visuals::Renderer& renderer, const Viewport& viewport, float alpha) override;

  void Update(float delta) override;

  void PlaySound(const std::string& name) const override;

  [[nodiscard]] float GetPlayerWidth() const noexcept override;

  [[nodiscard]] float GetPlayerHeight() const noexcept override;

  [[nodiscard]] int GetLevelWidth() const noexcept override;

  [[nodiscard]] int GetLevelHeight() const noexcept override;

  [[nodiscard]] Vector2 GetPlayerPosition() const noexcept override;

  [[nodiscard]] Vector2 GetPlayerInterpolatedPosition() const noexcept override;
};

}
