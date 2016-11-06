!!ARBfp1.0
OPTION NV_fragment_program2;
# cgc version 1.5.0014, build date Sep 18 2006 20:41:01
# command line args: -q -profile fp40 -entry Homography ARB_draw_buffers NumTemps=32 NumInstructionSlots=4096 MaxLocalParams=512
# source file: g:\projects\tests\GPUTest\scripts\homography.cg
#vendor NVIDIA Corporation
#version 1.5.0.14
#profile fp40
#program Homography
#semantic Homography.H
#semantic Homography.ratio
#semantic Homography.x1
#semantic Homography.y1
#semantic Homography.view
#semantic Homography.result
#var float2 coords : $vin.TEXCOORD0 : TEX0 : 0 : 1
#var float3x3 H :  : c[0], 3 : 1 : 1
#var float ratio :  : c[3] : 2 : 1
#var float x1 :  : c[4] : 3 : 1
#var float y1 :  : c[5] : 4 : 1
#var samplerRECT view :  : texunit 1 : 5 : 1
#var samplerRECT result :  : texunit 0 : 6 : 1
#var float4 Homography : $vout.COLOR : COL : -1 : 1
PARAM c[6] = { program.local[0..5] };
TEMP R0;
TEMP R1;
TEMP RC;
TEMP HC;
OUTPUT oCol = result.color;
MOVR  R0.x, c[5];
MADR  R0.y, fragment.texcoord[0], c[3].x, R0.x;
MOVR  R0.x, c[4];
MADR  R0.x, fragment.texcoord[0], c[3], R0;
MULR  R0.z, R0.y, c[0].y;
MULR  R0.w, R0.y, c[2].y;
MADR  R0.z, R0.x, c[0].x, R0;
MADR  R0.w, R0.x, c[2].x, R0;
MULR  R0.y, R0, c[1];
MADR  R0.x, R0, c[1], R0.y;
ADDR  R0.y, R0.w, c[2].z;
RCPR  R0.y, R0.y;
ADDR  R0.x, R0, c[1].z;
ADDR  R0.z, R0, c[0];
MULR  R0.w, R0.y, R0.x;
MULR  R0.z, R0, R0.y;
TEX   R1, R0.zwzw, texture[1], RECT;
TEX   R0, fragment.texcoord[0], texture[0], RECT;
ADDR  oCol, R0, R1;
END
# 19 instructions, 2 R-regs, 0 H-regs
