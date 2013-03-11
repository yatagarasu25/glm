///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2013-03-11
// Updated : 2013-03-11
// Licence : This source is under MIT licence
// File    : test/ilm/ilm_f32x4_ctr.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <glm/ilm.hpp>
#include <cstdio>
#include <vector>

namespace equal_op
{
	struct entry
	{
		ilm::f32x4 input0;
		ilm::f32x4 input1;
		bool output0;
	};

	static entry Set[] = 
	{
		{ilm::f32x4(), ilm::f32x4(0.0f), true},
		{ilm::f32x4(0.0f), ilm::f32x4(0.0f, 0.0f, 0.0f, 0.0f), true},
		{ilm::f32x4(1.0f), ilm::f32x4(1.0f, 1.0f, 1.0f, 1.0f), true},
		{ilm::f32x4(1.0f, 2.0f, 3.0f, 4.0f), ilm::f32x4(1.0f, 2.0f, 3.0f, 4.0f), true},
		{ilm::f32x4(1.0f, 2.0f, 3.0f, 4.0f), ilm::f32x4(1.0f, 2.0f, 3.0f, 8.0f), false},
		{ilm::f32x4(1.0f, 2.0f, 3.0f, 4.0f), ilm::f32x4(1.0f, 2.5f, 3.0f, 4.0f), false},
		{ilm::f32x4(1.0f, 2.0f, 3.0f, 4.0f), ilm::f32x4(-1.0f, 2.5f, 3.0f, 4.0f), false},
		{ilm::f32x4(1.5f, 2.3f, 3.2f, 4.9f), ilm::f32x4(1.1f, 2.5f, 3.8f, 4.1f), false}
	};

	int test()
	{
		int Error(0);

		for(std::size_t i = 0; i < sizeof(Set) /  sizeof(entry); ++i)
		{
			bool Result = Set[i].input0 == Set[i].input1;
			Error += Result == Set[i].output0 ? 0 : 1;
		}

		return Error;
	}
}

int main()
{
	int Error(0);

	Error += equal_op::test();

	{
		ilm::f32x4 a(0.0f);
		ilm::f32x4 b(0.0f, 0.0f, 0.0f, 0.0f);
		Error += a == b ? 0 : 1;
		Error += a != b ? 1 : 0;
	}

	return Error;
}

