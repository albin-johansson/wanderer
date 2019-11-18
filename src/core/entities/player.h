#pragma once
#include "entity.h"
#include "player_state_machine.h"
#include "image.h"
#include "animation.h"
#include <memory>

namespace wanderer::core {

class Player;

using Player_uptr = std::unique_ptr<Player>;
using Player_sptr = std::shared_ptr<Player>;
using Player_wptr = std::weak_ptr<Player>;

/**
 * The Player class represents the entity that is controlled by the player.
 *
 * @see IEntity
 * @since 0.1.0
 */
class Player final : public IEntity {
 private:
  IMovableObject_uptr movableObject = nullptr;
  IPlayerStateMachine_uptr playerStateMachine = nullptr;
  visuals::Image_sptr sheet = nullptr;
  visuals::Animation animation;

 public:
  /**
   * @param sheet a shared pointer to the tile sheet image which will be used by the player.
   * @throws NullPointerException if the supplied image pointer is null.
   * @since 0.1.0
   */
  explicit Player(visuals::Image_sptr sheet);

  ~Player() override = default;

  /**
   * Creates and returns a unique pointer to a player instance.
   *
   * @param sheet a shared pointer to the tile sheet image which will be used by the player.
   * @return a unique pointer to a player instance.
   * @throws NullPointerException if the supplied image pointer is null.
   * @since 0.1.0
   */
  static Player_uptr Create(visuals::Image_sptr sheet);

  void Tick(float delta) override;

  /**
   * Handles the supplied input.
   *
   * @param input a reference to the input state.
   * @since 0.1.0
   */
  inline void HandleInput(const Input& input) { playerStateMachine->HandleInput(input); }

  inline void Draw(visuals::Renderer& renderer, const Viewport& viewport) noexcept override {
    playerStateMachine->Draw(renderer, viewport);
  }

  inline void SetState(EntityStateID id) override { playerStateMachine->SetState(id); }

  inline void AddX(float dx) noexcept override {
    movableObject->AddX(dx);
  }

  inline void AddY(float dy) noexcept override {
    movableObject->AddY(dy);
  }

  inline void SetX(float x) noexcept override {
    movableObject->SetX(x);
  }

  inline void SetY(float y) noexcept override {
    movableObject->SetY(y);
  }

  inline void Move(Direction direction) noexcept override {
    movableObject->Move(direction);
  }

  inline void Stop(Direction direction) noexcept override {
    movableObject->Stop(direction);
  }

  inline void Stop() noexcept override {
    movableObject->Stop();
  }

  inline void SavePosition() noexcept override {
    movableObject->SavePosition();
  }

  inline void Interpolate(float alpha) noexcept override {
    movableObject->Interpolate(alpha);
  }

  inline void SetSpeed(float speed) noexcept override {
    movableObject->SetSpeed(speed);
  }

  inline void UpdateAnimation() noexcept override { animation.Update(); }

  inline void SetAnimationFrame(int index) noexcept override { animation.SetFrame(index); }

  inline void SetAnimationFrameAmount(int nFrames) override { animation.SetNumberOfFrames(nFrames); }

  inline void SetAnimationDelay(Uint32 ms) override { animation.SetDelay(ms); }

  [[nodiscard]] inline bool IsAnimationDone() const noexcept override { return animation.IsDone(); }

  [[nodiscard]] inline int GetAnimationFrame() const noexcept override {
    return animation.GetIndex();
  }

  [[nodiscard]] inline Vector2 GetVelocity() const noexcept override {
    return movableObject->GetVelocity();
  }

  [[nodiscard]] inline Vector2 GetPosition() const noexcept override {
    return movableObject->GetPosition();
  }

  [[nodiscard]] inline Vector2 GetInterpolatedPosition() const noexcept override {
    return movableObject->GetInterpolatedPosition();
  }

  [[nodiscard]] inline float GetX() const noexcept override {
    return movableObject->GetX();
  }

  [[nodiscard]] inline float GetY() const noexcept override {
    return movableObject->GetY();
  }

  [[nodiscard]] inline float GetWidth() const noexcept override {
    return movableObject->GetWidth();
  }

  [[nodiscard]] inline float GetHeight() const noexcept override {
    return movableObject->GetHeight();
  }

  [[nodiscard]] inline Rectangle GetHitbox() const noexcept override {
    return movableObject->GetHitbox();
  }

  [[nodiscard]] inline Direction GetDominantDirection() const noexcept override {
    return movableObject->GetDominantDirection();
  }

  [[nodiscard]] inline visuals::Image& GetSpriteSheet() const noexcept override { return *sheet; }
};

}
