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
		ilm::f32x4 output0;
		bool result
	};

	static entry Set[] = 
	{
		{ilm::f32x4(0.0f), ilm::f32x4(0.0f, 0.0f, 0.0f, 0.0f), },
	};

	int test()
	{
		int Error(0);

		

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

