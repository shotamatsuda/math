//
//  shotamatsuda/math/enablers.h
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
#ifndef SHOTAMATSUDA_MATH_ENABLERS_H_
#define SHOTAMATSUDA_MATH_ENABLERS_H_

#include <type_traits>

namespace shotamatsuda {
namespace math {

template <class T, class U = void>
using EnableIfScalar = typename std::enable_if<
    std::is_scalar<T>::value, U>::type;
template <class T, class U = void>
using EnableIfIntegral = typename std::enable_if<
    std::is_integral<T>::value, U>::type;
template <class T, class U = void>
using EnableIfFloating = typename std::enable_if<
    std::is_floating_point<T>::value, U>::type;

}  // namespace math

using math::EnableIfScalar;
using math::EnableIfIntegral;
using math::EnableIfFloating;

}  // namespace shotamatsuda

#endif  // SHOTAMATSUDA_MATH_ENABLERS_H_