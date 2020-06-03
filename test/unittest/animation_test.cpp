#include "animation.h"

#include <doctest.h>
#include <timer.h>

using namespace wanderer;
using namespace centurion;

TEST_SUITE("Animation")
{
  TEST_CASE("Defaults")
  {
    Animation animation;
    CHECK(animation.frame() == 0);
    CHECK(animation.delay() == 100);
    CHECK(animation.frames() == 1);
  }

  TEST_CASE("tick")
  {
    Animation animation;
    const auto then = Timer::millis();

    animation.set_delay(200);
    animation.set_frames(15);

    animation.tick();
    CHECK(animation.frame() == (Timer::millis() - then) / animation.delay());
  }

  TEST_CASE("reset")
  {
    Animation animation;

    animation.tick();
    animation.reset();

    CHECK(animation.frame() == 0);
  }

  TEST_CASE("set_delay")
  {
    Animation animation;

    const auto delay = 163;
    animation.set_delay(delay);

    CHECK(animation.delay() == delay);
  }

  TEST_CASE("set_frames")
  {
    Animation animation;

    const auto frames = 7;
    animation.set_frames(frames);

    CHECK(animation.frames() == frames);
  }
}
