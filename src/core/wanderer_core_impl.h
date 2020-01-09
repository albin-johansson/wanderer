#pragma once
#include <memory>
#include "wanderer_core.h"
#include "viewport.h"
#include "image_generator.h"
#include "menu_state_machine.h"
#include "sound_engine.h"
#include "hud.h"

namespace albinjohansson::wanderer {

/**
 * The WandererCoreImpl class is an implementation of the IWandererCore interface.
 *
 * @since 0.1.0
 */
class WandererCoreImpl final : public IWandererCore {
 private:
  std::shared_ptr<ITileMap> activeMap = nullptr; // could maybe be a raw pointer
  std::unique_ptr<IMenuStateMachine> menuStateMachine = nullptr;
  HUD hud;

  std::shared_ptr<IPlayer> player = nullptr;
  std::shared_ptr<ITileMap> world = nullptr;
  std::unique_ptr<SoundEngine> soundEngine = nullptr;

  Viewport viewport;
  bool shouldQuit = false;

  void init_viewport();

  explicit WandererCoreImpl(ImageGenerator& imageGenerator);

 public:
  ~WandererCoreImpl() override;

  /**
   * Creates and returns a unique pointer to an IWandererCore instance.
   *
   * @param imageGenerator a reference to an image generator.
   * @return a unique pointer to an IWandererCore instance.
   * @since 0.1.0
   */
  friend std::unique_ptr<IWandererCore> create_core(ImageGenerator& imageGenerator);

  void handle_input(const Input& input) override;

  void update(float delta) override;

  void render(centurion::Renderer& renderer, float alpha) override;

  void set_map(std::shared_ptr<ITileMap> map) override;

  void play_sound(const std::string& id) const override;

  void quit() noexcept override;

  void set_viewport_width(float width) override;

  void set_viewport_height(float height) override;

  [[nodiscard]]
  bool should_quit() const noexcept override;

  [[nodiscard]]
  const IPlayer& get_player() const override;

  [[nodiscard]]
  const ITileMap& get_active_map() const override;
};

}
