Math
====

A collection of C++ classes and functions to compute common mathematical operations and transformations that interoperate with common creative-coding libraries.

[![Build Status](https://travis-ci.org/shotamatsuda/math.svg)](https://travis-ci.org/shotamatsuda/math) [![License](http://img.shields.io/badge/license-MIT-lightgrey.svg?style=flat
)](http://mit-license.org)

### Classes

- [`shotamatsuda::math::Random`](src/shotamatsuda/math/random.h)
- [`shotamatsuda::math::Vec2`](src/shotamatsuda/math/vector2.h)
- [`shotamatsuda::math::Vec3`](src/shotamatsuda/math/vector3.h)
- [`shotamatsuda::math::Vec4`](src/shotamatsuda/math/vector4.h)
- [`shotamatsuda::math::Size2`](src/shotamatsuda/math/size2.h)
- [`shotamatsuda::math::Size3`](src/shotamatsuda/math/size3.h)
- [`shotamatsuda::math::Line2`](src/shotamatsuda/math/line2.h)
- [`shotamatsuda::math::Line3`](src/shotamatsuda/math/line3.h)
- [`shotamatsuda::math::Triangle2`](src/shotamatsuda/math/triangle2.h)
- [`shotamatsuda::math::Triangle3`](src/shotamatsuda/math/triangle3.h)
- [`shotamatsuda::math::Rectangle2`](src/shotamatsuda/math/rectangle2.h)
- [`shotamatsuda::math::Circle2`](src/shotamatsuda/math/circle2.h)

## Examples

### Random

[Random](src/shotamatsuda/math/random.h) is a wrapper of STL’s random number library designed for providing a simpler interface.

```cpp
#include <limits>

#include "shotamatsuda/math/random.h"

shotamatsuda::Random<> random;

// Uniform distribution ranges from 0 to the max int
random.uniform<int>(std::numeric_limits<int>::max());

// Gaussian (normal) distribution of mean 0 and standard deviation 1
random.gaussian<double>();
```

### Return Type Promotion

All types in this module promote the return type of arithmetic operators in the same way built-in arithmetic types do. Some member functions like `magnitude()` also promote the return type. The magnitude of a vector of integral type is promoted to double, but that of float remains float.

```cpp
#include "shotamatsuda/math/vector.h"

shotamatsuda::Vec2i veci;
shotamatsuda::Vec2d vecd;
shotamatsuda::Vec2f vecf;

veci + veci;  // Vec2<double>
veci + vecf;  // Vec2<double>
veci + vecd;  // Vec2<double>
vecf + vecf;  // Vec2<float>
vecf + vecd;  // Vec2<double>
```

### Implicit Type Conversions

[Vec](src/shotamatsuda/math/vector.h), [Size](src/shotamatsuda/math/size.h) and [Rect](src/shotamatsuda/math/rectangle.h) are implicitly convertible to/from corresponding types of OpenCV, openFrameworks and Cinder.

| | OpenCV | openFrameworks | Cinder
|---------|------------|----------------|----------
| [Vec2](src/shotamatsuda/math/vector2.h) | cv::Point | ofVec2f | ci::Vec2
| [Vec3](src/shotamatsuda/math/vector3.h) | cv::Point3 | ofVec3f | ci::Vec3
| [Vec4](src/shotamatsuda/math/vector4.h) | | ofVec4f | ci::Vec4
| [Size2](src/shotamatsuda/math/size2.h) | cv::Size   | |
| [Size3](src/shotamatsuda/math/size3.h) | | |
| [Rect2](src/shotamatsuda/math/rectangle2.h) | cv::Rect | ofRectangle | ci::Rect

## Setup Guide

Run "setup.sh" inside "script" directory to initialize submodules and build dependant libraries.

### Submodules

- [Google Test Framework](https://github.com/google/googletest)

## License

The MIT License

Copyright (C) 2013-2017 Shota Matsuda

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
