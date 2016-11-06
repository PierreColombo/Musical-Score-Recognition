#include "stdafx.h"
#include "../../MinGPU/gpu.h"
#include "../../math/matrix.h" 
#include "../image.h" 
#include "common.h"
#include "pyramid.h" 

bool ReducePyramid(CImage& image, CImage& result, float *pfpMask)
{
  bool fRet = true;

  Array In;
  Array Out;

  fRet &= In.Create(image, Array::enLuminance);
  fRet &= Out.Create(NULL, result.Cols(), result.Rows(), Array::enLuminance);
	fRet &= In.CopyToGPU();

	// create, load and run a program
  fRet &= _reducepyramid(In, Out, pfpMask);
  fRet &= Out.CopyFromGPU();

	result.Import(Out.getData(), Out.Cols());

  return fRet;
}

