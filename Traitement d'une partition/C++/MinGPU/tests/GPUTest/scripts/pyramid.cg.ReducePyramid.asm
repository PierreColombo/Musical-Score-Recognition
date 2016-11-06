!!ARBfp1.0
OPTION NV_fragment_program2;
# cgc version 1.5.0014, build date Sep 18 2006 20:41:01
# command line args: -q -profile fp40 -entry ReducePyramid ARB_draw_buffers NumTemps=32 NumInstructionSlots=4096 MaxLocalParams=512
# source file: g:\projects\tests\GPUTest\scripts\pyramid.cg
#vendor NVIDIA Corporation
#version 1.5.0.14
#profile fp40
#program ReducePyramid
#semantic ReducePyramid.T
#semantic ReducePyramid.Mask
#var float2 C : $vin.TEXCOORD0 : TEX0 : 0 : 1
#var samplerRECT T :  : texunit 0 : 1 : 1
#var float Mask[0][0] :  : c[0] : 2 : 1
#var float Mask[0][1] :  : c[1] : 2 : 1
#var float Mask[0][2] :  : c[2] : 2 : 1
#var float Mask[0][3] :  : c[3] : 2 : 1
#var float Mask[0][4] :  : c[4] : 2 : 1
#var float Mask[1][0] :  : c[5] : 2 : 1
#var float Mask[1][1] :  : c[6] : 2 : 1
#var float Mask[1][2] :  : c[7] : 2 : 1
#var float Mask[1][3] :  : c[8] : 2 : 1
#var float Mask[1][4] :  : c[9] : 2 : 1
#var float Mask[2][0] :  : c[10] : 2 : 1
#var float Mask[2][1] :  : c[11] : 2 : 1
#var float Mask[2][2] :  : c[12] : 2 : 1
#var float Mask[2][3] :  : c[13] : 2 : 1
#var float Mask[2][4] :  : c[14] : 2 : 1
#var float Mask[3][0] :  : c[15] : 2 : 1
#var float Mask[3][1] :  : c[16] : 2 : 1
#var float Mask[3][2] :  : c[17] : 2 : 1
#var float Mask[3][3] :  : c[18] : 2 : 1
#var float Mask[3][4] :  : c[19] : 2 : 1
#var float Mask[4][0] :  : c[20] : 2 : 1
#var float Mask[4][1] :  : c[21] : 2 : 1
#var float Mask[4][2] :  : c[22] : 2 : 1
#var float Mask[4][3] :  : c[23] : 2 : 1
#var float Mask[4][4] :  : c[24] : 2 : 1
#var float4 ReducePyramid : $vout.COLOR : COL : -1 : 1
#const c[25] = -1 0 1 2
PARAM c[26] = { program.local[0..24],
		{ -1, 0, 1, 2 } };
TEMP R0;
TEMP R1;
TEMP R2;
TEMP R3;
TEMP R4;
TEMP RC;
TEMP HC;
OUTPUT oCol = result.color;
MADR  R3.xy, fragment.texcoord[0], c[25].w, -c[25].w;
MADR  R4, fragment.texcoord[0].x, c[25].w, c[25];
MOVR  R0.y, R3;
MOVR  R0.x, R4;
TEX   R0, R0, texture[0], RECT;
MULR  R1, R0, c[1].x;
TEX   R0, R3, texture[0], RECT;
MADR  R1, R0, c[0].x, R1;
MOVR  R0.y, R3;
MOVR  R0.x, R4.y;
TEX   R0, R0, texture[0], RECT;
MADR  R1, R0, c[2].x, R1;
MOVR  R0.y, R3;
MOVR  R0.x, R4.z;
TEX   R0, R0, texture[0], RECT;
MADR  R2, R0, c[3].x, R1;
MADR  R1, fragment.texcoord[0].xyxx, c[25].w, c[25].xxyz;
MOVR  R0.y, R3;
MOVR  R0.x, R4.w;
TEX   R0, R0, texture[0], RECT;
MADR  R2, R0, c[4].x, R2;
MOVR  R0.y, R1;
MOVR  R0.x, R3;
TEX   R0, R0, texture[0], RECT;
MADR  R2, R0, c[5].x, R2;
TEX   R0, R1, texture[0], RECT;
MADR  R2, R0, c[6].x, R2;
TEX   R0, R1.zyzw, texture[0], RECT;
MADR  R2, R0, c[7].x, R2;
TEX   R0, R1.wyzw, texture[0], RECT;
MADR  R2, R0, c[8].x, R2;
MOVR  R0.y, R1;
MOVR  R0.x, R4.w;
TEX   R0, R0, texture[0], RECT;
MADR  R2, R0, c[9].x, R2;
MADR  R1, fragment.texcoord[0].xyxx, c[25].w, c[25].xyyz;
MOVR  R0.y, R1;
MOVR  R0.x, R3;
TEX   R0, R0, texture[0], RECT;
MADR  R2, R0, c[10].x, R2;
TEX   R0, R1, texture[0], RECT;
MADR  R2, R0, c[11].x, R2;
TEX   R0, R1.zyzw, texture[0], RECT;
MADR  R2, R0, c[12].x, R2;
TEX   R0, R1.wyzw, texture[0], RECT;
MADR  R2, R0, c[13].x, R2;
MOVR  R0.y, R1;
MOVR  R0.x, R4.w;
TEX   R0, R0, texture[0], RECT;
MADR  R2, R0, c[14].x, R2;
MADR  R1, fragment.texcoord[0].xyxx, c[25].w, c[25].xzyz;
MOVR  R0.y, R1;
MOVR  R0.x, R3;
TEX   R0, R0, texture[0], RECT;
MADR  R2, R0, c[15].x, R2;
TEX   R0, R1, texture[0], RECT;
MADR  R2, R0, c[16].x, R2;
TEX   R0, R1.zyzw, texture[0], RECT;
MADR  R2, R0, c[17].x, R2;
TEX   R0, R1.wyzw, texture[0], RECT;
MADR  R2, R0, c[18].x, R2;
MOVR  R0.y, R1;
MOVR  R0.x, R4.w;
TEX   R0, R0, texture[0], RECT;
MADR  R2, R0, c[19].x, R2;
MADR  R1, fragment.texcoord[0].xyxx, c[25].w, c[25].xwyz;
MOVR  R0.y, R1;
MOVR  R0.x, R3;
TEX   R0, R0, texture[0], RECT;
MADR  R2, R0, c[20].x, R2;
TEX   R0, R1, texture[0], RECT;
MADR  R2, R0, c[21].x, R2;
TEX   R0, R1.zyzw, texture[0], RECT;
MADR  R2, R0, c[22].x, R2;
TEX   R0, R1.wyzw, texture[0], RECT;
MOVR  R1.x, R4.w;
MADR  R0, R0, c[23].x, R2;
TEX   R1, R1, texture[0], RECT;
MADR  oCol, R1, c[24].x, R0;
END
# 79 instructions, 5 R-regs, 0 H-regs
