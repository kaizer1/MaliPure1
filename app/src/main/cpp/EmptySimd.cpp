//
// Created by Сергей Лоскутников on 30/10/2017.
//

#include "LosEmptySimd.h"


simdLos createVector2Los(float r, float ghh)
{
    simdLos er;
    er.x = r;
    er.y = ghh;
    return er;
}

simdLos simd_los_2mul(simdLos lhs, simdLos rhs)
{
    simdLos newLos;

    return newLos;
}

float simdGetValueX( simdLos sinmL, const int number)
{

         return sinmL.x;
}

float simdGetValueY(simdLos simd)
{
    return simd.y;
}


simdL4f createVector4Los(float x, float y, float z, float w)
{
    simdL4f  ef;
    return ef;
}

simdL4f  createVector4Los(simdL4f sam)
{

}

simdL4f simdMax4f(simdL4f a, simdL4f b)
{
    simdL4f  ret;
    return ret;
}

simdL4f simdMin4f(simdL4f a, simdL4f b)
{
    simdL4f  e;
    return e;
}


simdL4f multiple4f(simdL4f a, simdL4f b)
{
    return a;
}


float simdGetValueXvec4(simdL4f simd)
{
    float er =10;
    return er;
}

float simdGetValueYvec4(simdL4f simd)
{
    float er =10;
    return er;
}


float simdGetValueZvec4(simdL4f simd)
{
    float er =10;
    return er;
}


float simdGetValueWvec4(simdL4f simd)
{
    float er =10;
    return er;
}