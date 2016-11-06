#include "stdafx.h"
#include "../../MinGPU/gpu.h"
#include "../../math/matrix.h" 
#include "../image.h" 
#include "common.h"
#include "gaussian.h" 

bool gpuGaussian(CImage& image, CImage& result, float fpSigma, BYTE bKernelSide, BYTE bDerivative)
{
  bool fRet = true;
  Array In;
  Array Out;

  // verify if bKernelSide is in valid range. 3, 5, 7 are currently supported
  if (bKernelSide != 3 && bKernelSide != 5 && bKernelSide != 7)
  {
    return false;
  }

	// convert image to float and copy to GPU
  fRet &= In.Create(image, Array::enLuminance);
  fRet &= Out.Create(NULL, image.Cols(), image.Rows(), Array::enLuminance);
	fRet &= In.CopyToGPU();

  // create convolution kernel
  float *pfpKernel = new float[bKernelSide * bKernelSide];
	switch (bDerivative)
	{
	  case enNoDerivative:
      for (unsigned int row = 0; row < bKernelSide; row++)
      {
        for (unsigned int col = 0; col < bKernelSide; col++)
        {
          pfpKernel[ row * bKernelSide + col] = 1;
        }
      }
		  break;
	  case enFirstPartialDerivativeX:
      for (unsigned int row = 0; row < bKernelSide; row++)
      {
        for (unsigned int col = 0; col < bKernelSide; col++)
        {
          pfpKernel[ row * bKernelSide + col] = 0;
        }
      }
	  	break;
	  case enFirstPartialDerivativeY:
      for (unsigned int row = 0; row < bKernelSide; row++)
      {
        for (unsigned int col = 0; col < bKernelSide; col++)
        {
          pfpKernel[ row * bKernelSide + col] = 0;
        }
      }
	  	break;
	  case enSecondPartialDerivativeX:
      for (unsigned int row = 0; row < bKernelSide; row++)
      {
        for (unsigned int col = 0; col < bKernelSide; col++)
        {
          pfpKernel[ row * bKernelSide + col] = 0;
        }
      }
		  break;
	  case enSecondPartialDerivativeY:
      for (unsigned int row = 0; row < bKernelSide; row++)
      {
        for (unsigned int col = 0; col < bKernelSide; col++)
        {
          pfpKernel[ row * bKernelSide + col] = 0;
        }
      }
		  break;
	  default:
		  // verify	if bKernelSide is	in valid range.	3, 5,	7	are	currently	supported
		  return false;
	}

	// create and load a program
  fRet &= _convolve(In, Out, pfpKernel, bKernelSide);
  fRet &= Out.CopyFromGPU();

	result.Import(Out.getData(), result.Cols());

  delete [] pfpKernel;
  return fRet;
}