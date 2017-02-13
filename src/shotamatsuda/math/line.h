//
//  shotamatsuda/math/line.h
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
#ifndef SHOTAMATSUDA_MATH_LINE_H_
#define SHOTAMATSUDA_MATH_LINE_H_

#if SHOTAMATSUDA_HAS_BOOST
#include <boost/polygon/isotropy.hpp>
#include <boost/polygon/segment_concept.hpp>
#endif  // SHOTAMATSUDA_HAS_BOOST

#include "shotamatsuda/math/line2.h"
#include "shotamatsuda/math/line3.h"
#include "shotamatsuda/math/vector.h"

#if SHOTAMATSUDA_HAS_BOOST

template <class T, int D>
struct boost::polygon::geometry_concept<shotamatsuda::Line<T, D>> {
  using type = boost::polygon::segment_concept;
};

template <class T, int D>
struct boost::polygon::segment_traits<shotamatsuda::Line<T, D>> {
  using point_type = shotamatsuda::Vec<T, D>;
  using coordinate_type = typename shotamatsuda::Line<T, D>::Type;

  static point_type get(const shotamatsuda::Line<T, D>& segment,
                        boost::polygon::direction_1d direction) {
    return direction == boost::polygon::LOW ? segment.a : segment.b;
  }
};

template <class T, int D>
struct boost::polygon::segment_mutable_traits<shotamatsuda::Line<T, D>> {
  using point_type = shotamatsuda::Vec<T, D>;
  using coordinate_type = typename shotamatsuda::Line<T, D>::Type;

  static void set(shotamatsuda::Line<T, D>& segment,
                  boost::polygon::direction_1d direction,
                  const shotamatsuda::Vec<T, D>& point) {
    if (direction == boost::polygon::LOW) {
      segment.a = point;
    } else {
      segment.b = point;
    }
  }

  static shotamatsuda::Line<T, D> construct(const shotamatsuda::Vec<T, D>& low,
                                      const shotamatsuda::Vec<T, D>& high) {
    return shotamatsuda::Line<T, D>(low, high);
  }
};

#endif  // SHOTAMATSUDA_HAS_BOOST

#endif  // SHOTAMATSUDA_MATH_LINE_H_
