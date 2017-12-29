//
// Created by Сергей Лоскутников on 30/10/2017.
//

#pragma once

struct newUni{
    float x;
    float y;
    newUni(){ x = 0; y = 0; }
};

struct newFloatU {
    float x;
    float y;
    float z;
    float w;
};

using simdLos  = newUni;
using simdL4f = newFloatU;
//using simdLos = float[2];

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

 ////: TODO MALIPURE_LOSEMPTYSIMD_H
