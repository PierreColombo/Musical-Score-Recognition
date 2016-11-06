!!ARBfp1.0
OPTION NV_fragment_program2;
# cgc version 1.5.0014, build date Sep 18 2006 20:41:01
# command line args: -q -profile fp40 -entry Correlation ARB_draw_buffers NumTemps=32 NumInstructionSlots=4096 MaxLocalParams=512
# source file: g:\projects\tests\GPUTest\scripts\correlation.cg
#vendor NVIDIA Corporation
#version 1.5.0.14
#profile fp40
#program Correlation
#semantic Correlation.fnorm
#semantic Correlation.tnorm
#semantic Correlation.Snorm2
#semantic Correlation.Tnorm2
#var float2 C : $vin.TEXCOORD0 : TEX0 : 0 : 1
#var samplerRECT fnorm :  : texunit 2 : 1 : 1
#var samplerRECT tnorm :  : texunit 3 : 2 : 1
#var samplerRECT Snorm2 :  : texunit 0 : 3 : 1
#var samplerRECT Tnorm2 :  : texunit 1 : 4 : 1
#var float4 Correlation : $vout.COLOR : COL : -1 : 1
#const c[0] = 0 1 255
#const c[1] = 77 0
PARAM c[2] = { { 0, 1, 255 },
		{ 77, 0 } };
TEMP R0;
TEMP R1;
TEMP R2;
TEMP R3;
TEMP R4;
TEMP RC;
TEMP HC;
OUTPUT oCol = result.color;
TEX   R1, c[0].x, texture[1], RECT;
TEX   R0, fragment.texcoord[0], texture[0], RECT;
MULR  R0, R0, R1;
RSQR  R0.x, R0.x;
RSQR  R0.y, R0.y;
RCPR  R3.x, R0.x;
RCPR  R3.y, R0.y;
RSQR  R0.x, R0.z;
RSQR  R0.y, R0.w;
RCPR  R3.z, R0.x;
RCPR  R3.w, R0.y;
MOVR  R2, c[0].x;
MOVR  R4.x, c[0];
LOOP c[1];
MOVR  R4.y, c[0].x;
LOOP c[1];
MOVR  R0.x, R4.y;
MOVR  R0.y, R4.x;
TEX   R1, R0, texture[3], RECT;
ADDR  R0.x, fragment.texcoord[0], R4.y;
ADDR  R0.y, fragment.texcoord[0], R4.x;
TEX   R0, R0, texture[2], RECT;
MADR  R2, R0, R1, R2;
ADDR  R4.y, R4, c[0];
ENDLOOP;
ADDR  R4.x, R4, c[0].y;
ENDLOOP;
RCPR  R0.x, R3.x;
RCPR  R0.y, R3.y;
RCPR  R0.w, R3.w;
RCPR  R0.z, R3.z;
MULR  R0, R2, R0;
MULR  oCol, |R0|, c[0].z;
END
# 33 instructions, 5 R-regs, 0 H-regs
