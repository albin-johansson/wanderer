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

#ifndef STEP_API_HEADER
#define STEP_API_HEADER

#include "step_cfg.h"

// Define STEP_API for any platform
// https://atomheartother.github.io/c++/2018/07/12/CPPDynLib.html
#if defined(_WIN32) && !defined(STEP_API)
#ifdef WIN_EXPORT
#define STEP_API __declspec(dllexport)
#else
#define STEP_API __declspec(dllimport)
#endif  // WIN_EXPORT
#else
#define STEP_API
#endif  // defined(_WIN32) && !defined(STEP_API)

// When header-only mode is enabled, definitions are specified as inline
#if !defined(STEP_DEF) && defined(STEP_HEADER_ONLY)
#define STEP_DEF inline
#else
#define STEP_DEF
#endif  // !defined(STEP_DEF) && defined(STEP_HEADER_ONLY)

// Used for getters that aren't inlined
#define STEP_QUERY [[nodiscard]] STEP_API

#endif  // STEP_API_HEADER