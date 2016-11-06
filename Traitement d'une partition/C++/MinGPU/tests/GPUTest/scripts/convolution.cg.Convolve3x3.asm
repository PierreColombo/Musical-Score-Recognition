!!ARBfp1.0
OPTION NV_fragment_program2;
# cgc version 1.5.0014, build date Sep 18 2006 20:41:01
# command line args: -q -profile fp40 -entry Convolve3x3 ARB_draw_buffers NumTemps=32 NumInstructionSlots=4096 MaxLocalParams=512
# source file: g:\projects\tests\GPUTest\scripts\convolution.cg
#vendor NVIDIA Corporation
#version 1.5.0.14
#profile fp40
#program Convolve3x3
#semantic Convolve3x3.T
#semantic Convolve3x3.K
#var float2 C : $vin.TEXCOORD0 : TEX0 : 0 : 1
#var samplerRECT T :  : texunit 0 : 1 : 1
#var float K[0][0] :  : c[0] : 2 : 1
#var float K[0][1] :  : c[1] : 2 : 1
#var float K[0][2] :  : c[2] : 2 : 1
#var float K[1][0] :  : c[3] : 2 : 1
#var float K[1][1] :  : c[4] : 2 : 1
#var float K[1][2] :  : c[5] : 2 : 1
#var float K[2][0] :  : c[6] : 2 : 1
#var float K[2][1] :  : c[7] : 2 : 1
#var float K[2][2] :  : c[8] : 2 : 1
#var float4 Convolve3x3 : $vout.COLOR : COL : -1 : 1
#const c[9] = -1 0 1
PARAM c[10] = { program.local[0..8],
		{ -1, 0, 1 } };
TEMP R0;
TEMP R1;
TEMP R2;
TEMP RC;
TEMP HC;
OUTPUT oCol = result.color;
ADDR  R0, fragment.texcoord[0].xyxx, c[9].xxyz;
TEX   R1, R0.zyzw, texture[0], RECT;
MULR  R2, R1, c[1].x;
TEX   R1, R0, texture[0], RECT;
MADR  R2, R1, c[0].x, R2;
TEX   R0, R0.wyzw, texture[0], RECT;
ADDR  R1, fragment.texcoord[0].xyxy, c[9].xyzz;
MADR  R2, R0, c[2].x, R2;
TEX   R0, R1, texture[0], RECT;
MADR  R2, R0, c[3].x, R2;
TEX   R0, fragment.texcoord[0], texture[0], RECT;
MADR  R0, R0, c[4].x, R2;
TEX   R2, R1.zyzw, texture[0], RECT;
MADR  R0, R2, c[5].x, R0;
TEX   R1, R1.xwzw, texture[0], RECT;
MADR  R1, R1, c[6].x, R0;
ADDR  R2.xyz, fragment.texcoord[0].xyxw, c[9].yzzw;
TEX   R0, R2, texture[0], RECT;
MADR  R0, R0, c[7].x, R1;
TEX   R1, R2.zyzw, texture[0], RECT;
MADR  oCol, R1, c[8].x, R0;
END
# 21 instructions, 3 R-regs, 0 H-regs
