#include "smooth_fixed_timestep_loop.h"

#include <SDL.h>
#include <colors.h>
#include <renderer.h>
#include <timer.h>

#include "input.h"
#include "wanderer_core.h"

using namespace centurion;
using namespace centurion::input;

namespace albinjohansson::wanderer {

SmoothFixedTimestepLoop::SmoothFixedTimestepLoop(
    Unique<KeyState> keyState,
    const Shared<MouseState>& mouseState,
    float vsyncRate)
    : m_vsyncRate{vsyncRate},
      m_timeStep{1.0f / vsyncRate},
      m_counterFreq{static_cast<float>(Timer::high_res_freq())}
{
  m_input = std::make_unique<Input>(std::move(keyState), mouseState);
  m_now = Timer::high_res();
  m_then = m_now;
}

SmoothFixedTimestepLoop::~SmoothFixedTimestepLoop() = default;

void SmoothFixedTimestepLoop::update_input(IWandererCore& core)
{
  m_input->update();

  if (m_input->was_quit_requested() || m_input->was_released(SDL_SCANCODE_O)) {
    core.quit();
  }

  core.handle_input(*m_input);
}

void SmoothFixedTimestepLoop::smooth_delta()
{
  /* Reference for delta smoothing: https://frankforce.com/?p=2636 */

  m_delta += m_deltaBuffer;

  int frameCount = static_cast<int>(m_delta * m_vsyncRate + 1);
  if (frameCount <= 0) {
    frameCount = 1;
  }

  const float oldDelta = m_delta;
  m_delta = static_cast<float>(frameCount) / m_vsyncRate;
  m_deltaBuffer = oldDelta - m_delta;
}

void SmoothFixedTimestepLoop::update(IWandererCore& core, Renderer& renderer)
{
  update_input(core);

  m_then = m_now;
  m_now = Timer::high_res();

  m_delta = static_cast<float>(m_now - m_then) / m_counterFreq;

  if (m_delta > maxFrameTime) {
    m_delta = maxFrameTime;
  }

  smooth_delta();

  m_accumulator += m_delta;

  while (m_accumulator >= m_timeStep) {
    m_accumulator -= m_timeStep;
    core.update(m_timeStep);
  }

  float alpha = m_accumulator / m_timeStep;
  if (alpha > 1.0f) {
    alpha = 1.0f;
  }

  renderer.set_color(black);
  renderer.clear();

  core.render(renderer, alpha);

  renderer.present();
}

}  // namespace albinjohansson::wanderer
