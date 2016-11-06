!!ARBfp1.0
OPTION NV_fragment_program2;
# cgc version 1.5.0014, build date Sep 18 2006 20:41:01
# command line args: -q -profile fp40 -entry Sum2 ARB_draw_buffers NumTemps=32 NumInstructionSlots=4096 MaxLocalParams=512
# source file: g:\projects\tests\GPUTest\scripts\opticalflow.cg
#vendor NVIDIA Corporation
#version 1.5.0.14
#profile fp40
#program Sum2
#semantic Sum2.I
#var float2 C : $vin.TEXCOORD0 : TEX0 : 0 : 1
#var samplerRECT I :  : texunit 0 : 1 : 1
#var float4 Sum2 : $vout.COLOR : COL : -1 : 1
#const c[0] = 255 0 -2 2
#const c[1] = -1 1
PARAM c[2] = { { 255, 0, -2, 2 },
		{ -1, 1 } };
TEMP R0;
TEMP R1;
TEMP R2;
TEMP RC;
TEMP HC;
OUTPUT oCol = result.color;
MOVR  R1, c[0].y;
MOVR  R2.z, c[0];
LOOP c[0];
SLERC HC.x, R2.z, c[0].w;
BRK   (EQ.x);
MOVR  R0.y, R2.z;
MOVR  R0.x, c[0].z;
ADDR  R0.xy, fragment.texcoord[0], R0;
TEX   R0, R0, texture[0], RECT;
MADR  R0, R0, R0, R1;
MOVR  R2.y, R2.z;
MOVR  R2.x, c[1];
ADDR  R2.xy, fragment.texcoord[0], R2;
TEX   R1, R2, texture[0], RECT;
MOVR  R2.y, R2.z;
MOVR  R2.x, c[0].y;
ADDR  R2.xy, fragment.texcoord[0], R2;
MADR  R0, R1, R1, R0;
TEX   R1, R2, texture[0], RECT;
MOVR  R2.y, R2.z;
MOVR  R2.x, c[1].y;
ADDR  R2.xy, fragment.texcoord[0], R2;
MADR  R0, R1, R1, R0;
TEX   R1, R2, texture[0], RECT;
MOVR  R2.y, R2.z;
MOVR  R2.x, c[0].w;
MADR  R0, R1, R1, R0;
ADDR  R2.xy, fragment.texcoord[0], R2;
TEX   R1, R2, texture[0], RECT;
MADR  R1, R1, R1, R0;
ADDR  R2.z, R2, c[1].y;
ENDLOOP;
MOVR  oCol, R1;
END
# 33 instructions, 3 R-regs, 0 H-regs
