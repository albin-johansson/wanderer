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

#ifndef STEP_TYPES_HEADER
#define STEP_TYPES_HEADER

#include <json.hpp>
#include <optional>

#include "step_api.h"

namespace step {

using JSON = nlohmann::json;
using JSONValueType = nlohmann::json::value_t;

// TODO remove the error aliases
using TypeError = nlohmann::json::type_error;
using ParseError = nlohmann::json::parse_error;
using OutOfRange = nlohmann::json::out_of_range;

/**
 * The type used for global IDs (GIDs).
 *
 * @since 0.1.0
 */
using GID = unsigned int;

#define STEP_SERIALIZE_ENUM NLOHMANN_JSON_SERIALIZE_ENUM

using CZString = const char*;

template <typename T>
using Maybe = std::optional<T>;

inline constexpr std::nullopt_t nothing = std::nullopt;

}  // namespace step

#endif  // STEP_TYPES_HEADER
