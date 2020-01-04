#include "hud.h"
#include "renderer.h"
#include "wanderer_core.h"
#include "player.h"
#include "game_constants.h"

namespace albinjohansson::wanderer {

HUD::HUD() = default;

HUD::~HUD() = default;

void HUD::draw_health_bar(centurion::Renderer& renderer, IWandererCore& core) const {
  const auto& player = core.get_player();

  const auto hp = player.get_health();
  const auto hpBarWidth = (hp / playerMaxHealth) * 100;
  const auto hpBarHeight = 20;

  renderer.SetColor(0xFF, 0, 0);
  renderer.RenderFillRect(10, 720 - hpBarHeight - 10, hpBarWidth, hpBarHeight);

  renderer.SetColor(0, 0, 0);
  renderer.RenderRect(10, 720 - hpBarHeight - 10, hpBarWidth, hpBarHeight);
}

void HUD::draw(centurion::Renderer& renderer, IWandererCore& core) const {
  draw_health_bar(renderer, core);
}

}