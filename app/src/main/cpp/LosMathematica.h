//
// Created by Сергей Лоскутников on 30/10/2017.
//

#pragma once

#if defined(HAVE_NEON) && defined(HAVE_NEON_X86)
/*
  * The latest version and instruction for NEON_2_SSE.h is at:
  *    https://github.com/intel/ARM_NEON_2_x86_SSE
  */
  #include "NEON_2_SSE.h"
#include "Losx_86Simd.h"
#elif defined(HAVE_NEON)
//#include <arm_neon.h>
#include "LosArmSimd.h"
#else
#include "LosEmptySimd.h"
#endif

#define los_inline static inline
los_inline const float absZero = 1.0f;

 class LosVector2
 {
     public:

     simdLos simdL1;

     LosVector2() { };
     LosVector2(float x, float y) { simdL1  = createVector2Los(x, y); }
     ~LosVector2(){}


//      float get_ValueX(){
//         vgetq_lane_f32(simdL1, 0);
//     }
 };


los_inline LosVector2 operator*(const LosVector2& lhs, const LosVector2& rhs)
{
      LosVector2 newLos;
    newLos.simdL1 = simd_los_2mul(lhs.simdL1, rhs.simdL1);

    return newLos;
}


los_inline float getValueSimdVecX(const LosVector2& myVec, const int num)
{
    float retV = simdGetValueX(myVec.simdL1, num);
    return retV;
}

los_inline float getValueSimdVecY(const LosVector2& meVec)
{
    float er = simdGetValueY(meVec.simdL1);
    return er;
}



class lvec4f
{
public:

    simdL4f simple4f;

    lvec4f() { };
  explicit inline lvec4f(float x, float y, float z, float w)
 : simple4f (createVector4Los(x, y, z, w)) {};

   inline lvec4f(const simdL4f& simdf4) : simple4f (createVector4Los(simdf4)) {}

    ~lvec4f(){}
};


los_inline lvec4f operator*(const lvec4f& lhs, const lvec4f& rhs)
{

    simdL4f newLos  = multiple4f(lhs.simple4f, rhs.simple4f);
    lvec4f neL;
    neL.simple4f = newLos;
    return neL;
}


los_inline simdL4f GetsimdMin4f(simdL4f a, simdL4f b)
{
    return simdMin4f(a, b);
}

 los_inline simdL4f GetsimdMax4f(simdL4f a, simdL4f b)
 {
     return simdMax4f(a, b);
 }

los_inline float getXvectro4(simdL4f a)
{
    return simdGetValueXvec4(a);
}

los_inline float getYvectro4(simdL4f a)
{
    return simdGetValueYvec4(a);
}

los_inline float getZvectro4(simdL4f a)
{
    return simdGetValueZvec4(a);
}

los_inline float getWvectro4(simdL4f a)
{
    return simdGetValueWvec4(a);
}

/*
   row 0 = [0][0]  [1][0]  [2][0]  [3][0]
   row 1 = [0][1]  [1][1]  [2][1]  [3][1]
   row 2 = [0][2]  [1][2]  [2][2]  [3][2]
   row 3 = [0][3]  [1][3]  [2][3]  [3][3]

 */

struct losMat
{
    simdL4f row0;
    simdL4f row1;
    simdL4f row2;
    simdL4f row3;
};

/*
    [0][0]  [1][0]  [2][0]  [3][0]
    [0][1]  [1][1]  [2][1]  [3][1]
    [0][2]  [1][2]  [2][2]  [3][2]
    [0][3]  [1][3]  [2][3]  [3][3]

 */

 using lmatelff = losMat;


class lmatff
{
    // two component s - second
    // three component t - third
    // four component f - fouths
public:

    lmatelff losEM;

    lmatff() {};
    lmatff (lvec4f a, lvec4f b, lvec4f c, lvec4f d)
    :lmatff(a.simple4f, b.simple4f, c.simple4f, d.simple4f)
    {

    }

    lmatff (simdL4f a, simdL4f b, simdL4f c, simdL4f d)
    {
       losEM.row0 = a;
       losEM.row1 = b;
       losEM.row2 = c;
       losEM.row3 = d;
    }


    float seeElementder(simdL4f currebt, int ele)
    {
        switch(ele)
        {
            case 0:
              return  getXvectro4(currebt);


            case 1:
                return   getYvectro4(currebt);



            case 2:
                return  getZvectro4(currebt);


            case 3:
                return  getWvectro4(currebt);


            default:
                return 0.0f;
        }
    }

   float backElememtMatrix(int row, int element)
   {
       switch (row)
       {
           case 0:
             return seeElementder(losEM.row0, element);



           case 1:
             return seeElementder(losEM.row1, element);


           case 2:
              return  seeElementder(losEM.row2, element);


           case 3:
               return seeElementder(losEM.row3, element);


           default:

               return 0.0f;

       }
   }



     void scalarScale(float scaleX, float scaleY, float scaleZ)
     {
         lvec4f err(scaleX, absZero, absZero, absZero);
         lvec4f er1(absZero, scaleY, absZero, absZero);
         lvec4f er2(absZero, absZero, scaleZ, absZero);
         losEM.row0 = losEM.row0 * err.simple4f;
         losEM.row1 = losEM.row1 * er1.simple4f;
         losEM.row2 = losEM.row2 * er2.simple4f;

     }



    ~lmatff() {}

};



los_inline lmatff operator*(const lmatff lhs, const lmatff rhs)
{
      lmatff backMat;

 return backMat;
}


















////: TODO END'S MALIPURE_LOSMATHEMATICA_H
