#pragma once
#include "level.h"
#include "player.h"
#include "entity.h"
#include "tile_map.h"
#include "image_generator.h"
#include "sound_engine.h"
#include <vector>

namespace albinjohansson::wanderer {

class AbstractLevel : public ILevel {
 private:
  ITileMap_uptr tileMap = nullptr;
  IPlayer_sptr player = nullptr;
  SoundEngine_sptr soundEngine = nullptr;

  std::vector<IEntity_sptr> entities;

  void Interpolate(float alpha);

 protected:
  AbstractLevel(ITileMap_uptr tileMap,
                IPlayer_sptr player,
                SoundEngine_sptr soundEngine,
                ImageGenerator& imageGenerator);

 public:
  ~AbstractLevel() override;

  void Update(const Viewport& viewport, float delta) override;

  void Render(Renderer& renderer, const Viewport& viewport, float alpha) override;

  void PlaySound(const std::string& name) const override;

  void Interact(const IEntity& source) override;

  void Attack(const IEntity& source) override;

  [[nodiscard]] int GetTile(int row, int col) override;

  [[nodiscard]] int GetWidth() const noexcept override;

  [[nodiscard]] int GetHeight() const noexcept override;

  [[nodiscard]] const IPlayer& GetPlayer() const noexcept override;

  [[nodiscard]] static bool CompareGameObjects(const IGameObject_sptr& first,
                                               const IGameObject_sptr& second) noexcept;

};

}
