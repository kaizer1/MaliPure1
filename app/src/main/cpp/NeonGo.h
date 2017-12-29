//
// Created by Сергей Лоскутников on 18/12/2017.
//


#ifndef MALIPURE_NEONGO_H
#define MALIPURE_NEONGO_H


#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef __attribute__((neon_vector_type(2))) int32_t losVectorInt2;

typedef struct losLL
{
    losVectorInt2 mitu[2];
}losStruct;



//__restrict  arm_float_t * dst
//extern int ne10_addc_float_neon (float * dst, float * src, const float cst, uint32_t count) asm ("ne10_addc_float_neon");
extern float ne10_mulcmatvec_cm2x2f_v2f_neon (float* losFloat, const float er[16], const float sef[16]) asm ("ne10_mulcmatvec_cm2x2f_v2f_neon");

#ifdef __cplusplus
}
#endif



#endif //MALIPURE_NEONGO_H
