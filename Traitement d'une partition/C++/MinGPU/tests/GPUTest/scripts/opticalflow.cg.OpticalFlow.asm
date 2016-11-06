!!ARBfp1.0
OPTION NV_fragment_program2;
# cgc version 1.5.0014, build date Sep 18 2006 20:41:01
# command line args: -q -profile fp40 -entry OpticalFlow ARB_draw_buffers NumTemps=32 NumInstructionSlots=4096 MaxLocalParams=512
# source file: g:\projects\tests\GPUTest\scripts\opticalflow.cg
#vendor NVIDIA Corporation
#version 1.5.0.14
#profile fp40
#program OpticalFlow
#semantic OpticalFlow.SIx2
#semantic OpticalFlow.SIy2
#semantic OpticalFlow.SIxIy
#semantic OpticalFlow.SIxIt
#semantic OpticalFlow.SIyIt
#var float2 C : $vin.TEXCOORD0 : TEX0 : 0 : 1
#var samplerRECT SIx2 :  : texunit 0 : 1 : 1
#var samplerRECT SIy2 :  : texunit 2 : 2 : 1
#var samplerRECT SIxIy :  : texunit 1 : 3 : 1
#var samplerRECT SIxIt :  : texunit 3 : 4 : 1
#var samplerRECT SIyIt :  : texunit 4 : 5 : 1
#var float4 OpticalFlow : $vout.COLOR : COL : -1 : 1
TEMP R0;
TEMP R1;
TEMP R2;
TEMP RC;
TEMP HC;
OUTPUT oCol = result.color;
TEX   R0.x, fragment.texcoord[0], texture[2], RECT;
MOVR  R2.y, R0.x;
TEX   R2.x, fragment.texcoord[0], texture[1], RECT;
TEX   R1.x, fragment.texcoord[0], texture[3], RECT;
TEX   R0.x, fragment.texcoord[0], texture[4], RECT;
MOVR  R0.w, -R0.x;
MOVR  R0.z, -R1.x;
MULR  R1.xy, R2, R0.zwzw;
TEX   R0.x, fragment.texcoord[0], texture[0], RECT;
MOVR  R0.y, R2.x;
MULR  R0.xy, R0.zwzw, R0;
ADDR  oCol.y, R1.x, R1;
ADDR  oCol.x, R0, R0.y;
END
# 13 instructions, 3 R-regs, 0 H-regs
