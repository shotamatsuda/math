//
//  shotamatsuda/math/size2.h
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
#ifndef SHOTAMATSUDA_MATH_SIZE2_H_
#define SHOTAMATSUDA_MATH_SIZE2_H_

#include <cmath>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <tuple>

#if SHOTAMATSUDA_HAS_OPENCV
#include "opencv2/core/core.hpp"
#endif  // SHOTAMATSUDA_HAS_OPENCV

#if SHOTAMATSUDA_HAS_OPENFRAMEWORKS
#include "ofVec2f.h"
#endif  // SHOTAMATSUDA_HAS_OPENFRAMEWORKS

#if SHOTAMATSUDA_HAS_CINDER
#include "cinder/Vec.h"
#endif  // SHOTAMATSUDA_HAS_CINDER

#if SHOTAMATSUDA_HAS_COREGRAPHICS
#include <CoreGraphics/CoreGraphics.h>
#endif  // SHOTAMATSUDA_HAS_COREGRAPHICS

#include "shotamatsuda/math/axis.h"
#include "shotamatsuda/math/enablers.h"
#include "shotamatsuda/math/promotion.h"
#include "shotamatsuda/math/vector.h"

namespace shotamatsuda {
namespace math {

template <class T, int D>
class Size;

template <class T>
using Size2 = Size<T, 2>;
template <class T>
using Size3 = Size<T, 3>;

template <class T>
class Size<T, 2> final {
 public:
  using Type = T;
  using Iterator = typename Vec2<T>::Iterator;
  using ConstIterator = typename Vec2<T>::ConstIterator;
  using ReverseIterator = typename Vec2<T>::ReverseIterator;
  using ConstReverseIterator = typename Vec2<T>::ConstReverseIterator;
  static constexpr const auto dimensions = Vec2<T>::dimensions;

 public:
  Size();
  explicit Size(T value);
  Size(T width, T height);
  explicit Size(const T *values, int size = 2);
  template <class... Args>
  Size(const std::tuple<Args...>& tuple);
  Size(std::initializer_list<T> list);

  // Implicit conversion
  template <class U>
  Size(const Size2<U>& other);

#if SHOTAMATSUDA_HAS_OPENCV
  template <class U>
  Size(const cv::Size_<U>& other);
  operator cv::Size_<T>() const;
#endif  // SHOTAMATSUDA_HAS_OPENCV

#if SHOTAMATSUDA_HAS_COREGRAPHICS
  Size(const CGSize& other);
  operator CGSize() const;
#endif  // SHOTAMATSUDA_HAS_COREGRAPHICS

  // Explicit conversion
  template <class U>
  explicit Size(const Size3<U>& other);
  explicit Size(const Vec2<T>& other);
  explicit Size(const Vec3<T>& other);
  explicit Size(const Vec4<T>& other);

#if SHOTAMATSUDA_HAS_OPENFRAMEWORKS
  explicit Size(const ofVec2f& other);
  explicit operator ofVec2f() const;
#endif  // SHOTAMATSUDA_HAS_OPENFRAMEWORKS

#if SHOTAMATSUDA_HAS_CINDER
  template <class U>
  explicit Size(const ci::Vec2<U>& other);
  explicit operator ci::Vec2<T>() const;
#endif  // SHOTAMATSUDA_HAS_CINDER

  // Copy semantics
  Size(const Size&) = default;
  Size& operator=(const Size&) = default;

  // Factory
  static Size min();
  static Size max();
  static Size random();
  static Size random(T max);
  static Size random(T min, T max);
  template <class Random>
  static Size random(Random *random);
  template <class Random>
  static Size random(T max, Random *random);
  template <class Random>
  static Size random(T min, T max, Random *random);

  // Mutators
  void set(T value);
  void set(T width, T height);
  void set(const T *values, int size = 2);
  template <class... Args>
  void set(const std::tuple<Args...>& tuple);
  void set(std::initializer_list<T> list);
  void reset();

