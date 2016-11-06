!!ARBfp1.0
OPTION NV_fragment_program2;
# cgc version 1.5.0014, build date Sep 18 2006 20:41:01
# command line args: -q -profile fp40 -entry tnorm ARB_draw_buffers NumTemps=32 NumInstructionSlots=4096 MaxLocalParams=512
# source file: g:\projects\tests\GPUTest\scripts\correlation.cg
#vendor NVIDIA Corporation
#version 1.5.0.14
#profile fp40
#program tnorm
#semantic tnorm.op1
#semantic tnorm.op2
#var float2 C : $vin.TEXCOORD0 : TEX0 : 0 : 1
#var samplerRECT op1 :  : texunit 0 : 1 : 1
#var samplerRECT op2 :  : texunit 1 : 2 : 1
#var float4 tnorm : $vout.COLOR : COL : -1 : 1
#const c[0] = 0
PARAM c[1] = { { 0 } };
TEMP R0;
TEMP R1;
TEMP RC;
TEMP HC;
OUTPUT oCol = result.color;
TEX   R1, c[0].x, texture[1], RECT;
TEX   R0, fragment.texcoord[0], texture[0], RECT;
ADDR  oCol, R0, -R1;
END
# 3 instructions, 2 R-regs, 0 H-regs
