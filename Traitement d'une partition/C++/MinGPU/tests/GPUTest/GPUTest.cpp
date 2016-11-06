
#include "stdafx.h"
#include "../../math/matrix.h"
#include "../../vision/vision.h"

void HomographyTest()
{
  const SLICES = 100;
  const VIEWS = 59;

  CMatrix <float> Hinv[SLICES][VIEWS];

	// read homographies from file
	char filename2[256];
	for (int slice = 1; slice <= SLICES; slice++)
	{
    FILE *F;

		sprintf(filename2, "c:\\image\\homographies\\inverse%d.txt", slice);
		F = fopen(filename2, "rb");
		for (int i = 1; i <= VIEWS; i++)
		{
			Hinv[slice - 1][i-1].Create(3, 3);
			fread(Hinv[slice - 1][i-1].pdata, 4, 3 * 3, F);
		}
		fclose(F);
	}

  __int64 lnFreq; QueryPerformanceFrequency((LARGE_INTEGER *) &lnFreq);
  __int64 lnStart; QueryPerformanceCounter((LARGE_INTEGER *) &lnStart);

  HomographyGPU("c:\\image\\foregrounds_binary", VIEWS, SLICES, (CMatrix <float> *) Hinv, 
                "c:\\image\\homography_result", 5, 0, 100, 100, 100);

  __int64 lnEnd; QueryPerformanceCounter((LARGE_INTEGER *) &lnEnd);
	printf("GPU time = %.2f ms (%I64u ticks)\n\n", 1000. * (lnEnd - lnStart) / (float)lnFreq, (lnEnd - lnStart));
}

void GaussianTest()
{
  CImage image;
  bool bRet = image.Read("e:\\peppers_out6.pgm");
  //bool bRet = image.Read("c:\\tmp\\0001.pgm");
  if (!bRet)
  {
    return;
  }
  gpuGaussian(image, image, 1, 3, enNoDerivative);

	image.Write("e:\\peppers_out7.pgm");
}

void DerivativeTest()
{
  CImage image;
  bool bRet = image.Read("e:\\peppers_noise.pgm");
  if (!bRet)
  {
    return;
  }
  gpuDY(image, image);

	image.Write("c:\\tmp\\peppers_outY.pgm");
}

void PyramidTest()
{
  CImage image;
  CImage result;
  bool bRet = image.Read("c:\\image\\t9.pgm");
  if (!bRet)
  {
    return;
  }
  bRet = result.Create(image.Rows() / 2, image.Cols() / 2, 255, _NO_INIT);

  // create simple weight mask 
  float Mask[5][5] = {{1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}};
  ReducePyramid(image, result, (float *) &Mask);

	result.Write("c:\\image\\t9.pgm");
}

void OpticalFlowTest()
{
  CImage imageT1;
  bool bRet = imageT1.Read("c:\\image\\flower00.pgm");
  if (!bRet)
  {
    return;
  }

  __int64 lnFreq; QueryPerformanceFrequency((LARGE_INTEGER *) &lnFreq);
  __int64 lnStart; QueryPerformanceCounter((LARGE_INTEGER *) &lnStart);

  bRet = OpticalFlowReset(imageT1);

  CImage U;
  CImage V;
  bRet = U.Create(imageT1.Rows(), imageT1.Cols(), 255, 0);
  bRet = V.Create(imageT1.Rows(), imageT1.Cols(), 255, 0);

  CImage imageT2;
  char buf[_MAX_PATH];
  for (int i = 1; i <= 30; i++)
  {
    sprintf(buf, "c:\\image\\flower%02d.pgm", i);
    bRet = imageT2.Read(buf);
    if (!bRet)
    {
      return;
    }
    
    bRet = OpticalFlow(imageT2, U, V);
    if (!bRet)
    {
      return;
    }

    sprintf(buf, "c:\\image\\U%02d.pgm", i);
    U.Write(buf);
    sprintf(buf, "c:\\image\\V%02d.pgm", i);
    V.Write(buf);
  }
  // matlab quiver() function is then used to build flow map

  __int64 lnEnd; QueryPerformanceCounter((LARGE_INTEGER *) &lnEnd);
	printf("GPU time = %.2f ms (%I64u ticks)\n\n", 1000. * (lnEnd - lnStart) / (float)lnFreq, (lnEnd - lnStart));

}

void CorrelationTest()
{
  CImage image;
  CImage t[7];
  bool bRet = image.Read("c:\\image\\clip4.pgm");
  if (!bRet)
  {
    return;
  }

  // load a stack of filters
  for (int i = -9, j = 0; i <= 9; i += 3, j++)
  {
    char buf[_MAX_PATH];
    sprintf(buf, "c:\\image\\t%d.pgm", i);
    bRet = t[j].Read(buf);
    if (!bRet)
    {
      return;
    }
  }

  // 100% positive filter, for testing ..
  //bRet = t[0].Read("c:\\image\\filter.pgm");

  __int64 lnFreq; QueryPerformanceFrequency((LARGE_INTEGER *) &lnFreq);
  __int64 lnStart; QueryPerformanceCounter((LARGE_INTEGER *) &lnStart);

  CImage result;
  bRet = result.Create(image.Rows(), image.Cols(), 255, 0);
  Correlation(image, result, t, 7);

  __int64 lnEnd; QueryPerformanceCounter((LARGE_INTEGER *) &lnEnd);
	printf("GPU time = %.2f ms (%I64u ticks)\n\n", 1000. * (lnEnd - lnStart) / (float)lnFreq, (lnEnd - lnStart));

	result.Write("c:\\image\\y2.pgm");
}

int _tmain(int argc, _TCHAR* argv[])
{
  //HomographyTest();
  //DerivativeTest();
  //GaussianTest();
  //PyramidTest();
  OpticalFlowTest();
  //CorrelationTest();
  return 0;
}

