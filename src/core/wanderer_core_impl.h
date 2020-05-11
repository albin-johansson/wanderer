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
class WandererCoreImpl final
    : public IWandererCore,
      public std::enable_shared_from_this<WandererCoreImpl> {
 public:
  ~WandererCoreImpl() override;

  /**
   * Creates and returns a shared pointer to an IWandererCore instance.
   *
   * @param textureLoader a reference to an image generator.
   * @return a shared pointer to an IWandererCore instance.
   * @since 0.1.0
   */
  friend shared<IWandererCore> create_core(ctn::TextureLoader& textureLoader);

  void handle_input(const Input& input) override;

  void update(float delta) override;

  void render(ctn::Renderer& renderer, float alpha) override;

  void set_map(shared<ITileMap> map) override;

  void play_sound(const std::string& id) const override;

  void quit() noexcept override;

  void set_viewport_width(float width) override;

  void set_viewport_height(float height) override;

  [[nodiscard]] bool should_quit() const noexcept override;

  [[nodiscard]] const IPlayer& get_player() const override;

  [[nodiscard]] const ITileMap& get_active_map() const override;

 private:
  shared<ITileMap> m_activeMap = nullptr;  // could maybe be a raw
                                           // pointer
  shared<IMenuStateMachine> m_menuStateMachine = nullptr;
  HUD m_hud;

  shared<IPlayer> m_player = nullptr;
  shared<ITileMap> m_world = nullptr;
  unique<SoundEngine> m_soundEngine = nullptr;

  Viewport m_viewport;
  bool m_shouldQuit = false;

  explicit WandererCoreImpl(ctn::TextureLoader& textureLoader);

  void init_viewport();

//  void init_menus();
};

}  // namespace albinjohansson::wanderer
