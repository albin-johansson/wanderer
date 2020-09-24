/**
 * MIT License
 *
 * Copyright (c) 2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef STEP_LAYER_HEADER
#define STEP_LAYER_HEADER

#include <memory>
#include <string>
#include <variant>
#include <vector>

#include "step_api.hpp"
#include "step_image_layer.hpp"
#include "step_object_group.hpp"
#include "step_properties.hpp"
#include "step_tile_layer.hpp"
#include "step_types.hpp"
#include "step_utils.hpp"

namespace step {

class layer;

/**
 * @class group
 *
 * @brief Represents the API for layers that represent "groups", that
 * in turn contain zero or more layers.
 *
 * @since 0.1.0
 *
 * @headerfile step_group.hpp
 */
class group final {
 public:
  friend void from_json(const json&, group&);

  /**
   * Iterates over all of the layers store in this group.
   *
   * @tparam Lambda the type of the lambda object.
   * @param lambda the lambda that takes one argument, <code>const
   * Layer&</code>.
   * @since 0.1.0
   */
  template <typename Lambda>
  void each(Lambda&& lambda) const
  {
    for (const auto& layer : m_layers) {
      lambda(*layer);
    }
  }

  /**
   * @brief Returns the layer at the specified index.
   *
   * @note This function throws if the index is out-of-bounds.
   *
   * @param index the index of the desired layer.
   *
   * @return the layer at the specified index.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto at(std::size_t index) const -> const layer&
  {
    return *m_layers.at(index);
  }

  /**
   * @brief Returns the amount of layers that are in the group.
   *
   * @return the amount of layers that are in the group.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto num_layers() const noexcept -> int
  {
    return static_cast<int>(m_layers.size());
  }

 private:
  std::vector<std::unique_ptr<layer>> m_layers;
};

inline void from_json(const json& json, group& group)
{
  for (const auto& [key, value] : json.at("layers").items()) {
    group.m_layers.push_back(std::make_unique<layer>(value));
  }
}

/**
 * @class layer
 *
 * @brief Represents the tile layers that reside in the tile maps.
 *
 * @since 0.1.0
 *
 * @headerfile step_layer.hpp
 */
class layer final {
 public:
  /**
   * @enum layer::type
   *
   * @brief Provides identifiers for all of the different possible layer types.
   *
   * @since 0.1.0
   */
  enum class type { tile_layer, object_group, image_layer, group };

  explicit layer(const json& json)
  {
    init_common(json);
    switch (get_type()) {
      case layer::type::tile_layer: {
        m_layerData.emplace<tile_layer>(json);
        break;
      }
      case layer::type::object_group: {
        m_layerData.emplace<object_group>(json);
        break;
      }
      case layer::type::image_layer: {
        m_layerData.emplace<image_layer>(json.get<image_layer>());
        break;
      }
      case layer::type::group: {
        m_layerData.emplace<group>(json.get<group>());
        break;
      }
      default: {
        const auto id = std::to_string(static_cast<int>(type()));
        throw step_exception{"Layer > Unknown layer type: " + id};
      }
    }
  }

  /**
   * @brief Returns specific information associated with the layer, depending
   * on the type of the layer.
   *
   * @note This function throws if the layer doesn't contain the specified
   * type.
   *
   * @tparam T the type of the internal layer information.
   *
   * @return the layer information.
   *
   * @throws step_exception if there is a type mismatch.
   *
   * @since 0.1.0
   */
  template <typename T>
  [[nodiscard]] auto as() const -> const T&
  {
    return std::get<T>(m_layerData);
  }

  /**
   * @brief Returns specific information associated with the layer.
   *
   * @tparam T the type of the internal layer information.
   *
   * @return the layer information; null if there was a type mismatch.
   *
   * @since 0.2.0
   */
  template <typename T>
  [[nodiscard]] auto try_as() const noexcept -> const T*
  {
    return std::get_if<T>(&m_layerData);
  }

