///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2012 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-09-16
// Updated : 2010-09-16
// Licence : This source is under MIT licence
// File    : test/gtx/simd-vec4.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

//#define GLM_SIMD_NO_TYPE_UNION
//#define GLM_FORCE_SSE4
#include <glm/glm.hpp>
#include <glm/gtx/simd_vec4.hpp>
#include <cstdio>
#include <ctime>
#include <vector>

#if(GLM_ARCH != GLM_ARCH_PURE)

void test_sizeof()
{
    bool result = sizeof(glm::simdVec4) == 16;
    printf("sizeof(glm::simdVec4) == 16 : %s\n", result ? "yes" : "no");
}

#ifndef GLM_SIMD_NO_TYPE_UNION
void test_data_equals_xyzw()
{
    glm::simdVec4 subject(1.0f, 2.0f, 3.0f, 4.0f);
    bool result =
        subject.Data.m128_f32[0] == subject.x &&
        subject.Data.m128_f32[1] == subject.y &&
        subject.Data.m128_f32[2] == subject.z &&
        subject.Data.m128_f32[3] == subject.w;

    printf("Data == xyzw : %s\n", result ? "yes" : "no");
}
#endif

void test_accessors()
{
    glm::simdVec4 subject(0.0f, 0.0f, 0.0f, 0.0f);
    subject[0] += 1.0f;
    subject[1] += 2.0f;
    subject[2] += 3.0f;
    subject[3] += 4.0f;

    bool result =
        subject[0] == 1.0f &&
        subject[1] == 2.0f &&
        subject[2] == 3.0f &&
        subject[3] == 4.0f;

    printf("operator[] working : %s\n", result ? "yes" : "no");
}



void test_add()
{
    glm::simdVec4 subjectA(1.0f, 2.0f, 3.0f, 4.0f);
    glm::simdVec4 subjectB(1.0f, 2.0f, 3.0f, 4.0f);
    glm::simdVec4 answer = subjectA + subjectB;

    bool result =
        answer[0] == 2.0f &&
        answer[1] == 4.0f &&
        answer[2] == 6.0f &&
        answer[3] == 8.0f;

    printf("{1.0, 2.0, 3.0, 4.0,} + {1.0, 2.0, 3.0, 4.0} == {2.0, 4.0, 6.0, 8.0} : %s\n", result ? "yes" : "no");
}

void test_sub()
{
    glm::simdVec4 subjectA(1.0f, 2.0f, 3.0f, 4.0f);
    glm::simdVec4 subjectB(1.0f, 2.0f, 3.0f, 4.0f);
    glm::simdVec4 answer = subjectA - subjectB;

    bool result =
        answer[0] == 0.0f &&
        answer[1] == 0.0f &&
        answer[2] == 0.0f &&
        answer[3] == 0.0f;

    printf("{1.0, 2.0, 3.0, 4.0,} - {1.0, 2.0, 3.0, 4.0} == {0.0, 0.0, 0.0, 0.0} : %s\n", result ? "yes" : "no");
}

void test_mul()
{
    glm::simdVec4 subjectA(1.0f, 2.0f, 3.0f, 4.0f);
    glm::simdVec4 subjectB(1.0f, 2.0f, 3.0f, 4.0f);
    glm::simdVec4 answer = subjectA * subjectB;

    bool result =
        answer[0] == 1.0f &&
        answer[1] == 4.0f &&
        answer[2] == 9.0f &&
        answer[3] == 16.0f;

    printf("{1.0, 2.0, 3.0, 4.0,} * {1.0, 2.0, 3.0, 4.0} == {1.0, 4.0, 9.0, 16.0} : %s\n", result ? "yes" : "no");
}

void test_div()
{
    glm::simdVec4 subjectA(1.0f, 2.0f, 3.0f, 4.0f);
    glm::simdVec4 subjectB(1.0f, 2.0f, 3.0f, 4.0f);
    glm::simdVec4 answer = subjectA / subjectB;

    bool result =
        answer[0] == 1.0f &&
        answer[1] == 1.0f &&
        answer[2] == 1.0f &&
        answer[3] == 1.0f;

    printf("{1.0, 2.0, 3.0, 4.0,} / {1.0, 2.0, 3.0, 4.0} == {1.0, 1.0, 1.0, 1.0} : %s\n", result ? "yes" : "no");
}




void do_correctness_checks()
{
    printf("--- Basic Tests ---\n");
    test_sizeof();
    test_accessors();

#ifndef GLM_SIMD_NO_TYPE_UNION
    test_data_equals_xyzw();
#endif
    
    printf("\n");

    printf("--- Simple Arithmetic Tests ---\n");
    test_add();
    test_sub();
    test_mul();
    test_div();

    printf("\n");
}

void do_consistency_checks()
{
    glm::vec4     pure(1.0f, 2.0f, 3.0f, 4.0f);
    glm::simdVec4 simd(1.0f, 2.0f, 3.0f, 4.0f);

    printf("--- Consistency Checks ---\n");


    printf("    dot : %s\n",
    (
        glm::dot(simd, simd) == glm::dot(pure, pure)

    ) ? "yes" : "no");

    printf("\n");
}

void do_timing_checks()
{
}

void do_all_tests()
{
    do_correctness_checks();
    do_consistency_checks();
    do_timing_checks();
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


    do_all_tests();


	return 0;
}

#else

int main()
{
	int Error = 0;

	return Error;
}

#endif//(GLM_ARCH != GLM_ARCH_PURE)
