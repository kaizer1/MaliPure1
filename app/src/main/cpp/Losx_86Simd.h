//
// Created by Сергей Лоскутников on 30/10/2017.
//

#pragma once

#include <xmmintrin.h>
#if defined(VECTORIAL_USE_SSE4_1)
#include <smmintrin.h>
#endif
#include <string.h>


using simdLos = __m64;
using simdL4f = __m128

simdLos createVector2Los(float r, float ghh);

simdLos simd_los_2mul(simdLos lhs, simdLos rhs);

float simdGetValue( simdLos sinmL, const int number);

float simdGetValueY( simdLos simd);

simdL4f createVector4Los(float x, float y, float z, float w);

simdL4f createVector4Los(const simdL4f& sim);

simdL4f simdMin4f(simdL4f a, simdL4f b);

simdL4f simdMax4f(simdL4f a, simdL4f b);

simdL4f multiple4f(simdL4f a, simdL4f b);

float simdGetValueXvec4(simdL4f simd);
float simdGetValueYvec4(simdL4f simd);
float simdGetValueZvec4(simdL4f simd);
float simdGetValueWvec4(simdL4f simd);

////: TODO MALIPURE_LOSX_86SIMD_H
