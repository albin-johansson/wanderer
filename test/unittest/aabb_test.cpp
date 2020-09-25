#include <catch.hpp>
#include <event.hpp>
#include <log.hpp>
#include <renderer.hpp>
#include <window.hpp>

#include "aabb_system.hpp"

using namespace wanderer;

TEST_CASE("aabb::insert", "[aabb]")
{
  entt::registry registry;

  const auto fstBox = sys::aabb::make_aabb({0, 0}, {100, 100});
  CHECK(fstBox.min == vector2f{0, 0});
  CHECK(fstBox.max == vector2f{100, 100});
  CHECK(fstBox.area == 10'000);

  const auto fstEntity = registry.create();
  sys::aabb::insert(registry, fstEntity, fstBox);

  const auto sndBox = sys::aabb::make_aabb({150, 150}, {100, 100});
  CHECK(sndBox.min == vector2f{150, 150});
  CHECK(sndBox.max == vector2f{250, 250});
  CHECK(sndBox.area == 10'000);

  const auto sndEntity = registry.create();
  sys::aabb::insert(registry, sndEntity, sndBox);

  SECTION("Check root")
  {
    const auto rootView = registry.view<comp::aabb_root>();
    REQUIRE(rootView.size() == 1);

    const auto rootEntity = rootView.front();

    CHECK(rootEntity != fstEntity);
    CHECK(rootEntity != sndEntity);

    const auto& node = registry.get<comp::aabb_node>(rootEntity);
    const auto& aabb = node.box;

    CHECK(aabb.min == vector2f{0, 0});
    CHECK(aabb.max == vector2f{250, 250});
    CHECK(aabb.area == (250 * 250));
  }

  CHECK(registry.view<comp::aabb_node>().size() == 3);
}

TEST_CASE("aabb::merge", "[aabb]")
{
  const auto fst = sys::aabb::make_aabb({10, 10}, {90, 90});
  const auto snd = sys::aabb::make_aabb({110, 110}, {90, 90});
  const auto combined = sys::aabb::merge(fst, snd);

  CHECK(combined.min.x() == std::min(fst.min.x(), snd.min.x()));
  CHECK(combined.min.y() == std::min(fst.min.y(), snd.min.y()));

  CHECK(combined.max.x() == std::max(fst.max.x(), snd.max.x()));
  CHECK(combined.max.y() == std::max(fst.max.y(), snd.max.y()));

  const auto width = combined.max.x() - combined.min.x();
  const auto height = combined.max.y() - combined.min.y();

  CHECK(combined.area == (width * height));
  CHECK(combined.center.x() == combined.min.x() + (width / 2.0f));
  CHECK(combined.center.y() == combined.min.y() + (height / 2.0f));
}

TEST_CASE("Visualization of the AABB system", "[.aabb]")
{
  entt::registry registry;

  const auto fst = registry.create();
  sys::aabb::insert(registry, fst, sys::aabb::make_aabb({0, 0}, {100, 100}));
  sys::aabb::insert(registry,
                    registry.create(),
                    sys::aabb::make_aabb({150, 150}, {100, 100}));
  sys::aabb::insert(registry,
                    registry.create(),
                    sys::aabb::make_aabb({175, 350}, {100, 100}));
  sys::aabb::insert(
      registry, registry.create(), sys::aabb::make_aabb({523, 120}, {33, 56}));

  cen::window window;
  cen::renderer renderer{window};
  cen::event event;

  bool running = true;
  window.show();
  while (running) {
    while (event.poll()) {
      if (event.is<cen::quit_event>()) {
        running = false;
      }

      if (const auto* key = event.try_get<cen::keyboard_event>(); key) {
        if (key->is_active(SDLK_ESCAPE)) {
          running = false;
        } else if (key->is_active(SDLK_RIGHT)) {
          cen::log::info("Updating first AABB...");
          const auto& node = registry.get<comp::aabb_node>(fst);

          auto copy = node.box;
          copy.min.set_x(copy.min.x() - 10);

          sys::aabb::validate(copy);
          sys::aabb::update(registry, fst, copy);
        }
      }
    }

    renderer.set_color(cen::colors::black);
    renderer.clear();

    const auto view = registry.view<comp::aabb_node>();
    for (const auto entity : view) {
      const auto& node = view.get(entity);

      if (node.left == entt::null) {
        renderer.set_color(cen::colors::pink);
      } else {
        renderer.set_color(cen::colors::red);
      }

      const cen::fpoint pos{node.box.min.x(), node.box.min.y()};
      const cen::farea size{node.box.max.x() - node.box.min.x(),
                            node.box.max.y() - node.box.min.y()};
      const cen::frect rect{pos, size};

      renderer.draw_rect(rect);
    }

    renderer.present();
  }
  window.hide();
}
