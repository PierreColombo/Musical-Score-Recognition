!!ARBfp1.0
OPTION NV_fragment_program2;
# cgc version 1.5.0014, build date Sep 18 2006 20:41:01
# command line args: -q -profile fp40 -entry Tnorm2 ARB_draw_buffers NumTemps=32 NumInstructionSlots=4096 MaxLocalParams=512
# source file: g:\projects\tests\GPUTest\scripts\correlation.cg
#vendor NVIDIA Corporation
#version 1.5.0.14
#profile fp40
#program Tnorm2
#semantic Tnorm2.tnorm
#var float2 C : $vin.TEXCOORD0 :  : 0 : 0
#var samplerRECT tnorm :  : texunit 0 : 1 : 1
#var float4 Tnorm2 : $vout.COLOR : COL : -1 : 1
#const c[0] = 0 1
#const c[1] = 77 0
PARAM c[2] = { { 0, 1 },
		{ 77, 0 } };
TEMP R0;
TEMP R1;
TEMP R2;
TEMP RC;
TEMP HC;
OUTPUT oCol = result.color;
MOVR  R1, c[0].x;
MOVR  R2.x, c[0];
LOOP c[1];
MOVR  R2.y, c[0].x;
LOOP c[1];
MOVR  R0.x, R2.y;
MOVR  R0.y, R2.x;
TEX   R0, R0, texture[0], RECT;
MADR  R1, R0, R0, R1;
ADDR  R2.y, R2, c[0];
ENDLOOP;
ADDR  R2.x, R2, c[0].y;
ENDLOOP;
MOVR  oCol, R1;
END
# 14 instructions, 3 R-regs, 0 H-regs
