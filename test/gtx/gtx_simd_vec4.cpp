///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-09-16
// Updated : 2010-09-16
// Licence : This source is under MIT licence
// File    : test/gtx/simd-vec4.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#define GLM_FORCE_AVX
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtx/simd_vec4.hpp>
#include <cstdio>
#include <ctime>
#include <vector>

#if(GLM_ARCH != GLM_ARCH_PURE)

__m128 f32x4_dp_p_sse2(__m128 const & a, __m128 const & b)
{
	__m128 mul0 = _mm_mul_ps(a, b);
	__m128 swp0 = _mm_shuffle_ps(mul0, mul0, _MM_SHUFFLE(2, 3, 0, 1));
	__m128 add0 = _mm_add_ps(mul0, swp0);
	__m128 swp1 = _mm_shuffle_ps(add0, add0, _MM_SHUFFLE(0, 1, 2, 3));
	__m128 add1 = _mm_add_ps(add0, swp1);
	return add1;
}

__m128 f32x4_dp_p_sse3(__m128 const & a, __m128 const & b)
{
	__m128 mul0 = _mm_mul_ps(a, b);
	__m128 hadd0 = _mm_hadd_ps(mul0, mul0);
	__m128 hadd1 = _mm_hadd_ps(hadd0, hadd0);
	return hadd1;
}

__m128 f32x4_dp_p_sse4(__m128 const & a, __m128 const & b)
{
	__m128 dot0 = _mm_dp_ps(a, b, 0xff);
	return dot0;
}

int perf_dp()
{
	std::size_t Count(100000);
	std::size_t Items(1000);

	std::vector<__m128> init_a;
	init_a.resize(Items);
	std::vector<__m128> init_b;
	init_b.resize(Items);
	std::vector<__m128> a;
	a.resize(Items);
	std::vector<__m128> b;
	b.resize(Items);

	// init
	{
		for(std::size_t i = 0; i < b.size(); ++i)
		{
			glm::vec4 v = glm::linearRand(glm::vec4(-1.0f), glm::vec4(1.0f));
			init_a[i] = _mm_set_ps(v.x, v.y, v.z, v.w);
		}

		for(std::size_t i = 0; i < b.size(); ++i)
		{
			glm::vec4 v = glm::linearRand(glm::vec4(-1.0f), glm::vec4(1.0f));
			init_b[i] = _mm_set_ps(v.x, v.y, v.z, v.w);
		}
	}

	// sse2
	{
		a = init_a;
		b = init_b;

		std::clock_t StartTime = std::clock();

		for(std::size_t j = 0; j < Count; ++j)
		for(std::size_t i = 0; i < b.size(); ++i)
			b[i] = f32x4_dp_p_sse2(a[i], b[i]);

		std::clock_t EndTime = std::clock();

		printf("dot sse2 %d\n", EndTime - StartTime);
	}

	// sse3
	{
		a = init_a;
		b = init_b;

		std::clock_t StartTime = std::clock();

		for(std::size_t j = 0; j < Count; ++j)
		for(std::size_t i = 0; i < b.size(); ++i)
			b[i] = f32x4_dp_p_sse3(a[i], b[i]);

		std::clock_t EndTime = std::clock();

		printf("dot sse3 %d\n", EndTime - StartTime);
	}

	// sse4
	{
		a = init_a;
		b = init_b;

		std::clock_t StartTime = std::clock();

		for(std::size_t j = 0; j < Count; ++j)
		for(std::size_t i = 0; i < b.size(); ++i)
			b[i] = f32x4_dp_p_sse4(a[i], b[i]);

		std::clock_t EndTime = std::clock();

		printf("dot sse4 %d\n", EndTime - StartTime);
	}

	return 0;
}

int main()
{
	glm::simdVec4 A1(0.0f, 0.1f, 0.2f, 0.3f);
	glm::simdVec4 B1(0.4f, 0.5f, 0.6f, 0.7f);
	glm::simdVec4 C1 = A1 + B1;
	glm::simdVec4 D1 = A1.swizzle<glm::X, glm::Z, glm::Y, glm::W>();
	glm::simdVec4 E1(glm::vec4(1.0f));
	glm::vec4 F1 = glm::vec4_cast(E1);
	//glm::vec4 G1(E1);

	//printf("A1(%2.3f, %2.3f, %2.3f, %2.3f)\n", A1.x, A1.y, A1.z, A1.w);
	//printf("B1(%2.3f, %2.3f, %2.3f, %2.3f)\n", B1.x, B1.y, B1.z, B1.w);
	//printf("C1(%2.3f, %2.3f, %2.3f, %2.3f)\n", C1.x, C1.y, C1.z, C1.w);
	//printf("D1(%2.3f, %2.3f, %2.3f, %2.3f)\n", D1.x, D1.y, D1.z, D1.w);

	int Error(0);

	Error += perf_dp();

	while(true);

	return Error;
}

#else

int main()
{
	int Error(0);

	return Error;
}

#endif//(GLM_ARCH != GLM_ARCH_PURE)
