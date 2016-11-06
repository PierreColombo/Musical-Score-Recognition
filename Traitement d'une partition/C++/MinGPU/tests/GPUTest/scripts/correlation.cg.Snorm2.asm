!!ARBfp1.0
OPTION NV_fragment_program2;
# cgc version 1.5.0014, build date Sep 18 2006 20:41:01
# command line args: -q -profile fp40 -entry Snorm2 ARB_draw_buffers NumTemps=32 NumInstructionSlots=4096 MaxLocalParams=512
# source file: g:\projects\tests\GPUTest\scripts\correlation.cg
#vendor NVIDIA Corporation
#version 1.5.0.14
#profile fp40
#program Snorm2
#semantic Snorm2.fnorm
#var float2 C : $vin.TEXCOORD0 : TEX0 : 0 : 1
#var samplerRECT fnorm :  : texunit 0 : 1 : 1
#var float4 Snorm2 : $vout.COLOR : COL : -1 : 1
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
ADDR  R0.x, fragment.texcoord[0], R2.y;
ADDR  R0.y, fragment.texcoord[0], R2.x;
TEX   R0, R0, texture[0], RECT;
MADR  R1, R0, R0, R1;
ADDR  R2.y, R2, c[0];
ENDLOOP;
ADDR  R2.x, R2, c[0].y;
ENDLOOP;
MOVR  oCol, R1;
END
# 14 instructions, 3 R-regs, 0 H-regs
