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
/// @ref ilm
/// @file glm/ilm/type.hpp
/// @date 2013-03-11 / 2013-03-11
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#ifndef ILM_TYPE_INCLUDED
#define ILM_TYPE_INCLUDED

#include "../core/setup.hpp"

namespace ilm
{
	typedef __m128 __m128f;
	struct nop {};

	class f32x4;
	class i32x4;
	class b32x4;
	class b128x1;

	// Storage of 4 floats
	class f32x4
	{
	public:
		typedef __m128 data_type;
		typedef float value_type;

		f32x4(nop const &){}
		f32x4() : Data(_mm_setzero_ps()){}
		f32x4(i32x4 const & x);
		f32x4(data_type const & x);
		f32x4(value_type x);
		f32x4(value_type x, value_type y, value_type z, value_type w) : Data(_mm_set_ps(w, z, y, x)){}

		operator data_type() const{return this->Data;}

	private:
		data_type Data;
	};

	// Storage of 4 integers
	class i32x4
	{
	public:
		typedef __m128i data_type;
		typedef int value_type;

		i32x4(nop const &){}
		i32x4() : Data(_mm_setzero_si128()){}
		i32x4(f32x4 const & x);
		i32x4(data_type const & x);
		i32x4(value_type x);
		i32x4(value_type x, value_type y, value_type z, value_type w) : Data(_mm_set_epi32(w, z, y, x)){}

		operator data_type() const{return this->Data;}

	private:
		data_type Data;
	};

	// Storage of 4 32bit bitfields
	class b32x4
	{
	public:
		typedef __m128 data_type;
		typedef bool value_type;

		b32x4(nop const &){}
		b32x4() : Data(_mm_setzero_ps()){}
		b32x4(b128x1 const & x);
		b32x4(f32x4 const & x);
		b32x4(i32x4 const & x);
		b32x4(data_type const & x) : Data(x){}
		b32x4(value_type x) : Data(x ? _mm_cmpneq_ps(_mm_setzero_ps(), _mm_setzero_ps()) : _mm_setzero_ps()){}

		operator data_type() const{return this->Data;}

	private:
		data_type Data;
	};

	// Storage of a 128bit bitfield
	class b128x1
	{
	public:
		typedef __m128 data_type;
		typedef bool value_type;

		b128x1(nop const &){}
		b128x1() : Data(_mm_setzero_ps()){}
		b128x1(f32x4 const & x);
		b128x1(i32x4 const & x);
		b128x1(b32x4 const & x);
		b128x1(data_type x) : Data(x){}
		b128x1(value_type x) : Data(x ? _mm_cmpneq_ps(_mm_setzero_ps(), _mm_setzero_ps()) : _mm_setzero_ps()){}

		operator data_type() const{return this->Data;}

	private:
		data_type Data;
	};

	// f32x4 definition
	f32x4::f32x4(i32x4 const & x) : Data(_mm_castsi128_ps(x)){}
	f32x4::f32x4(data_type const & x) : Data(x){}
	f32x4::f32x4(value_type x) : Data(_mm_set1_ps(x)){}

	// i32x4 definition
	i32x4::i32x4(f32x4 const & x) : Data(_mm_castps_si128(x)){}
	i32x4::i32x4(data_type const & x) : Data(x){}
	i32x4::i32x4(value_type x) : Data(_mm_set1_epi32(x)){}

	// b32x4 definition
	b32x4::b32x4(b128x1 const & x) : Data(x){}
	b32x4::b32x4(f32x4 const & x) : Data(x){}
	b32x4::b32x4(i32x4 const & x) : Data(_mm_castsi128_ps(x)){}

	// b128x1 definition
	b128x1::b128x1(f32x4 const & x) : Data(x){}
	b128x1::b128x1(i32x4 const & x) : Data(_mm_castsi128_ps(x)){}
	b128x1::b128x1(b32x4 const & x) : Data(x){}

	inline bool all(f32x4 const & a)
	{
		__m128i cst0 = _mm_castps_si128(a);
		__m128i srl0 = _mm_srli_si128(cst0, sizeof(__m128f) >> 1);
		__m128i cmp0 = _mm_and_si128(cst0, srl0);
		__m128i srl1 = _mm_srli_si128(cmp0, sizeof(float));
		__m128i cmp1 = _mm_and_si128(cmp0, srl1);
		int cmp2 = _mm_cvtsi128_si32(cmp1);
		return cmp2 ? true : false;
	}

	inline bool any(f32x4 const & a)
	{
		__m128i cst0 = _mm_castps_si128(a);
		__m128i srl0 = _mm_srli_si128(cst0, sizeof(__m128f) >> 1);
		__m128i cmp0 = _mm_or_si128(cst0, srl0);
		__m128i srl1 = _mm_srli_si128(cmp0, sizeof(float));
		__m128i cmp1 = _mm_or_si128(cmp0, srl1);
		int cmp2 = _mm_cvtsi128_si32(cmp1);
		return cmp2 ? true : false;
	}

