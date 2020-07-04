#include <centurion_as_ctn.h>
#include <doctest.h>

#include "aabb_system.h"

using namespace wanderer::sys;
using namespace wanderer::comp;

TEST_SUITE("AABB system")
{
  entt::registry registry;

  TEST_CASE("...")
  {
    const auto fstEntity = registry.create();
    const AABB fstBox = aabb::create_box({0, 0}, {100, 100});

    CHECK(fstBox.min == wanderer::vector2f{0, 0});
    CHECK(fstBox.max == wanderer::vector2f{100, 100});
    CHECK(fstBox.area == (100 * 100));

    aabb::insert(registry, fstEntity, fstBox);

    const auto sndEntity = registry.create();
    const AABB sndBox = aabb::create_box({150, 150}, {100, 100});

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
      CHECK(aabb.min.x == 0);
      CHECK(aabb.min.y == 0);
      CHECK(aabb.max.x == 250);
      CHECK(aabb.max.y == 250);
      CHECK(aabb.area == (250.0f * 250.0f));
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
}