#include "hud.h"
#include "renderer.h"
#include "wanderer_core.h"
#include "player.h"
#include "game_constants.h"

namespace albinjohansson::wanderer {

HUD::HUD() = default;

HUD::~HUD() = default;

void HUD::DrawHealthBar(Renderer& renderer, IWandererCore& core) const {
  const auto& player = core.GetPlayer();

  const auto hp = player.GetHealth();
  const auto hpBarWidth = (hp / PLAYER_MAX_HEALTH) * 100;
  const auto hpBarHeight = 20;

  renderer.SetColor(0xFF, 0, 0);
  renderer.RenderFillRect(10, 720 - hpBarHeight - 10, hpBarWidth, hpBarHeight);

  renderer.SetColor(0, 0, 0);
  renderer.RenderRect(10, 720 - hpBarHeight - 10, hpBarWidth, hpBarHeight);
}

void HUD::Draw(Renderer& renderer, IWandererCore& core) const {
  DrawHealthBar(renderer, core);
}

}