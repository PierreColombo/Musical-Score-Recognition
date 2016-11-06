
#include "stdafx.h"
#include "../../MinGPU/gpu.h"
#include "../../math/matrix.h" 
#include "../image.h" 
#include "homography.h" 

void HomographyGPU(char *szInputFolder, int nViews, int nSlices, CMatrix <float> *Hinv, 
                      char *szOutputFolder, float fpRatio, int cx, int cy, int dx, int dy)
{
	float *pbuf = NULL;
	bool fRet = true;

	float left = cx - dx * fpRatio, right = cx + dx * fpRatio, top = cy - dy * fpRatio, bottom = cy + dy * fpRatio;
	int	xdim = dx * 2, ydim = dy * 2;

  // load arrays into GPU
	CImage image;
	Array *pTex = new Array[nViews];
	char filename[_MAX_PATH];
	for (int k = 1; k <= nViews; k++)
	{
		sprintf(filename, "%s/%04d.pgm", szInputFolder, k);
		fRet = image.Read(filename);
		//image.ScaleTo(1);

		// convert image to float and copy to GPU
		fRet &= pTex[k-1].Create(image, Array::enLuminance);
		fRet &= pTex[k-1].CopyToGPU();
	}

	// create and load a program
	Program Program;
	fRet &= Program.Create("homography.cg", "Homography");
	fRet &= Program.SetParameter(Program::enFloat, "ratio", (void *) &fpRatio);
	fRet &= Program.SetParameter(Program::enFloat, "x1", (void *) &left);
	fRet &= Program.SetParameter(Program::enFloat, "y1", (void *) &top);

	// process all slices and files
	pbuf = new float[xdim * ydim * sizeof(float)];
	for (int slice = 1; slice <= nSlices; slice ++)
	{
		CImage Slice;
		Slice.Create(ydim, xdim, 255, 0);

		// create and load empty array for output
		Array Accumulator;
    fRet &= Accumulator.Create(pbuf, xdim, ydim, Array::enLuminance);

		// point a program to output array
		fRet &= Program.SetParameter(Program::enTexture, "result", (void *) Accumulator.Id()); 

		for (int i = 1; i <= nViews; i++)
		{
			// set program parameters: input array and homography matrix
			fRet &= Program.SetParameter(Program::enTexture, "view", (void *) pTex[i-1].Id()); 
      fRet &= Program.SetParameter(Program::enMatrixf, "H", (void *) &Hinv[(slice - 1) * nViews + (i - 1)].At(1, 1)); 

			// run the program
			fRet &= Program.Run(&Accumulator);
		}
		// recover results from the program
		fRet &= Accumulator.CopyFromGPU();

		// convert output image to BYTE and save them as PGM file
		sprintf(filename, "%s\\%05d.pgm", szOutputFolder, slice);
    Slice.Import(Accumulator.getData(), xdim);
		Slice.Write(filename);
	}
	
  delete [] pbuf;
  delete [] pTex;

	return;
}

