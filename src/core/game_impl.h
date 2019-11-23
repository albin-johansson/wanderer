#pragma once
#include "image_generator.h"
#include "player.h"
#include "world.h"
#include "game.h"
#include "sound_engine.h"

namespace albinjohansson::wanderer {

class GameImpl final : public IGame {
 private:
  IWorld_uptr world = nullptr;
  SoundEngine_uptr soundEngine = nullptr;

  void LoadSoundEffects();

 public:
  explicit GameImpl(ImageGenerator& imageGenerator);

  ~GameImpl() override;

  static IGame_uptr Create(ImageGenerator& imageGenerator);

  inline void PlayerHandleInput(const Input& input) override {
    world->PlayerHandleInput(input, *this);
  }

  inline void Render(Renderer& renderer, const Viewport& viewport, float alpha) override {
    world->Render(renderer, viewport, alpha);
  }

  void Update(float delta) override;

  void PlaySound(const std::string& name) const override;

  [[nodiscard]] inline float GetPlayerWidth() const noexcept override {
    return world->GetPlayerWidth();
  }

  [[nodiscard]] inline float GetPlayerHeight() const noexcept override {
    return world->GetPlayerHeight();
  }

  // TODO look over level dimension getters
  [[nodiscard]] inline int GetLevelWidth() const noexcept override { return world->GetWidth(); }

  [[nodiscard]] inline int GetLevelHeight() const noexcept override { return world->GetHeight(); }

  [[nodiscard]] inline Vector2 GetPlayerPosition() const noexcept override {
    return world->GetPlayerPosition();
  }

  [[nodiscard]] inline Vector2 GetPlayerInterpolatedPosition() const noexcept override {
    return world->GetPlayerInterpolatedPosition();
  }
};

}
