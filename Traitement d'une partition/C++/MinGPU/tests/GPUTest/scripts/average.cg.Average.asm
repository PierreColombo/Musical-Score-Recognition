!!ARBfp1.0
OPTION NV_fragment_program2;
# cgc version 1.5.0014, build date Sep 18 2006 20:41:01
# command line args: -q -profile fp40 -entry Average ARB_draw_buffers NumTemps=32 NumInstructionSlots=4096 MaxLocalParams=512
# source file: g:\projects\tests\GPUTest\scripts\average.cg
#vendor NVIDIA Corporation
#version 1.5.0.14
#profile fp40
#program Average
#semantic Average.src
#semantic Average.dest
#var float2 C : $vin.TEXCOORD0 : TEX0 : 0 : 1
#var samplerRECT src :  : texunit 1 : 1 : 1
#var samplerRECT dest :  : texunit 0 : 2 : 1
#var float4 Average : $vout.COLOR : COL : -1 : 1
#const c[0] = 0.5
PARAM c[1] = { { 0.5 } };
TEMP R0;
TEMP R1;
TEMP RC;
TEMP HC;
OUTPUT oCol = result.color;
TEX   R1, fragment.texcoord[0], texture[1], RECT;
TEX   R0, fragment.texcoord[0], texture[0], RECT;
ADDR  R0, R0, R1;
MULR  oCol, R0, c[0].x;
END
# 4 instructions, 2 R-regs, 0 H-regs
