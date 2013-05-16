///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Mathematics (glm.g-truc.net)
///
/// Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// @ref core
/// @file glm/core/dummy.cpp
/// @date 2011-01-19 / 2011-06-15
/// @author Christophe Riccio
///
/// GLM is a header only library. There is nothing to compile. 
/// dummy.cpp exist only a wordaround for CMake file.
///////////////////////////////////////////////////////////////////////////////////

#define GLM_MESSAGES
#include "../glm.hpp"

<<<<<<< refs/remotes/origin/simd
//#error "GLM is a header only library"

int main()
{

=======
#include <emmintrin.h>
#include <cstddef>
struct float4
{
float4(){}
float4(float const & s) :
x(s), y(s), z(s), w(s)
{}
float4(float const & x, float const & y, float const & z, float const & w) :
x(x), y(y), z(z), w(w)
{}
float operator[](std::size_t i) const
{
return (&x)[i];
}
union
{
struct {float r, g, b, a;};
struct {float s, t, p, q;};
struct {float x, y, z, w;};
__m128 data;
};
};

inline float4 operator*(float4 const & a, float4 const & b)
{
return float4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

float4 mul_intrinsic(float4 const m[4], float4 const & v)
{
__m128 v0 = _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(0, 0, 0, 0));
__m128 v1 = _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(1, 1, 1, 1));
__m128 v2 = _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(2, 2, 2, 2));
__m128 v3 = _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(3, 3, 3, 3));
__m128 m0 = _mm_mul_ps(m[0].data, v0);
__m128 m1 = _mm_mul_ps(m[1].data, v1);
__m128 a0 = _mm_add_ps(m0, m1);
__m128 m2 = _mm_mul_ps(m[2].data, v2);
__m128 m3 = _mm_mul_ps(m[3].data, v3);
__m128 a1 = _mm_add_ps(m2, m3);
__m128 a2 = _mm_add_ps(a0, a1);
float4 f;
f.data = a2;
return f;
}
float4 mul_cpp(float4 const m[4], float4 const & v)
{
return float4(
m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3],
m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3],
m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3],
m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3]);
}
float4 mul_inst_like(float4 const m[4], float4 const & v)
{
float4 const Mov0(v[0]);
float4 const Mov1(v[1]);
float4 const Mul0 = m[0] * Mov0;
float4 const Mul1 = m[1] * Mov1;
float4 const Add0 = Mul0 * Mul1;
float4 const Mov2(v[2]);
float4 const Mov3(v[3]);
float4 const Mul2 = m[2] * Mov2;
float4 const Mul3 = m[3] * Mov3;
float4 const Add1 = Mul2 * Mul3;
float4 const Add2 = Add0 * Add1;
return Add2;
}
int main()
{
return 0;
>>>>>>> local
}