  // Element access
  T& operator[](int index) { return at(index); }
  const T& operator[](int index) const { return at(index); }
  T& operator[](Axis axis) { return at(axis); }
  const T& operator[](Axis axis) const { return at(axis); }
  T& at(int index);
  const T& at(int index) const;
  T& at(Axis axis);
  const T& at(Axis axis) const;
  T& front() { return vector.front(); }
  const T& front() const { return vector.front(); }
  T& back() { return vector.back(); }
  const T& back() const { return vector.back(); }

  // Comparison
  template <class V, class U = T>
  bool equals(const Size2<U>& other, V tolerance) const;

  // Arithmetic
  Size& operator+=(const Size& other);
  Size& operator-=(const Size& other);
  Size& operator*=(const Size& other);
  Size& operator/=(const Size& other);
  Size2<Promote<T>> operator-() const;

  // Scalar arithmetic
  Size& operator+=(T scalar);
  Size& operator-=(T scalar);
  Size& operator*=(T scalar);
  Size& operator/=(T scalar);

  // Vector arithmetic
  Size& operator+=(const Vec2<T>& other);
  Size& operator-=(const Vec2<T>& other);
  Size& operator*=(const Vec2<T>& other);
  Size& operator/=(const Vec2<T>& other);

  // Attributes
  bool empty() const { return !width && !height; }
  Promote<T> aspect() const;
  Promote<T> area() const;
  Promote<T> diagonal() const;

  // Conversion
  template <class U>
  explicit operator Vec2<U>() { return vector; }
  template <class U>
  explicit operator const Vec2<U>() const { return vector; }

  // Iterator
  Iterator begin() { return std::begin(vector); }
  ConstIterator begin() const { return std::begin(vector); }
  Iterator end() { return std::end(vector); }
  ConstIterator end() const { return std::end(vector); }
  ReverseIterator rbegin() { return std::rbegin(vector); }
  ConstReverseIterator rbegin() const { return std::rbegin(vector); }
  ReverseIterator rend() { return std::rend(vector); }
  ConstReverseIterator rend() const { return std::rend(vector); }

  // Pointer
  T * pointer() { return vector.pointer(); }
  const T * pointer() const { return vector.pointer(); }

