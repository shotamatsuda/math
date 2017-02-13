//
//  shotamatsuda/math/circle2.h
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
#ifndef SHOTAMATSUDA_MATH_CIRCLE2_H_
#define SHOTAMATSUDA_MATH_CIRCLE2_H_

#include <cstddef>
#include <functional>

#include "shotamatsuda/math/constants.h"
#include "shotamatsuda/math/promotion.h"
#include "shotamatsuda/math/vector.h"

namespace shotamatsuda {
namespace math {

template <class T, int D>
class Circle;

template <class T>
using Circle2 = Circle<T, 2>;

template <class T>
class Circle<T, 2> final {
 public:
  using Type = T;

 public:
  Circle();
  Circle(const Vec2<T>& center, T radius);
  Circle(const Vec2<T>& a, const Vec2<T>& b);
  Circle(const Vec2<T>& a, const Vec2<T>& b, const Vec2<T>& c);

  // Copy semantics
  Circle(const Circle& other) = default;
  Circle& operator=(const Circle& other) = default;

  // Mutators
  void set(const Vec2<T>& center, T radius);
  void set(const Vec2<T>& a, const Vec2<T>& b);
  void set(const Vec2<T>& a, const Vec2<T>& b, const Vec2<T>& c);
  void reset();

  // Comparison
  template <class V, class U = T>
  bool equals(const Circle2<U>& other, V tolerance) const;

  // Attributes
  bool empty() const { return !radius; }
  Promote<T> diameter() const;
  Promote<T> circumference() const;
  Promote<T> area() const;

  // Canonicalization
  bool canonical() const { return radius > 0; }
  Circle& canonicalize();
  Circle2<Promote<T>> canonicalized() const;

  // Containment
  template <class U = T>
  bool contains(const Vec2<U>& point) const;

 public:
  union {
    Vec2<T> center;
    struct { T x; T y; };
  };
  T radius;
};

using Circle2i = Circle2<int>;
using Circle2f = Circle2<float>;
using Circle2d = Circle2<double>;

// MARK: -

template <class T>
inline Circle<T, 2>::Circle() : center(), radius() {}

template <class T>
inline Circle<T, 2>::Circle(const Vec2<T>& center, T radius)
    : center(center),
      radius(radius) {}

template <class T>
inline Circle<T, 2>::Circle(const Vec2<T>& a, const Vec2<T>& b) {
  set(a, b);
}

template <class T>
inline Circle<T, 2>::Circle(const Vec2<T>& a,
                            const Vec2<T>& b,
                            const Vec2<T>& c) {
  set(a, b, c);
}

// MARK: Mutators

template <class T>
inline void Circle<T, 2>::set(const Vec2<T>& center, T radius) {
  this->center = center;
  this->radius = radius;
}

template <class T>
inline void Circle<T, 2>::set(const Vec2<T>& a, const Vec2<T>& b) {
  center = (a + b) / 2;
  radius = center.distance(a);
}

template <class T>
inline void Circle<T, 2>::set(const Vec2<T>& a,
                              const Vec2<T>& b,
                              const Vec2<T>& c) {
  // TODO(shotamatsuda):
}

template <class T>
inline void Circle<T, 2>::reset() {
  *this = Circle();
}

// MARK: Comparison

template <class T, class U>
inline bool operator==(const Circle2<T>& lhs, const Circle2<U>& rhs) {
  return lhs.center == rhs.center && lhs.radius == rhs.radius;
}

template <class T, class U>
inline bool operator!=(const Circle2<T>& lhs, const Circle2<U>& rhs) {
  return !(lhs == rhs);
}

template <class T, class U>
inline bool operator<(const Circle2<T>& lhs, const Circle2<U>& rhs) {
  return lhs.center < rhs.center ||
        (lhs.center == rhs.center && lhs.radius < rhs.radius);
}

template <class T, class U>
inline bool operator>(const Circle2<T>& lhs, const Circle2<U>& rhs) {
  return lhs.center > rhs.center ||
        (lhs.center == rhs.center && lhs.radius > rhs.radius);
}

template <class T, class U>
inline bool operator<=(const Circle2<T>& lhs, const Circle2<U>& rhs) {
  return lhs < rhs || lhs == rhs;
}

template <class T, class U>
inline bool operator>=(const Circle2<T>& lhs, const Circle2<U>& rhs) {
  return lhs > rhs || lhs == rhs;
}

template <class T>
template <class V, class U>
inline bool Circle<T, 2>::equals(const Circle2<U>& other, V tolerance) const {
  return ((center - radius).equals((other.center - other.radius), tolerance) &&
          (center + radius).equals((other.center + other.radius), tolerance));
}

// MARK: Attributes

template <class T>
inline Promote<T> Circle<T, 2>::diameter() const {
  return radius + radius;
}

template <class T>
inline Promote<T> Circle<T, 2>::circumference() const {
  return radius * tau<T>();
}

template <class T>
inline Promote<T> Circle<T, 2>::area() const {
  return radius * radius * pi<T>();
}

// MARK: Canonicalization

template <class T>
inline Circle2<T>& Circle<T, 2>::canonicalize() {
  if (radius < 0) {
    radius = -radius;
  }
  return *this;
}

template <class T>
inline Circle2<Promote<T>> Circle<T, 2>::canonicalized() const {
  return Circle2<Promote<T>>(*this).canonicalize();
}

// MARK: Containment

template <class T>
template <class U>
inline bool Circle<T, 2>::contains(const Vec2<U>& point) const {
  return center.distanceSquared(point) <= radius * radius;
}

}  // namespace math

using math::Circle2;
using math::Circle2i;
using math::Circle2f;
using math::Circle2d;

}  // namespace shotamatsuda

template <class T>
struct std::hash<shotamatsuda::math::Circle2<T>> {
  std::size_t operator()(const shotamatsuda::math::Circle2<T>& value) const {
    return ((std::hash<shotamatsuda::math::Vec2<T>>()(value.center) << 0) ^
            (std::hash<T>()(value.radius) << 1));
  }
};

#endif  // SHOTAMATSUDA_MATH_CIRCLE2_H_
