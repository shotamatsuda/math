//
//  shotamatsuda/math/side.h
//
//  The MIT License
//
//  Copyright (C) 2013-2017 Shota Matsuda
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//

#pragma once
#ifndef SHOTAMATSUDA_MATH_SIDE_H_
#define SHOTAMATSUDA_MATH_SIDE_H_

#include <cassert>
#include <cstddef>
#include <functional>
#include <ostream>

namespace shotamatsuda {
namespace math {

enum class Side : int {
  COINCIDENT = 0,
  LEFT = 1,
  RIGHT = 2
};

inline std::ostream& operator<<(std::ostream& os, Side side) {
  switch (side) {
    case Side::COINCIDENT: os << "coincident"; break;
    case Side::LEFT: os << "left"; break;
    case Side::RIGHT: os << "right"; break;
    default:
      assert(false);
      break;
  }
  return os;
}

}  // namespace math

using math::Side;

}  // namespace shotamatsuda

template <>
struct std::hash<shotamatsuda::math::Side> {
  std::size_t operator()(const shotamatsuda::math::Side& value) const {
    return static_cast<std::underlying_type<shotamatsuda::math::Side>::type>(value);
  }
};

#endif  // SHOTAMATSUDA_MATH_SIDE_H_