 public:
  union {
    Vec2<T> vector;
    struct { T width; T height; };
    struct { T w; T h; };
  };
};

// Comparison
template <class T, class U>
bool operator==(const Size2<T>& lhs, const Size2<U>& rhs);
template <class T, class U>
bool operator!=(const Size2<T>& lhs, const Size2<U>& rhs);
template <class T, class U>
bool operator<(const Size2<T>& lhs, const Size2<U>& rhs);
template <class T, class U>
bool operator>(const Size2<T>& lhs, const Size2<U>& rhs);
template <class T, class U>
bool operator<=(const Size2<T>& lhs, const Size2<U>& rhs);
template <class T, class U>
bool operator>=(const Size2<T>& lhs, const Size2<U>& rhs);

// Arithmetic
template <class T, class U>
Size2<Promote<T, U>> operator+(const Size2<T>& lhs, const Size2<U>& rhs);
template <class T, class U>
Size2<Promote<T, U>> operator-(const Size2<T>& lhs, const Size2<U>& rhs);
template <class T, class U>
Size2<Promote<T, U>> operator*(const Size2<T>& lhs, const Size2<U>& rhs);
template <class T, class U>
Size2<Promote<T, U>> operator/(const Size2<T>& lhs, const Size2<U>& rhs);

// Scalar arithmetic
template <class T, class U, EnableIfScalar<U> * = nullptr>
Size2<Promote<T, U>> operator+(const Size2<T>& lhs, U rhs);
template <class T, class U, EnableIfScalar<U> * = nullptr>
Size2<Promote<T, U>> operator-(const Size2<T>& lhs, U rhs);
template <class T, class U, EnableIfScalar<U> * = nullptr>
Size2<Promote<T, U>> operator*(const Size2<T>& lhs, U rhs);
template <class T, class U, EnableIfScalar<U> * = nullptr>
Size2<Promote<T, U>> operator/(const Size2<T>& lhs, U rhs);
template <class T, class U, EnableIfScalar<T> * = nullptr>
Size2<Promote<T, U>> operator+(T lhs, const Size2<U>& rhs);
template <class T, class U, EnableIfScalar<T> * = nullptr>
Size2<Promote<T, U>> operator-(T lhs, const Size2<U>& rhs);
template <class T, class U, EnableIfScalar<T> * = nullptr>
Size2<Promote<T, U>> operator*(T lhs, const Size2<U>& rhs);
template <class T, class U, EnableIfScalar<T> * = nullptr>
Size2<Promote<T, U>> operator/(T lhs, const Size2<U>& rhs);

// Vector arithmetic
template <class T, class U>
Size2<Promote<T, U>> operator+(const Size2<T>& lhs, const Vec2<U>& rhs);
template <class T, class U>
Size2<Promote<T, U>> operator-(const Size2<T>& lhs, const Vec2<U>& rhs);
template <class T, class U>
Size2<Promote<T, U>> operator*(const Size2<T>& lhs, const Vec2<U>& rhs);
template <class T, class U>
Size2<Promote<T, U>> operator/(const Size2<T>& lhs, const Vec2<U>& rhs);
template <class T, class U>
Vec2<Promote<T, U>> operator+(const Vec2<T>& lhs, const Size2<U>& rhs);
template <class T, class U>
Vec2<Promote<T, U>> operator-(const Vec2<T>& lhs, const Size2<U>& rhs);
template <class T, class U>
Vec2<Promote<T, U>> operator*(const Vec2<T>& lhs, const Size2<U>& rhs);
template <class T, class U>
Vec2<Promote<T, U>> operator/(const Vec2<T>& lhs, const Size2<U>& rhs);

using Size2i = Size2<int>;
using Size2f = Size2<float>;
using Size2d = Size2<double>;

// MARK: -

template <class T>
inline Size<T, 2>::Size() : vector() {}

template <class T>
inline Size<T, 2>::Size(T value) : vector(value) {}

template <class T>
inline Size<T, 2>::Size(T width, T height) : vector(width, height) {}

template <class T>
inline Size<T, 2>::Size(const T *values, int size) : vector(values, size) {}

template <class T>
template <class... Args>
inline Size<T, 2>::Size(const std::tuple<Args...>& tuple) : vector(tuple) {}

template <class T>
inline Size<T, 2>::Size(std::initializer_list<T> list) : vector(list) {}

// MARK: Implicit conversion

template <class T>
template <class U>
inline Size<T, 2>::Size(const Size2<U>& other) : vector(other.vector) {}

#if SHOTAMATSUDA_HAS_OPENCV

template <class T>
template <class U>
inline Size<T, 2>::Size(const cv::Size_<U>& other)
    : vector(other.width, other.height) {}

template <class T>
inline Size<T, 2>::operator cv::Size_<T>() const {
  return cv::Size_<T>(width, height);
}

#endif  // SHOTAMATSUDA_HAS_OPENCV

#if SHOTAMATSUDA_HAS_COREGRAPHICS

template <class T>
inline Size<T, 2>::Size(const CGSize& other)
    : vector(other.width, other.height) {}

template <class T>
inline Size<T, 2>::operator CGSize() const {
  return CGSizeMake(width, height);
}

#endif  // SHOTAMATSUDA_HAS_COREGRAPHICS

// MARK: Explicit conversion

template <class T>
template <class U>
inline Size<T, 2>::Size(const Size3<U>& other) : vector(other.vector) {}

template <class T>
inline Size<T, 2>::Size(const Vec2<T>& other) : vector(other) {}

template <class T>
inline Size<T, 2>::Size(const Vec3<T>& other) : vector(other) {}

template <class T>
inline Size<T, 2>::Size(const Vec4<T>& other) : vector(other) {}

#if SHOTAMATSUDA_HAS_OPENFRAMEWORKS

template <class T>
inline Size<T, 2>::Size(const ofVec2f& other) : vector(other) {}

template <class T>
inline Size<T, 2>::operator ofVec2f() const {
  return ofVec2f(vector);
}

#endif  // SHOTAMATSUDA_HAS_OPENFRAMEWORKS

#if SHOTAMATSUDA_HAS_CINDER

template <class T>
template <class U>
inline Size<T, 2>::Size(const ci::Vec2<U>& other) : vector(other) {}

template <class T>
inline Size<T, 2>::operator ci::Vec2<T>() const {
  return ci::Vec2<T>(vector);
}

#endif  // SHOTAMATSUDA_HAS_CINDER

// MARK: Factory

template <class T>
inline Size2<T> Size<T, 2>::min() {
  return Size(Vec2<T>::min());
}

template <class T>
inline Size2<T> Size<T, 2>::max() {
  return Size(Vec2<T>::max());
}

template <class T>
inline Size2<T> Size<T, 2>::random() {
  return random(&Random<>::shared());
}

template <class T>
inline Size2<T> Size<T, 2>::random(T max) {
  return random(max, &Random<>::shared());
}

template <class T>
inline Size2<T> Size<T, 2>::random(T min, T max) {
  return random(min, max, &Random<>::shared());
}

template <class T>
template <class Random>
inline Size2<T> Size<T, 2>::random(Random *random) {
  return Size(Vec2<T>::random(random));
}

template <class T>
template <class Random>
inline Size2<T> Size<T, 2>::random(T max, Random *random) {
  return Size(Vec2<T>::random(max, random));
}

template <class T>
template <class Random>
inline Size2<T> Size<T, 2>::random(T min, T max, Random *random) {
  return Size(Vec2<T>::random(min, max, random));
}

// MARK: Mutators

template <class T>
inline void Size<T, 2>::set(T value) {
  vector.set(value);
}

template <class T>
inline void Size<T, 2>::set(T width, T height) {
  vector.set(width, height);
}

template <class T>
inline void Size<T, 2>::set(const T *values, int size) {
  vector.set(values, size);
}

template <class T>
template <class... Args>
inline void Size<T, 2>::set(const std::tuple<Args...>& tuple) {
  vector.set(tuple);
}

template <class T>
inline void Size<T, 2>::set(std::initializer_list<T> list) {
  vector.set(list);
}

template <class T>
inline void Size<T, 2>::reset() {
  vector.reset();
}

// MARK: Element access

template <class T>
inline T& Size<T, 2>::at(int index) {
  return vector.at(index);
}

template <class T>
inline const T& Size<T, 2>::at(int index) const {
  return vector.at(index);
}

template <class T>
inline T& Size<T, 2>::at(Axis axis) {
  return at(static_cast<int>(axis));
}

template <class T>
inline const T& Size<T, 2>::at(Axis axis) const {
  return at(static_cast<int>(axis));
}

// MARK: Comparison

template <class T, class U>
inline bool operator==(const Size2<T>& lhs, const Size2<U>& rhs) {
  return lhs.vector == rhs.vector;
}

template <class T, class U>
inline bool operator!=(const Size2<T>& lhs, const Size2<U>& rhs) {
  return lhs.vector != rhs.vector;
}

template <class T, class U>
inline bool operator<(const Size2<T>& lhs, const Size2<U>& rhs) {
  return operator<(lhs.vector, rhs.vector);
}

template <class T, class U>
inline bool operator>(const Size2<T>& lhs, const Size2<U>& rhs) {
  return operator>(lhs.vector, rhs.vector);
}

template <class T, class U>
inline bool operator<=(const Size2<T>& lhs, const Size2<U>& rhs) {
  return lhs.vector <= rhs.vector;
}

template <class T, class U>
inline bool operator>=(const Size2<T>& lhs, const Size2<U>& rhs) {
  return lhs.vector >= rhs.vector;
}

template <class T>
template <class V, class U>
inline bool Size<T, 2>::equals(const Size2<U>& other, V tolerance) const {
  return vector.equals(other.vector);
}

// MARK: Arithmetic

template <class T>
inline Size2<T>& Size<T, 2>::operator+=(const Size& other) {
  vector += other.vector;
  return *this;
}

template <class T>
inline Size2<T>& Size<T, 2>::operator-=(const Size& other) {
  vector -= other.vector;
  return *this;
}

template <class T>
inline Size2<T>& Size<T, 2>::operator*=(const Size& other) {
  vector *= other.vector;
  return *this;
}

template <class T>
inline Size2<T>& Size<T, 2>::operator/=(const Size& other) {
  vector /= other.vector;
  return *this;
}

template <class T>
inline Size2<Promote<T>> Size<T, 2>::operator-() const {
  return Size2<Promote<T>>(-vector);
}

template <class T, class U>
inline Size2<Promote<T, U>> operator+(const Size2<T>& lhs,
                                      const Size2<U>& rhs) {
  return Size2<Promote<T, U>>(lhs.vector + rhs.vector);
}

template <class T, class U>
inline Size2<Promote<T, U>> operator-(const Size2<T>& lhs,
                                      const Size2<U>& rhs) {
  return Size2<Promote<T, U>>(lhs.vector - rhs.vector);
}

template <class T, class U>
inline Size2<Promote<T, U>> operator*(const Size2<T>& lhs,
                                      const Size2<U>& rhs) {
  return Size2<Promote<T, U>>(lhs.vector * rhs.vector);
}

template <class T, class U>
inline Size2<Promote<T, U>> operator/(const Size2<T>& lhs,
                                      const Size2<U>& rhs) {
  return Size2<Promote<T, U>>(lhs.vector / rhs.vector);
}

// MARK: Scalar arithmetic

template <class T>
inline Size2<T>& Size<T, 2>::operator+=(T scalar) {
  vector += scalar;
  return *this;
}

template <class T>
inline Size2<T>& Size<T, 2>::operator-=(T scalar) {
  vector -= scalar;
  return *this;
}

template <class T>
inline Size2<T>& Size<T, 2>::operator*=(T scalar) {
  vector *= scalar;
  return *this;
}

template <class T>
inline Size2<T>& Size<T, 2>::operator/=(T scalar) {
  vector /= scalar;
  return *this;
}

template <class T, class U, EnableIfScalar<U> *>
inline Size2<Promote<T, U>> operator+(const Size2<T>& lhs, U rhs) {
  return Size2<Promote<T, U>>(lhs.vector + rhs);
}

template <class T, class U, EnableIfScalar<U> *>
inline Size2<Promote<T, U>> operator-(const Size2<T>& lhs, U rhs) {
  return Size2<Promote<T, U>>(lhs.vector - rhs);
}

template <class T, class U, EnableIfScalar<U> *>
inline Size2<Promote<T, U>> operator*(const Size2<T>& lhs, U rhs) {
  return Size2<Promote<T, U>>(lhs.vector * rhs);
}

template <class T, class U, EnableIfScalar<U> *>
inline Size2<Promote<T, U>> operator/(const Size2<T>& lhs, U rhs) {
  return Size2<Promote<T, U>>(lhs.vector / rhs);
}

template <class T, class U, EnableIfScalar<T> *>
inline Size2<Promote<T, U>> operator+(T lhs, const Size2<U>& rhs) {
  return Size2<Promote<T, U>>(lhs + rhs.vector);
}

template <class T, class U, EnableIfScalar<T> *>
inline Size2<Promote<T, U>> operator-(T lhs, const Size2<U>& rhs) {
  return Size2<Promote<T, U>>(lhs - rhs.vector);
}

template <class T, class U, EnableIfScalar<T> *>
inline Size2<Promote<T, U>> operator*(T lhs, const Size2<U>& rhs) {
  return Size2<Promote<T, U>>(lhs * rhs.vector);
}

template <class T, class U, EnableIfScalar<T> *>
inline Size2<Promote<T, U>> operator/(T lhs, const Size2<U>& rhs) {
  return Size2<Promote<T, U>>(lhs / rhs.vector);
}

// MARK: Vector arithmetic

template <class T>
inline Size2<T>& Size<T, 2>::operator+=(const Vec2<T>& other) {
  vector += other;
  return *this;
}

template <class T>
inline Size2<T>& Size<T, 2>::operator-=(const Vec2<T>& other) {
  vector -= other;
  return *this;
}

template <class T>
inline Size2<T>& Size<T, 2>::operator*=(const Vec2<T>& other) {
  vector *= other;
  return *this;
}

template <class T>
inline Size2<T>& Size<T, 2>::operator/=(const Vec2<T>& other) {
  vector /= other;
  return *this;
}

template <class T, class U>
inline Size2<Promote<T, U>> operator+(const Size2<T>& lhs, const Vec2<U>& rhs) {
  return Size2<Promote<T, U>>(lhs.vector + rhs);
}

template <class T, class U>
inline Size2<Promote<T, U>> operator-(const Size2<T>& lhs, const Vec2<U>& rhs) {
  return Size2<Promote<T, U>>(lhs.vector - rhs);
}

template <class T, class U>
inline Size2<Promote<T, U>> operator*(const Size2<T>& lhs, const Vec2<U>& rhs) {
  return Size2<Promote<T, U>>(lhs.vector * rhs);
}

template <class T, class U>
inline Size2<Promote<T, U>> operator/(const Size2<T>& lhs, const Vec2<U>& rhs) {
  return Size2<Promote<T, U>>(lhs.vector / rhs);
}

template <class T, class U>
inline Vec2<Promote<T, U>> operator+(const Vec2<T>& lhs, const Size2<U>& rhs) {
  return lhs + rhs.vector;
}

template <class T, class U>
inline Vec2<Promote<T, U>> operator-(const Vec2<T>& lhs, const Size2<U>& rhs) {
  return lhs - rhs.vector;
}

template <class T, class U>
inline Vec2<Promote<T, U>> operator*(const Vec2<T>& lhs, const Size2<U>& rhs) {
  return lhs * rhs.vector;
}

template <class T, class U>
inline Vec2<Promote<T, U>> operator/(const Vec2<T>& lhs, const Size2<U>& rhs) {
  return lhs / rhs.vector;
}

// MARK: Attributes

template <class T>
inline Promote<T> Size<T, 2>::aspect() const {
  return static_cast<Promote<T>>(width) / height;
}

template <class T>
inline Promote<T> Size<T, 2>::area() const {
  return std::abs(static_cast<Promote<T>>(width) * height);
}

template <class T>
inline Promote<T> Size<T, 2>::diagonal() const {
  return vector.magnitude();
}

// MARK: Stream

template <class T>
inline std::ostream& operator<<(std::ostream& os, const Size2<T>& size) {
  return os << size.vector;
}

}  // namespace math

using math::Size;
using math::Size2;
using math::Size2i;
using math::Size2f;
using math::Size2d;

}  // namespace shotamatsuda

template <class T>
struct std::hash<shotamatsuda::math::Size2<T>> {
  std::size_t operator()(const shotamatsuda::math::Size2<T>& value) const {
    std::hash<T> hash;
    return (hash(value.w) << 0) ^ (hash(value.h) << 1);
  }
};

#endif  // SHOTAMATSUDA_MATH_SIZE2_H_