	inline bool operator==(f32x4 const & a, f32x4 const & b)
	{
		__m128f cmp0 = _mm_cmpeq_ps(a, b);
		return all(cmp0);
	}

	inline bool operator!=(f32x4 const & a, f32x4 const & b)
	{
		__m128f cmp0 = _mm_cmpneq_ps(a, b);
		return any(cmp0);
	}


/*
	inline b32x4 all(b32x4 const & v)
	{
		__m128i cst0 = _mm_castps_si128(v);
		__m128i sll0 = _mm_srli_si128(cst0, sizeof(f32x4) >> 1);
		__m128i cmp0 = _mm_and_si128(cst0, sll0);
		__m128i sll1 = _mm_srli_si128(cst0, sizeof(float));
		__m128i cmp1 = _mm_cmpeq_epi32(cmp0, sll1);
		return cmp1;
	}

	inline bool operator==(f32x4 const & a, f32x4 const & b)
	{
		f32x4 cmp0 = _mm_cmpeq_ps(a, b);
		i32x4 cst0 = _mm_castps_si128(cmp0);
		i32x4 sll0 = _mm_srli_si128(cst0, sizeof(f32x4) >> 1);
		i32x4 cmp1 = _mm_and_si128(cst0, sll0);
		i32x4 sll1 = _mm_srli_si128(cst0, sizeof(float));
		f32x4 cst1 = _mm_castsi128_ps(cmp1);
		f32x4 cst2 = _mm_castsi128_ps(sll1);
		int cmp2 = _mm_comieq_ss(cst1, cst2);
		return cmp2 ? true : false;
	}

	inline bool operator!=(f32x4 const & a, f32x4 const & b)
	{
		f32x4 cmp0 = _mm_cmpneq_ps(a, b);
		i32x4 cst0 = _mm_castps_si128(cmp0);
		i32x4 sll0 = _mm_srli_si128(cst0, sizeof(f32x4) >> 1);
		i32x4 cmp1 = _mm_and_si128(cst0, sll0);
		i32x4 sll1 = _mm_srli_si128(cst0, sizeof(float));
		f32x4 cst1 = _mm_castsi128_ps(cmp1);
		f32x4 cst2 = _mm_castsi128_ps(sll1);
		int cmp2 = _mm_comieq_ss(cst1, cst2);
		return cmp2 ? true : false;
	}
*/
#if(GLM_ARCH & GLM_ARCH_AVX)
	struct f64x4
	{
		typedef __m256d data_type;
		typedef double value_type;

		f64x4(nop const &){}
		f64x4() : Data(_mm256_setzero_pd()){}
		f64x4(data_type x) : Data(x){}
		f64x4(value_type x) : Data(_mm256_set1_pd(x)){}
		f64x4(value_type x, value_type y, value_type z, value_type w) : Data(_mm256_set_pd(w, z, y, x)){}

		operator data_type() const{return this->Data;}

		data_type Data;
	};
#elif(GLM_ARCH & GLM_ARCH_SSE2)
	struct f64x4
	{
		typedef __m128d data_type[2];
		typedef double value_type;

		f64x4(nop const &){}
		f64x4(){
			this->Data[0] = _mm_setzero_pd();
			this->Data[1] = _mm_setzero_pd();
		}
		f64x4(data_type x) : Data(x){
			this->Data[0] = x[0];
			this->Data[1] = x[1];
		}
		f64x4(value_type x){
			this->Data[0] = _mm_set1_pd(x);
			this->Data[1] = _mm_set1_pd(x);
		}
		f64x4(value_type x, value_type y, value_type z, value_type w){
			this->Data[0] = _mm_set_pd(y, x);
			this->Data[1] = _mm_set_pd(w, z);
		}

		operator data_type() const{return this->Data;}

		data_type Data;
	};
#else
	struct f64x4
	{
		typedef glm::dvec4 data_type;
		typedef double value_type;

		f64x4(nop const &){}
		f64x4() : Data(0){}
		f64x4(value_type x) : Data(x){}
		f64x4(value_type x, value_type y, value_type z, value_type w) : Data(x, y, z, w)){}

		operator data_type() const{return this->Data;}

		data_type Data;
	};
#endif

/*
	struct i32x4
	{
		typedef __m128i data_type;
		typedef int value_type;

		i32x4(nop const &){}

		i32x4() : Data(_mm_xor_ps(this->Data, this->Data)){}
		i32x4(value_type x) : Data(_mm_set1_ps(x)){}
		i32x4(value_type x, value_type y, value_type z, value_type w) : Data(_mm_set_ps(w, z, y, x)){}

		operator data_type() const{return this->Data;}

		data_type Data;
	};
*/
}//namespace ilm

#include "type.inl"

#endif//ILM_TYPE_INCLUDED
