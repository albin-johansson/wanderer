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

#ifndef STEP_TILE_LAYER_HEADER
#define STEP_TILE_LAYER_HEADER

#include <memory>

#include "step_api.hpp"
#include "step_chunk.hpp"
#include "step_data.hpp"
#include "step_types.hpp"

namespace step {

/**
 * The TileLayer class represents the API for layers that represent "tile
 * layers", that mainly hold tile data.
 *
 * @since 0.1.0
 */
class TileLayer final {
 public:
  /**
   * The Compression enum class provides values for the different kinds of
   * compression used by layers.
   *
   * @since 0.1.0
   */
  enum class Compression { ZLib, GZip, None };

  /**
   * The Encoding enum class provides identifiers for the different encodings
   * used by layers.
   *
   * @since 0.1.0
   */
  enum class Encoding { CSV, Base64 };

  STEP_API
  explicit TileLayer(const json& json);

  /**
   * Returns the encoding used by the tile layer. The default value of this
   * property is <code>CSV</code>.
   *
   * @return the encoding used by the tile layer.
   * @since 0.1.0
   */
  STEP_QUERY
  Encoding encoding() const noexcept;

  /**
   * Returns the compression used by the tile layer. The default value of
   * this property is <code>None</code>.
   *
   * @return the compression used by the tile layer.
   * @since 0.1.0
   */
  STEP_QUERY
  Compression compression() const noexcept;

  /**
   * Returns a pointer to the tile data associated with the tile layer. This
   * property is optional. Do not claim ownership of the returned pointer.
   *
   * @return the tile data associated with the tile layer; null if there is
   * no such data.
   * @since 0.1.0
   */
  STEP_QUERY
  const detail::Data* data() const;

  /**
   * Returns the chunks associated with the tile layer.
   *
   * @return the chunks associated with the tile layer.
   * @since 0.1.0
   */
  STEP_QUERY
  const std::vector<Chunk>& chunks() const noexcept;

 private:
  Encoding m_encoding{Encoding::CSV};
  Compression m_compression{Compression::None};
  std::unique_ptr<detail::Data> m_data;
  std::vector<Chunk> m_chunks;
};

NLOHMANN_JSON_SERIALIZE_ENUM(TileLayer::Compression,
                             {{TileLayer::Compression::None, ""},
                              {TileLayer::Compression::GZip, "gzip"},
                              {TileLayer::Compression::ZLib, "zlib"}})

NLOHMANN_JSON_SERIALIZE_ENUM(TileLayer::Encoding,
                             {{TileLayer::Encoding::CSV, "csv"},
                              {TileLayer::Encoding::Base64, "base64"}})

}  // namespace step

#endif  // STEP_TILE_LAYER_HEADER
