
     .text
     .syntax unified

     .balign 4
     .global ne10_mulcmatvec_cm2x2f_v2f_neon
     .thumb
     .thumb_func

ne10_mulcmatvec_cm2x2f_v2f_neon:
      //push   {r1}
     // PUSH    {r0,r1}
    //  and  r4, r3
    //  sub  r3, r3, r4


   //  ldm r1, {r0} -- work fine   r0 == const float er[4]
   //  ldr r3, [r0] -- work ok     r0 == const float er[4]
   //  ldr r4, [r0] -- work ok     r0 == const float er[4]
   //  ldr r4, [r1] -- work ok     r0 == const float er[4]  r1 - unkwown

  //     ldr r4, [r2] //-- NOT WORK    r0 == const float er[4]  r1 - unkwown
    // ldr r2, [r1]!         //all ok
     //   vld1.32  {q0}, [r1]!  }    if(r1 remove and add r0 - work is fine too)
    //    vld1.32  {q1}, [r1]!  }  all work fine (two parameter)

     //    .32  was
       vld1.16  {q0}, [r1]!
       vld1.16  {q1}, [r2]!

       subs   r3, r3, #4

      // vsub.f32 q3, q0, q1        @ q3 = q0 - q1  -ok working !!!
      // vmul.f32 q3, q0, q1        @ q3 = q0 * q1  -ok working
      // vdiv.f32 d7, d0, d2        @ q3 = q0 / q1  -not working !
      // vadd.f32 q3, q0, q1        @ q3 = q0 + q1  -ok working

     //vmull.s16
       vmull.s16 q3, d1, d2[0]
    // vmul.f32 q3, q0, d2[0]     @ scalar d2[0] * vec (q0) = vec (q3) -ok working
       vst1.16 {d7[0]}, [r0]!
       mov     r0, #0

         // {d0[0]}, [r0]!      {d6,d7}, [r0]!
        //vadd.f32 d0,d0,d0
      //vsub.16  d3, d4, d5  -- not working
       // vld1.32         {q1}, [r2]!

    // vld2.32  Rd, Rm, Rs
   //LDRH R1, [R0];
    //VMOV.16 D1[0], R1
 // "vld1.8     {d0}, [%0]!
    //ldr r1, [r1]   ; work fine  vld1.16
        //    {d0-d1} - ok too
     // vld2.f32 {q0-q1}, [r1]!

      //vadd.f32 {q0}, [q1-q2]
    //  vaddl.f32 d3, d0, d1
     //ldr r2, [r1]   ok work
     // mov r2, {d0}

   //  add r0, r1, r2
   //  mov r0, #2
     b end
 // VADDL
    // vmul.F32 {r3,} r1, r2  -not working
    // vld1.32 d0[1], [r1]!
   // vst return numbers
     //vadd

     //vst1.16 r1, d1[0]

   // VLD1.8 {d0}, [r0]
  // mov1.32	d1, d0
  // mov d1, r0

//VLD1.32 {d0,d1}, [r1]!
//VADD.I32 q0, q0, q1
//SUBS r2, r2, #1
//VST1.32 {d0,d1}, [r0]!
//BNE |L1.20|
   // bx lr

    // vld1.8 {d0}, [r0]!

//  vst1.16   {d2}, [pDst]!
   // vst1.32 {d0[0]}, [r1]!


end:
     bx lr
     // blx r1
      // lr
   // VSVC 0

.end

      //ble .L_mainloopend_mat2x2

//@.L_mainloopend_mat2x2:

 //@     vst.32 {d24, d25, d26, d27 }. [r0]!

 // work is fine !!
 //  in float xx      ldr r0, [r1]
      //               bx lr     -- back float
      // it's this ok too:    ldr r1, [r1]    -return correct variable
      // o'kay work      :     vld1.32 d0, [r1] - return correct result
      //                        vld1.32 d0[0], [r1] - return correct result
      // o'kay                 vld2.16 {d0-d1}, [r1]