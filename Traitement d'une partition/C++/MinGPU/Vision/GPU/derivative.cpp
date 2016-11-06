#include "stdafx.h"
#include "../../MinGPU/gpu.h"
#include "../../math/matrix.h" 
#include "../image.h" 
#include "common.h"
#include "derivative.h" 

bool gpuDX(CImage& image, CImage& result)
{
  bool fRet = true;

  Array In;
  Array Out;
  fRet &= In.Create(image, Array::enLuminance);
  fRet &= Out.Create(NULL, image.Cols(), image.Rows(), Array::enLuminance);
	fRet &= In.CopyToGPU();

  // create convolution kernel for DX
  float K[3][3] = {{0, 0, 0}, {0, -1, 1}, {0, 0, 0}};

	// create, load and run a program
  fRet &= _convolve(In, Out, (float *) &K, 3);
  fRet &= Out.CopyFromGPU();

	result.Import(Out.getData(), result.Cols());

  return fRet;
}

bool gpuDY(CImage& image, CImage& result)
{
  bool fRet = true;

  Array In;
  Array Out;
  fRet &= In.Create(image, Array::enLuminance);
  fRet &= Out.Create(NULL, image.Cols(), image.Rows(), Array::enLuminance);
	fRet &= In.CopyToGPU();

  // create convolution kernel for DY
  float K[3][3] = {{0, 0, 0}, {0, -1, 0}, {0, 1, 0}};

	// create, load and run a program
  fRet &= _convolve(In, Out, (float *) &K, 3);
  fRet &= Out.CopyFromGPU();

	result.Import(Out.getData(), result.Cols());

  return fRet;
}
