//
//  takram/math/rectangle2.h
//
//  MIT License
//
//  Copyright (C) 2015 Shota Matsuda
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
#ifndef TAKRAM_MATH_RECTANGLE2_H_
#define TAKRAM_MATH_RECTANGLE2_H_

#include <algorithm>
#include <cassert>
#include <cmath>
#include <ostream>

#if TAKRAM_HAS_OPENCV
#include "opencv2/core/core.hpp"
#endif  // TAKRAM_HAS_OPENCV

#if TAKRAM_HAS_OPENFRAMEWORKS
#include "ofRectangle.h"
#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER
#include "cinder/Rect.h"
#endif  // TAKRAM_HAS_CINDER

#if TAKRAM_HAS_COREGRAPHICS
#include <CoreGraphics/CoreGraphics.h>
#endif  // TAKRAM_HAS_COREGRAPHICS

#include "takram/math/enablers.h"
#include "takram/math/promotion.h"
#include "takram/math/line.h"
#include "takram/math/size.h"
#include "takram/math/vector.h"

namespace takram {
namespace math {

template <class T, int D>
class Rect;

template <class T>
using Rect2 = Rect<T, 2>;

template <class T>
class Rect<T, 2> final {
 public:
  using Type = T;

 public:
  Rect();
  explicit Rect(const Vec2<T>& origin);
  explicit Rect(const Size2<T>& size);
  Rect(T x, T y, T width, T height);
  Rect(T x, T y, const Size2<T>& size);
  Rect(const Vec2<T>& origin, T width, T height);
  Rect(const Vec2<T>& origin, const Size2<T>& size);
  Rect(const Vec2<T>& p1, const Vec2<T>& p2);

  // Implicit conversion
  template <class U>
  Rect(const Rect2<U>& other);

#if TAKRAM_HAS_OPENCV
  template <class U>
  Rect(const cv::Rect_<U>& other);
  operator cv::Rect_<T>() const;
#endif  // TAKRAM_HAS_OPENCV

#if TAKRAM_HAS_OPENFRAMEWORKS
  Rect(const ofRectangle& other);
  operator ofRectangle() const;
#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER
  template <class U>
  Rect(const ci::RectT<U>& other);
  operator ci::RectT<T>() const;
#endif  // TAKRAM_HAS_CINDER

#if TAKRAM_HAS_COREGRAPHICS
  Rect(const CGRect& other);
  operator CGRect() const;
#endif  // TAKRAM_HAS_COREGRAPHICS

  // Copy semantics
  Rect(const Rect&) = default;
  Rect& operator=(const Rect&) = default;

  // Mutators
  void set(const Vec2<T>& origin);
  void set(const Size2<T>& size);
  void set(T x, T y, T width, T height);
  void set(const Vec2<T>& origin, const Size2<T>& size);
  void set(T x, T y, const Size2<T>& size);
  void set(const Vec2<T>& origin, T width, T height);
  void set(const Vec2<T>& p1, const Vec2<T>& p2);
  void reset();

  // Comparison
  template <class U>
  bool operator==(const Rect2<U>& other) const;
  template <class U>
  bool operator!=(const Rect2<U>& other) const;
  template <class U>
  bool operator<(const Rect2<U>& other) const;
  template <class U>
  bool operator>(const Rect2<U>& other) const;
  template <class U>
  bool operator<=(const Rect2<U>& other) const;
  template <class U>
  bool operator>=(const Rect2<U>& other) const;

  // Attributes
  bool empty() const { return size.empty(); }
  Promote<T> aspect() const;
  Promote<T> diagonal() const;
  Promote<T> area() const;
  Promote<T> circumference() const;
  Vec2<Promote<T>> centroid() const;

  // Edges
  T minX() const;
  T maxX() const;
  T minY() const;
  T maxY() const;
  T left() const { return minX(); }
  T right() const { return maxX(); }
  T top() const { return minY(); }
  T bottom() const { return maxY(); }
  Line2<T> leftEdge() const;
  Line2<T> rightEdge() const;
  Line2<T> topEdge() const;
  Line2<T> bottomEdge() const;

  // Corners
  Vec2<T> topLeft() const;
  Vec2<T> topRight() const;
  Vec2<T> bottomLeft() const;
  Vec2<T> bottomRight() const;

