!!ARBfp1.0
OPTION NV_fragment_program2;
# cgc version 1.5.0014, build date Sep 18 2006 20:41:01
# command line args: -q -profile fp40 -entry SumXY ARB_draw_buffers NumTemps=32 NumInstructionSlots=4096 MaxLocalParams=512
# source file: g:\projects\tests\GPUTest\scripts\opticalflow.cg
#vendor NVIDIA Corporation
#version 1.5.0.14
#profile fp40
#program SumXY
#semantic SumXY.X
#semantic SumXY.Y
#var float2 C : $vin.TEXCOORD0 : TEX0 : 0 : 1
#var samplerRECT X :  : texunit 0 : 1 : 1
#var samplerRECT Y :  : texunit 1 : 2 : 1
#var float4 SumXY : $vout.COLOR : COL : -1 : 1
#const c[0] = 255 0 -2 2
#const c[1] = -1 1
PARAM c[2] = { { 255, 0, -2, 2 },
		{ -1, 1 } };
TEMP R0;
TEMP R1;
TEMP R2;
TEMP R3;
TEMP RC;
TEMP HC;
OUTPUT oCol = result.color;
MOVR  R2, c[0].y;
MOVR  R3.z, c[0];
LOOP c[0];
SLERC HC.x, R3.z, c[0].w;
BRK   (EQ.x);
MOVR  R0.y, R3.z;
MOVR  R0.x, c[0].z;
ADDR  R1.xy, fragment.texcoord[0], R0;
TEX   R0, R1, texture[0], RECT;
TEX   R1, R1, texture[1], RECT;
MADR  R1, R0, R1, R2;
MOVR  R3.y, R3.z;
MOVR  R3.x, c[1];
ADDR  R3.xy, fragment.texcoord[0], R3;
TEX   R0, R3, texture[0], RECT;
TEX   R2, R3, texture[1], RECT;
MADR  R1, R0, R2, R1;
MOVR  R3.y, R3.z;
MOVR  R3.x, c[0].y;
ADDR  R3.xy, fragment.texcoord[0], R3;
TEX   R0, R3, texture[0], RECT;
TEX   R2, R3, texture[1], RECT;
MADR  R1, R0, R2, R1;
MOVR  R3.y, R3.z;
MOVR  R3.x, c[1].y;
ADDR  R3.xy, fragment.texcoord[0], R3;
TEX   R0, R3, texture[0], RECT;
TEX   R2, R3, texture[1], RECT;
MOVR  R3.y, R3.z;
MOVR  R3.x, c[0].w;
MADR  R1, R0, R2, R1;
ADDR  R3.xy, fragment.texcoord[0], R3;
TEX   R0, R3, texture[0], RECT;
TEX   R2, R3, texture[1], RECT;
MADR  R2, R0, R2, R1;
ADDR  R3.z, R3, c[1].y;
ENDLOOP;
MOVR  oCol, R2;
END
# 38 instructions, 4 R-regs, 0 H-regs
