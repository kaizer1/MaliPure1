//
// Created by Сергей Лоскутников on 30/10/2017.
//

#include "LosArmSimd.h"


simdLos createVector2Los(float r, float ghh)
{
    const float32_t fe[2] = {r, ghh};
    simdLos fea = vld1_f32(fe);
  return fea;
}

simdLos simd_los_2mul(simdLos lhs, simdLos rhs)
{
    simdLos  ret = vmul_f32(lhs, rhs);
    return ret;
}


float simdGetValueX( simdLos sinmL, const int number)
{
    float32_t a = vget_lane_f32(sinmL, 0);
    // vgetq_lane_f32  == 32x4
   return a;
}


float simdGetValueY(simdLos simd)
{
    float32_t a = vget_lane_f32(simd, 1);
    return a;
}

simdL4f createVector4Los(float x, float y, float z, float w)
{
    const float32_t losd[4] = {x, y, z, w};
    simdL4f retSimd = vld1q_f32(losd);
    return retSimd;
}

simdL4f simdMax4f(simdL4f a, simdL4f b)
{
    return vmaxq_f32(a, b);
}

simdL4f simdMin4f(simdL4f a, simdL4f b)
{
    return vminq_f32(a, b);
}
// vec4f * vec4f
simdL4f multiple4f(simdL4f a, simdL4f b)
{
    simdL4f newL = vmulq_f32(a, b);
    return newL;
}
      //

simdL4f createVector4Los(const simdL4f& sim)
{
     //simdL4f dupl = vdup_
    //return
}

float simdGetValueXvec4(simdL4f simd)
{
    float32_t a = vgetq_lane_f32(simd, 0);
    return a;
}

float simdGetValueYvec4(simdL4f simd)
{
    float32_t a = vgetq_lane_f32(simd, 1);
    return a;
}


float simdGetValueZvec4(simdL4f simd)
{
    float32_t a = vgetq_lane_f32(simd, 2);
    return a;
}


float simdGetValueWvec4(simdL4f simd)
{
    float32_t a = vgetq_lane_f32(simd, 3);
    return a;
}