  // Canonicalization
  bool canonical() const { return width > 0 && height > 0; }
  Rect& canonicalize();
  Rect2<Promote<T>> canonicalized() const;

  // Translation
  Rect& translate(T offset);
  Rect& translate(T dx, T dy);
  Rect& translate(const Vec2<T>& offset);
  template <class U>
  Rect2<Promote<T, U>> translated(U offset) const;
  template <class U>
  Rect2<Promote<T, U>> translated(U dx, U dy) const;
  template <class U>
  Rect2<Promote<T, U>> translated(const Vec2<U>& offset) const;

  // Scaling
  Rect& scale(T scale);
  Rect& scale(T sx, T sy);
  Rect& scale(const Vec2<T>& scale);
  template <class U>
  Rect2<Promote<T, U>> scaled(U scale) const;
  template <class U>
  Rect2<Promote<T, U>> scaled(U sx, U sy) const;
  template <class U>
  Rect2<Promote<T, U>> scaled(const Vec2<U>& scale) const;

  // Containment
  template <class U>
  bool contains(const Vec2<U>& point) const;

 public:
  union {
    Vec2<T> origin;
    struct { T x; T y; };
  };
  union {
    Size2<T> size;
    struct { T width; T height; };
    struct { T w; T h; };
  };
};

using Rect2i = Rect2<int>;
using Rect2f = Rect2<float>;
using Rect2d = Rect2<double>;

template <class T, int D>
using Rectangle = Rect<T, D>;
template <class T>
using Rectangle2 = Rect2<T>;
using Rectangle2i = Rect2i;
using Rectangle2f = Rect2f;
using Rectangle2d = Rect2d;

#pragma mark -

template <class T>
inline Rect2<T>::Rect() : origin(), size() {}

template <class T>
inline Rect2<T>::Rect(const Vec2<T>& origin) : origin(origin), size() {}

template <class T>
inline Rect2<T>::Rect(const Size2<T>& size) : origin(), size(size) {}

template <class T>
inline Rect2<T>::Rect(T x, T y, T width, T height)
    : origin(x, y),
      size(width, height) {}

template <class T>
inline Rect2<T>::Rect(T x, T y, const Size2<T>& size)
    : origin(x, y),
      size(size) {}

template <class T>
inline Rect2<T>::Rect(const Vec2<T>& origin, T width, T height)
    : origin(origin),
      size(width, height) {}

template <class T>
inline Rect2<T>::Rect(const Vec2<T>& origin, const Size2<T>& size)
    : origin(origin),
      size(size) {}

template <class T>
inline Rect2<T>::Rect(const Vec2<T>& p1, const Vec2<T>& p2)
    : origin(std::min(p1.x, p2.x), std::min(p1.y, p2.y)),
      size(std::max(p1.x, p2.x) - origin.x, std::max(p1.y, p2.y) - origin.y) {}

#pragma mark Implicit conversion

template <class T>
template <class U>
inline Rect2<T>::Rect(const Rect2<U>& other)
    : origin(other.origin),
      size(other.size) {}

#if TAKRAM_HAS_COREGRAPHICS

template <class T>
inline Rect2<T>::Rect(const CGRect& other)
    : origin(other.origin),
      size(other.size) {}

template <class T>
inline Rect2<T>::operator CGRect() const {
  return CGRectMake(x, y, width, height);
}

#endif  // TAKRAM_HAS_COREGRAPHICS

#if TAKRAM_HAS_OPENCV

template <class T>
template <class U>
inline Rect2<T>::Rect(const cv::Rect_<U>& other)
    : origin(other.x, other.y),
      size(other.width, other.height) {}

template <class T>
inline Rect2<T>::operator cv::Rect_<T>() const {
  return ofRectangle(x, y, width, height);
}

#endif  // TAKRAM_HAS_OPENCV

#if TAKRAM_HAS_OPENFRAMEWORKS

template <class T>
inline Rect2<T>::Rect(const ofRectangle& other)
    : origin(other.x, other.y),
      size(other.width, other.height) {}

template <class T>
inline Rect<T>::operator ofRectangle() const {
  return ofRectangle(x, y, width, height);
}

#endif  // TAKRAM_HAS_OPENFRAMEWORKS

#if TAKRAM_HAS_CINDER

template <class T>
template <class U>
inline Rect2<T>::Rect(const ci::RectT<U>& other)
    : origin(other.x1, other.y1),
      size(other.x2 - other.x1, other.y2 - other.y1) {}

template <class T>
inline Rect<T>::operator ci::RectT<T>() const {
  return ci::RectT<T>(x, y, x + width, y + height);
}

#endif  // TAKRAM_HAS_CINDER

#pragma mark Mutators

template <class T>
inline void Rect2<T>::set(const Vec2<T>& origin) {
  this->origin = origin;
}

template <class T>
inline void Rect2<T>::set(const Size2<T>& size) {
  this->size = size;
}

template <class T>
inline void Rect2<T>::set(T x, T y, T width, T height) {
  origin.set(x, y);
  size.set(width, height);
}

template <class T>
inline void Rect2<T>::set(const Vec2<T>& origin, const Size2<T>& size) {
  this->origin = origin;
  this->size = size;
}

template <class T>
inline void Rect2<T>::set(T x, T y, const Size2<T>& size) {
  origin.set(x, y);
  this->size = size;
}

template <class T>
inline void Rect2<T>::set(const Vec2<T>& origin, T width, T height) {
  this->origin = origin;
  size.set(width, height);
}

template <class T>
inline void Rect2<T>::set(const Vec2<T>& p1, const Vec2<T>& p2) {
  origin.set(std::min(p1.x, p2.x), std::min(p1.y, p2.y));
  size.set(std::max(p1.x, p2.x) - origin.x, std::max(p1.y, p2.y) - origin.y);
}

template <class T>
inline void Rect2<T>::reset() {
  *this = Rect();
}

#pragma mark Comparison

template <class T>
template <class U>
inline bool Rect2<T>::operator==(const Rect2<U>& other) const {
  return origin == other.origin && size == other.size;
}

template <class T>
template <class U>
inline bool Rect2<T>::operator!=(const Rect2<U>& other) const {
  return !operator==(other);
}

template <class T>
template <class U>
inline bool Rect2<T>::operator<(const Rect2<U>& other) const {
  return origin < other.origin || (origin == other.origin && size < other.size);
}

template <class T>
template <class U>
inline bool Rect2<T>::operator>(const Rect2<U>& other) const {
  return origin > other.origin || (origin == other.origin && size > other.size);
}

template <class T>
template <class U>
inline bool Rect2<T>::operator<=(const Rect2<U>& other) const {
  return operator<(other) || operator==(other);
}

template <class T>
template <class U>
inline bool Rect2<T>::operator>=(const Rect2<U>& other) const {
  return operator>(other) || operator==(other);
}

#pragma mark Attributes

template <class T>
inline Promote<T> Rect2<T>::aspect() const {
  return size.aspect();
}

template <class T>
inline Promote<T> Rect2<T>::diagonal() const {
  return size.diagonal();
}

template <class T>
inline Promote<T> Rect2<T>::area() const {
  return size.area();
}

template <class T>
inline Promote<T> Rect2<T>::circumference() const {
  return 2 * std::abs(Promote<T>(width)) + 2 * std::abs(Promote<T>(height));
}

template <class T>
inline Vec2<Promote<T>> Rect2<T>::centroid() const {
  return origin + Vec2<Promote<T>>(static_cast<Size2<T>>(size) / 2);
}

#pragma mark Edges

template <class T>
inline T Rect2<T>::minX() const {
  return std::min<T>(x, x + width);
}

template <class T>
inline T Rect2<T>::maxX() const {
  return std::max<T>(x, x + width);
}

template <class T>
inline T Rect2<T>::minY() const {
  return std::min<T>(y, y + height);
}

template <class T>
inline T Rect2<T>::maxY() const {
  return std::max<T>(y, y + height);
}

template <class T>
inline Line2<T> Rect2<T>::leftEdge() const {
  const auto x = left();
  return Line2<T>({x, top()}, {x, bottom()});
}

template <class T>
inline Line2<T> Rect2<T>::rightEdge() const {
  const auto x = right();
  return Line2<T>({x, top()}, {x, bottom()});
}

template <class T>
inline Line2<T> Rect2<T>::topEdge() const {
  const auto y = top();
  return Line2<T>({left(), y}, {right(), y});
}

template <class T>
inline Line2<T> Rect2<T>::bottomEdge() const {
  const auto y = bottom();
  return Line2<T>({left(), y}, {right(), y});
}

#pragma mark Corners

template <class T>
inline Vec2<T> Rect2<T>::topLeft() const {
  return Vec2<T>(left(), top());
}

template <class T>
inline Vec2<T> Rect2<T>::topRight() const {
  return Vec2<T>(right(), top());
}

template <class T>
inline Vec2<T> Rect2<T>::bottomLeft() const {
  return Vec2<T>(left(), bottom());
}

template <class T>
inline Vec2<T> Rect2<T>::bottomRight() const {
  return Vec2<T>(right(), bottom());
}

#pragma mark Canonical form

template <class T>
inline Rect2<T>& Rect2<T>::canonicalize() {
  if (width < 0) {
    x += width;
    width = -width;
  }
  if (height < 0) {
    y += height;
    height = -height;
  }
  return *this;
}

template <class T>
inline Rect2<Promote<T>> Rect2<T>::canonicalized() const {
  return Rect2<Promote<T>>(*this).canonicalize();
}

#pragma mark Translation

template <class T>
inline Rect2<T>& Rect2<T>::translate(T offset) {
  origin += offset;
  return *this;
}

template <class T>
inline Rect2<T>& Rect2<T>::translate(T dx, T dy) {
  x += dx;
  y += dy;
  return *this;
}

template <class T>
inline Rect2<T>& Rect2<T>::translate(const Vec2<T>& offset) {
  origin += offset;
  return *this;
}

template <class T>
template <class U>
inline Rect2<Promote<T, U>> Rect2<T>::translated(U offset) const {
  return Rect2<Promote<T, U>>(*this).translate(offset);
}

template <class T>
template <class U>
inline Rect2<Promote<T, U>> Rect2<T>::translated(U dx, U dy) const {
  return Rect2<Promote<T, U>>(*this).translate(dx, dy);
}

template <class T>
template <class U>
inline Rect2<Promote<T, U>> Rect2<T>::translated(const Vec2<U>& offset) const {
  return Rect2<Promote<T, U>>(*this).translate(offset);
}

#pragma mark Scaling

template <class T>
inline Rect2<T>& Rect2<T>::scale(T scale) {
  size *= scale;
  return *this;
}

template <class T>
inline Rect2<T>& Rect2<T>::scale(T sx, T sy) {
  width *= sx;
  height *= sy;
  return *this;
}

template <class T>
inline Rect2<T>& Rect2<T>::scale(const Vec2<T>& scale) {
  size *= scale;
  return *this;
}

template <class T>
template <class U>
inline Rect2<Promote<T, U>> Rect2<T>::scaled(U scale) const {
  return Rect2<Promote<T, U>>(*this).scale(scale);
}

template <class T>
template <class U>
inline Rect2<Promote<T, U>> Rect2<T>::scaled(U sx, U sy) const {
  return Rect2<Promote<T, U>>(*this).scale(sx, sy);
}

template <class T>
template <class U>
inline Rect2<Promote<T, U>> Rect2<T>::scaled(const Vec2<U>& scale) const {
  return Rect2<Promote<T, U>>(*this).scale(scale);
}

#pragma mark Containment

template <class T>
template <class U>
inline bool Rect2<T>::contains(const Vec2<U>& point) const {
  return !(point.x < minX() || maxX() < point.x ||
           point.y < minY() || maxY() < point.y);
}

#pragma mark Stream

template <class T>
inline std::ostream& operator<<(std::ostream& os, const Rect2<T>& other) {
  return os << "( " << other.origin << ", " << other.size << " )";
}

}  // namespace math

using math::Rect;
using math::Rect2;
using math::Rect2i;
using math::Rect2f;
using math::Rect2d;

using math::Rectangle;
using math::Rectangle2;
using math::Rectangle2i;
using math::Rectangle2f;
using math::Rectangle2d;

}  // namespace takram

#endif  // TAKRAM_MATH_RECTANGLE2_H_