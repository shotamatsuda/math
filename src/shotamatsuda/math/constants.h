//
//  shotamatsuda/math/constants.h
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
#ifndef SHOTAMATSUDA_MATH_CONSTANTS_H_
#define SHOTAMATSUDA_MATH_CONSTANTS_H_

namespace shotamatsuda {
namespace math {

template <class T = double>
constexpr T e();
template <class T = double>
constexpr T pi();
template <class T = double>
constexpr T half_pi();
template <class T = double>
constexpr T third_pi();
template <class T = double>
constexpr T quarter_pi();
template <class T = double>
constexpr T two_pi();
template <class T = double>
constexpr T tau();
template <class T = double>
constexpr T degree();
template <class T = double>
constexpr T radian();

// MARK: -

template <class T>
inline constexpr T e() {
  return 2.718281828459045235360287471352662497e+00L;
}

template <class T>
inline constexpr T pi() {
  return 3.141592653589793238462643383279502884e+00L;
}

template <class T>
inline constexpr T half_pi() {
  return 1.570796326794896619231321691639751442e+00L;
}

template <class T>
inline constexpr T third_pi() {
  return 1.047197551196597746154214461093167628e+00L;
}

template <class T>
inline constexpr T quarter_pi() {
  return 0.785398163397448309615660845819875721+00L;
}

template <class T>
inline constexpr T two_pi() {
  return 6.283185307179586476925286766559005768e+00L;
}

template <class T>
inline constexpr T tau() {
  return 6.283185307179586476925286766559005768e+00L;
}

template <class T>
inline constexpr T degree() {
  return 1.745329251994329576923690768488612713e-02L;
}

template <class T>
inline constexpr T radian() {
  return 5.729577951308232087679815481410517033e+01L;
}

}  // namespace math
}  // namespace shotamatsuda

#endif  // SHOTAMATSUDA_MATH_CONSTANTS_H_
