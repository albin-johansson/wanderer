#pragma once

namespace albinjohansson::wanderer {

class Renderer;
class Viewport;
class IEntity;

/**
 * The EntityDrawDelegate provides a method that renders an entity.
 *
 * @since 0.1.0
 */
class EntityDrawDelegate final {
 public:
  EntityDrawDelegate() = delete;

  ~EntityDrawDelegate() = default;

  /**
   * Draws an entity.
   *
   * @param renderer a reference to the renderer that will be used.
   * @param viewport a reference to the viewport that will be used.
   * @param entity a reference to the entity that will be rendered.
   * @param srcX the source x-coordinate of the area in the sprite sheet that will be rendered.
   * @param srcY the source y-coordinate of the area in the sprite sheet that will be rendered.
   * @since 0.1.0
   */
  static void Draw(Renderer& renderer,
                   const Viewport& viewport,
                   const IEntity& entity,
                   int srcX,
                   int srcY) noexcept;

};

}
