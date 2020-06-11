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

#ifndef STEP_HEADER
#define STEP_HEADER

#include <string_view>

#include "step_animation.h"
#include "step_api.h"
#include "step_cfg.h"
#include "step_chunk.h"
#include "step_color.h"
#include "step_data.h"
#include "step_exception.h"
#include "step_frame.h"
#include "step_grid.h"
#include "step_group.h"
#include "step_image_layer.h"
#include "step_layer.h"
#include "step_map.h"
#include "step_object.h"
#include "step_object_group.h"
#include "step_point.h"
#include "step_properties.h"
#include "step_property.h"
#include "step_terrain.h"
#include "step_text.h"
#include "step_tile.h"
#include "step_tile_layer.h"
#include "step_tile_offset.h"
#include "step_tileset.h"
#include "step_types.h"
#include "step_utils.h"

namespace step {

/**
 * Attempts to parse a Tiled JSON map file located at the specified path.
 * This method will throw an exception if the map cannot be parsed for some
 * reason.
 *
 * @param root the file path of the directory that contains the map file.
 * @param file the location of the Tiled JSON map file.
 * @return a unique pointer to a map that represents the map file.
 * @throws StepException if the map cannot be parsed.
 * @since 0.1.0
 */
STEP_QUERY std::unique_ptr<Map> parse(std::string_view root,
                                      std::string_view file);

}  // namespace step

#endif  // STEP_HEADER
