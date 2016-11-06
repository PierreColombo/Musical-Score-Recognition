#include "stdafx.h"
#include "../../MinGPU/gpu.h"
#include "../../math/matrix.h" 
#include "../image.h" 
#include "common.h"
#include "opticalflow.h" 

CImage* im1 = NULL;
Array* T1 = NULL;

bool OpticalFlowReset(CImage& im)
{
  bool fRet = true;

  if (T1 != NULL)
  {
    delete T1;
  }
  T1 = new Array;

  im1 = &im;
  fRet &= T1->Create(*im1, Array::enLuminance);
	fRet &= T1->CopyToGPU();
  return fRet;
}

bool OpticalFlow(CImage& im2, CImage& imU, CImage& imV)
{
  bool fRet = true;

  Array* T2 = new Array;
  fRet &= T2->Create(im2, Array::enLuminance);
	fRet &= T2->CopyToGPU();

  Array result;
  fRet &= result.Create(NULL, imU.Cols(), imU.Rows(), Array::enRGBA);

  Array Ix, Iy, It, Itmp; 
  fRet &= Ix.Create(NULL, imU.Cols(), imU.Rows(), Array::enLuminance);
  fRet &= Iy.Create(NULL, imU.Cols(), imU.Rows(), Array::enLuminance);
  fRet &= It.Create(NULL, imU.Cols(), imU.Rows(), Array::enLuminance);
  fRet &= Itmp.Create(NULL, imU.Cols(), imU.Rows(), Array::enLuminance);

  // Take derivative from both input images, and average them
  // X direction ...
  float Kx[3][3] = {{0, 0, 0}, {0, -1, 1}, {0, 0, 0}};
  fRet &= _convolve(*T1, Ix, (float *) &Kx, 3);
  fRet &= _convolve(*T2, Itmp, (float *) &Kx, 3);

  // average over Ix ...
  fRet &= _average(Itmp, Ix);

  // Y direction ...
  float Ky[3][3] = {{0, 0, 0}, {0, -1, 0}, {0, 1, 0}};
  fRet &= _convolve(*T1, Iy, (float *) &Ky, 3);
  fRet &= _convolve(*T2, Itmp, (float *) &Ky, 3);
  // average over Iy ...
  fRet &= _average(Itmp, Iy);

  // T direction ...
  fRet &= _subtract(*T2, *T1, It);

  // Calculate sums in 5x5 area
  Array SIx2, SIy2, SIxIy, SIxIt, SIyIt; 
  fRet &= SIx2.Create(NULL, imU.Cols(), imU.Rows(), Array::enLuminance);
  fRet &= SIy2.Create(NULL, imU.Cols(), imU.Rows(), Array::enLuminance);
  fRet &= SIxIy.Create(NULL, imU.Cols(), imU.Rows(), Array::enLuminance);
  fRet &= SIxIt.Create(NULL, imU.Cols(), imU.Rows(), Array::enLuminance);
  fRet &= SIyIt.Create(NULL, imU.Cols(), imU.Rows(), Array::enLuminance);

  Program Program;
  fRet &= Program.Create("opticalflow.cg", "Sum2");
  fRet &= Program.SetParameter(Program::enTexture, "I", (void *) Ix.Id());
  fRet &= Program.Run(&SIx2);

  fRet &= Program.Create("opticalflow.cg", "Sum2");
  fRet &= Program.SetParameter(Program::enTexture, "I", (void *) Iy.Id());
  fRet &= Program.Run(&SIy2);

  fRet &= Program.Create("opticalflow.cg", "SumXY");
  fRet &= Program.SetParameter(Program::enTexture, "X", (void *) Ix.Id());
  fRet &= Program.SetParameter(Program::enTexture, "Y", (void *) Iy.Id());
  fRet &= Program.Run(&SIxIy);

  fRet &= Program.Create("opticalflow.cg", "SumXY");
  fRet &= Program.SetParameter(Program::enTexture, "X", (void *) Ix.Id());
  fRet &= Program.SetParameter(Program::enTexture, "Y", (void *) It.Id());
  fRet &= Program.Run(&SIxIt);

  fRet &= Program.Create("opticalflow.cg", "SumXY");
  fRet &= Program.SetParameter(Program::enTexture, "X", (void *) Iy.Id());
  fRet &= Program.SetParameter(Program::enTexture, "Y", (void *) It.Id());
  fRet &= Program.Run(&SIyIt);

  // apply matrix operations and calculate u, v
  fRet &= Program.Create("opticalflow.cg", "OpticalFlow");
  fRet &= Program.SetParameter(Program::enTexture, "SIx2", (void *) SIx2.Id());
  fRet &= Program.SetParameter(Program::enTexture, "SIy2", (void *) SIy2.Id());
  fRet &= Program.SetParameter(Program::enTexture, "SIxIy", (void *) SIxIy.Id());
  fRet &= Program.SetParameter(Program::enTexture, "SIxIt", (void *) SIxIt.Id());
  fRet &= Program.SetParameter(Program::enTexture, "SIyIt", (void *) SIyIt.Id());
  fRet &= Program.Run(&result);

  fRet &= result.CopyFromGPU();

	imU.Import(result.getData(), imU.Cols(), 1); 
  imV.Import(result.getData(), imU.Cols(), 2); 

  im1 = &im2;
  if (T1 != NULL)
  {
    delete T1;
  }
  T1 = T2;

  return fRet;
}