  /**
   * @brief Indicates whether or not the layer is of the specified layer type.
   *
   * @tparam T the layer type to check for.
   *
   * @return `true` if the layer matches the supplied layer type; `false`
   * otherwise.
   *
   * @since 0.1.0
   */
  template <typename T>
  [[nodiscard]] auto is() const noexcept -> bool
  {
    return std::holds_alternative<T>(m_layerData);
  }

  /**
   * @brief Returns the type of the layer.
   *
   * @return the type of the layer.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_type() const noexcept -> type
  {
    return m_type;
  }

  /**
   * @brief Returns the unique integer ID associated with the layer.
   *
   * @return the unique integer ID associated with the layer.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto id() const noexcept -> int
  {
    return m_id;
  }

  /**
   * @brief Returns the amount of columns in the layer.
   *
   * @return the amount of columns in the layer.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto width() const noexcept -> int
  {
    return m_width;
  }

  /**
   * @brief Returns the amount of rows in the layer.
   *
   * @return the amount of rows in the layer.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto height() const noexcept -> int
  {
    return m_height;
  }

  /**
   * @brief Returns the properties associated with the layer.
   *
   * @return the properties associated with the layer; null if there are none.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_properties() const noexcept -> const properties*
  {
    return m_properties.get();
  }

  /**
   * @brief Returns the x-coordinate of where the layer content begins.
   *
   * @details This is used by infinite maps.
   *
   * @return the x-coordinate of where the layer content begins.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto start_x() const noexcept -> int
  {
    return m_startX;
  }

  /**
   * @brief Returns the y-coordinate of where the layer content begins.
   *
   * @details This is used by infinite maps.
   *
   * @return the y-coordinate of where the layer content begins.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto start_y() const noexcept -> int
  {
    return m_startY;
  }

  /**
   * @brief Returns the horizontal offset of the layer.
   *
   * @details The default value of this property is 0.
   *
   * @return the horizontal offset of the layer, in pixels.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto offset_x() const noexcept -> double
  {
    return m_offsetX;
  }

  /**
   * @brief Returns the vertical offset of the layer.
   *
   * @details The default value of this property is 0.
   *
   * @return the vertical offset of the layer, in pixels.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto offset_y() const noexcept -> double
  {
    return m_offsetY;
  }

  /**
   * @brief Returns the opacity of the layer.
   *
   * @return the opacity of the layer, in the range [0, 1].
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto opacity() const noexcept -> double
  {
    return m_opacity;
  }

  /**
   * @brief Indicates whether or not the layer is visible.
   *
   * @return `true` if the layer is visible; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto visible() const noexcept -> bool
  {
    return m_visible;
  }

  /**
   * @brief Returns the name associated with the layer.
   *
   * @return the name associated with the layer.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto name() const -> std::string
  {
    return m_name;
  }

 private:
  type m_type{};
  int m_id{0};
  std::variant<std::monostate, tile_layer, image_layer, object_group, group>
      m_layerData;
  std::unique_ptr<properties> m_properties;
  int m_width{0};
  int m_height{0};
  int m_startX{0};
  int m_startY{0};
  double m_offsetX{0};
  double m_offsetY{0};
  double m_opacity{1};
  std::string m_name;
  bool m_visible{true};

  void init_common(const json& json)
  {
    json.at("type").get_to(m_type);

    detail::safe_bind(json, "name", m_name);
    detail::safe_bind(json, "opacity", m_opacity);
    detail::safe_bind(json, "visible", m_visible);
    detail::safe_bind(json, "id", m_id);
    detail::safe_bind(json, "width", m_width);
    detail::safe_bind(json, "height", m_height);
    detail::safe_bind(json, "startx", m_startX);
    detail::safe_bind(json, "starty", m_startY);
    detail::safe_bind(json, "offsetx", m_offsetX);
    detail::safe_bind(json, "offsety", m_offsetY);

    m_properties = detail::safe_bind_unique<properties>(json, "properties");
  }
};

NLOHMANN_JSON_SERIALIZE_ENUM(layer::type,
                             {{layer::type::tile_layer, "tilelayer"},
                              {layer::type::image_layer, "imagelayer"},
                              {layer::type::object_group, "objectgroup"},
                              {layer::type::group, "group"}})

}  // namespace step

#endif  // STEP_LAYER_HEADER
