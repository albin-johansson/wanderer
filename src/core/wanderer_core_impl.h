#pragma once
#include <texture_loader.h>

#include <memory>

#include "hud.h"
#include "menu_state_machine.h"
#include "sound_engine.h"
#include "viewport.h"
#include "wanderer_core.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

/**
 * The WandererCoreImpl class is an implementation of the IWandererCore
 * interface.
 *
 * @since 0.1.0
 */
class WandererCoreImpl final : public IWandererCore {
 private:
  shared<ITileMap> activeMap = nullptr;  // could maybe be a raw pointer

  shared<IMenuStateMachine> menuStateMachine = nullptr;
  HUD hud;

  shared<IPlayer> player = nullptr;
  shared<ITileMap> world = nullptr;
  unique<SoundEngine> soundEngine = nullptr;

  Viewport viewport;
  bool shouldQuit = false;

  void init_viewport();

  explicit WandererCoreImpl(centurion::video::TextureLoader& textureLoader);

 public:
  ~WandererCoreImpl() override;

  /**
   * Creates and returns a unique pointer to an IWandererCore instance.
   *
   * @param textureLoader a reference to an image generator.
   * @return a unique pointer to an IWandererCore instance.
   * @since 0.1.0
   */
  friend unique<IWandererCore> create_core(
      centurion::video::TextureLoader& textureLoader);

  void handle_input(const Input& input) override;

  void update(float delta) override;

  void render(centurion::video::Renderer& renderer, float alpha) override;

  void set_map(shared<ITileMap> map) override;

  void play_sound(const std::string& id) const override;

  void quit() noexcept override;

  void set_viewport_width(float width) override;

  void set_viewport_height(float height) override;

  [[nodiscard]] bool should_quit() const noexcept override;

  [[nodiscard]] const IPlayer& get_player() const override;

  [[nodiscard]] const ITileMap& get_active_map() const override;
};

}  // namespace albinjohansson::wanderer
