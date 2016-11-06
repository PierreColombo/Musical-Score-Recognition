#include "stdafx.h"
#include "../../MinGPU/gpu.h"
#include "common.h"

// This file contains primitive functions which execute directly in GPU without GPU-to-CPU and back data movement

bool _convolve(Array& in, Array& out, float *pfpKernel, BYTE bKernelSide)
{
  bool fRet = true;
  char szArrayName[5];

  Program Program;
  switch (bKernelSide)
  {
  case 3:
    fRet &= Program.Create("convolution.cg", "Convolve3x3");
    break;
  case 5:
    fRet &= Program.Create("convolution.cg", "Convolve5x5");
    break;
  case 7:
    fRet &= Program.Create("convolution.cg", "Convolve7x7");
    break;
  default:
    // verify if bKernelSide is in valid range. 3, 5, 7 are currently supported
    return false;
  }
	
  fRet &= Program.SetParameter(Program::enTexture, "T", (void *) in.Id());

  for (int i = 0; i < bKernelSide; i++)
  {
    sprintf(szArrayName, "K[%d]", i);
    fRet &= Program.SetParameter(Program::enArrayf, szArrayName, (void *) &pfpKernel[i * bKernelSide]); 
  }

  fRet &= Program.Run(&out);

  return fRet;
}

bool _reducepyramid(Array& in, Array& out, float *pfpMask)
{
  bool fRet = true;
  char szArrayName[10];

  Program Program;
  fRet &= Program.Create("pyramid.cg", "ReducePyramid");
  fRet &= Program.SetParameter(Program::enTexture, "T", (void *) in.Id());

  const BYTE bKernelSide = 5;
  for (int i = 0; i < bKernelSide; i++)
  {
    sprintf(szArrayName, "Mask[%d]", i);
    fRet &= Program.SetParameter(Program::enArrayf, szArrayName, (void *) &pfpMask[i * bKernelSide]); 
  }

  fRet &= Program.Run(&out);

  return fRet;
}

bool _average(Array& src, Array& dest)
{
  bool fRet = true;

  Program Program;
  fRet &= Program.Create("average.cg", "Average");
  fRet &= Program.SetParameter(Program::enTexture, "src", (void *) src.Id());
  fRet &= Program.SetParameter(Program::enTexture, "dest", (void *) dest.Id());
  fRet &= Program.Run(&dest);

  return fRet;
}

bool _subtract(Array& op1, Array& op2, Array& dest)
{
  bool fRet = true;

  Program Program;
  fRet &= Program.Create("subtract.cg", "Subtract");
  fRet &= Program.SetParameter(Program::enTexture, "op1", (void *) op1.Id());
  fRet &= Program.SetParameter(Program::enTexture, "op2", (void *) op2.Id());
  fRet &= Program.Run(&dest);

  return fRet;
}