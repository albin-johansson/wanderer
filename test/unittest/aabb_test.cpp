#include <centurion_as_ctn.h>
#include <doctest.h>

#include "aabb_system.h"

using namespace wanderer::sys;
using namespace wanderer::comp;

TEST_SUITE("AABB system")
{
  TEST_CASE("aabb::insert")
  {
    entt::registry registry;

    const auto fstEntity = registry.create();
    const AABB fstBox = aabb::create_box({0, 0}, {100, 100});

    CHECK(fstBox.min == wanderer::vector2f{0, 0});
    CHECK(fstBox.max == wanderer::vector2f{100, 100});
    CHECK(fstBox.area == 10'000);

    aabb::insert(registry, fstEntity, fstBox);

    const auto sndEntity = registry.create();
    const AABB sndBox = aabb::create_box({150, 150}, {100, 100});

    CHECK(sndBox.min == wanderer::vector2f{150, 150});
    CHECK(sndBox.max == wanderer::vector2f{250, 250});
    CHECK(sndBox.area == 10'000);

    aabb::insert(registry, sndEntity, sndBox);

    SUBCASE("Check root")
    {
      const auto rootView = registry.view<AABBRoot>();
      REQUIRE(rootView.size() == 1);

      const auto rootEntity = rootView.front();

      CHECK(rootEntity != fstEntity);
      CHECK(rootEntity != sndEntity);

      const auto& node = registry.get<AABBNode>(rootEntity);
      const auto& aabb = node.box;

      CHECK(aabb.min == wanderer::vector2f{0, 0});
      CHECK(aabb.max == wanderer::vector2f{250, 250});
      CHECK(aabb.area == (250 * 250));
    }

    CHECK(registry.view<AABBNode>().size() == 3);

    //    ctn::Window window;
    //    ctn::Renderer renderer{window};
    //    ctn::event::Event event;
    //
    //    bool running = true;
    //    window.show();
    //    while (running) {
    //      while (event.poll()) {
    //        if (const auto quit = event.as_quit_event(); quit) {
    //          running = false;
    //        }
    //
    //        if (const auto key = event.as_keyboard_event(); key) {
    //          if (key->is_active(SDLK_ESCAPE)) {
    //            running = false;
    //          }
    //        }
    //      }
    //
    //      static bool first = true;
    //      if (first) {
    //        renderer.set_color(ctn::color::black);
    //        renderer.clear();
    //
    //        renderer.set_color(ctn::color::red);
    //
    //        ctn::Log::info("---");
    //        const auto view = registry.view<AABBNode>();
    //        for (const auto entity : view) {
    //          const auto& node = view.get(entity);
    //
    //          const ctn::FPoint pos{node.box.min.x, node.box.min.y};
    //          const ctn::FArea size{node.box.max.x - node.box.min.x,
    //                                node.box.max.y - node.box.min.y};
    //          const ctn::FRect rect{pos, size};
    //
    //          if (registry.has<AABBRoot>(entity)) {
    //            ctn::Log::info("Drawing root...");
    //          }
    //
    //          ctn::Log::info("Drawing (%f, %f, %f, %f))",
    //                         pos.x(),
    //                         pos.y(),
    //                         size.width,
    //                         size.height);
    //
    //          renderer.draw_rect_f(rect);
    //
    //          first = false;
    //        }
    //
    //        renderer.present();
    //      }
    //    }
    //    window.hide();
  }

  TEST_CASE("aabb::merge")
  {
    const auto fst = aabb::create_box({10, 10}, {90, 90});
    const auto snd = aabb::create_box({110, 110}, {90, 90});
    const auto combined = aabb::merge(fst, snd);

    CHECK(combined.min.x == std::min(fst.min.x, snd.min.x));
    CHECK(combined.min.y == std::min(fst.min.y, snd.min.y));

    CHECK(combined.max.x == std::max(fst.max.x, snd.max.x));
    CHECK(combined.max.y == std::max(fst.max.y, snd.max.y));

    const auto width = combined.max.x - combined.min.x;
    const auto height = combined.max.y - combined.min.y;

    CHECK(combined.area == (width * height));
    CHECK(combined.center.x == combined.min.x + (width / 2.0f));
    CHECK(combined.center.y == combined.min.y + (height / 2.0f));
  }
}