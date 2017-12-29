//
// Created by Сергей Лоскутников on 30/10/2017.
//

#pragma once

#include <arm_neon.h>
//#include "LosMathematica.h"

using simdLos = float32x2_t;
using simdL4f = float32x4_t;

simdLos createVector2Los(float r, float ghh);

simdLos simd_los_2mul(simdLos lhs, simdLos rhs);

float simdGetValueX( simdLos sinmL, const int number);

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

 ////: TODO END's MALIPURE_LOSARMSIMD_H
