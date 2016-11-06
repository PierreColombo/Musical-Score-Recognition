#include "stdafx.h"
#include "../../MinGPU/gpu.h"
#include "../../math/matrix.h" 
#include "../image.h" 
#include "common.h"
#include "correlation.h" 

bool Correlation(CImage& imf, CImage& res, CImage imt[], int cFilters)
{
  bool fRet = true;

  Array f;
  Array t[MAX_FILTERS];
  Array y[MAX_FILTERS];
  Array result;

  fRet &= f.Create(imf, Array::enLuminance);
  fRet &= f.CopyToGPU();
  fRet &= result.Create(res, Array::enLuminance);

  for (int i = 1; i <= cFilters; i++)
  {
    fRet &= t[i - 1].Create(imt[i - 1], Array::enLuminance);
    fRet &= t[i - 1].CopyToGPU();
    fRet &= y[i - 1].Create(NULL, imf.Cols(), imf.Rows(), Array::enLuminance);
  }

  // 1. Calculate favg for every image point
  Array favg; 
  fRet &= favg.Create(NULL, imf.Cols(), imf.Rows(), Array::enLuminance);
  Program _Program;
  fRet &= _Program.Create("correlation.cg", "favg");
  fRet &= _Program.SetParameter(Program::enTexture, "I", (void *) f.Id());
  fRet &= _Program.Run(&favg);

  // 2. Calculate f - favg (normalized f) for every image point
  Array fnorm; 
  fRet &= fnorm.Create(NULL, imf.Cols(), imf.Rows(), Array::enLuminance);
  fRet &= _Program.Create("subtract.cg", "Subtract");
  fRet &= _Program.SetParameter(Program::enTexture, "op1", (void *) f.Id());
  fRet &= _Program.SetParameter(Program::enTexture, "op2", (void *) favg.Id());
  fRet &= _Program.Run(&fnorm);

  //fRet &= fnorm.CopyFromGPU();
  //imf.Import(fnorm.getData(), imf.Cols()); 
  //imf.Write("c:\\image\\y.pgm");

  // 3. Calculate S(f - favg)^2 for every image point
  Array Snorm2; 
  fRet &= Snorm2.Create(NULL, imf.Cols(), imf.Rows(), Array::enLuminance);
  fRet &= _Program.Create("correlation.cg", "Snorm2");
  fRet &= _Program.SetParameter(Program::enTexture, "fnorm", (void *) fnorm.Id());
  fRet &= _Program.Run(&Snorm2);

  // do not load re-usable programs from disk every time ...
  Program Program1, Program2, Program3, Program4, Program5;
  fRet &= Program1.Create("correlation.cg", "tavg");
  fRet &= Program2.Create("correlation.cg", "tnorm");
  fRet &= Program3.Create("correlation.cg", "Tnorm2");
  fRet &= Program4.Create("correlation.cg", "Correlation");
  fRet &= Program5.Create("correlation.cg", "Accumulate");

  // for every filter ...
  Array tavg[MAX_FILTERS]; 
  Array tnorm[MAX_FILTERS]; 
  Array tnorm2[MAX_FILTERS]; 
  for (int i = 1; i <= cFilters; i++)
  {
    // 4. Calculate tavg. 
    
    fRet &= tavg[i - 1].Create(NULL, 1, 1, Array::enLuminance);
    fRet &= Program1.SetParameter(Program::enTexture, "t", (void *) t[i - 1].Id());
    fRet &= Program1.Run(&tavg[i - 1]);
    
    // 5. Calculate t-tavg for every image point
    fRet &= tnorm[i - 1].Create(NULL, imt[0].Cols(), imt[0].Rows(), Array::enLuminance);
    fRet &= Program2.SetParameter(Program::enTexture, "op1", (void *) t[i - 1].Id());
    fRet &= Program2.SetParameter(Program::enTexture, "op2", (void *) tavg[i - 1].Id());
    fRet &= Program2.Run(&tnorm[i - 1]);

    //fRet &= tnorm[i - 1].CopyFromGPU();
	  //imt[i - 1].Import(tnorm[i - 1].getData(), imt[i - 1].Cols()); 
    //imt[i - 1].Write("c:\\image\\y.pgm");

    // 6. Calculate S(t - tavg)^2. 
    fRet &= tnorm2[i - 1].Create(NULL, 1, 1, Array::enLuminance);
    fRet &= Program3.SetParameter(Program::enTexture, "tnorm", (void *) tnorm[i - 1].Id());
    fRet &= Program3.Run(&tnorm2[i - 1]);

    // 7. Now, calculate the formula, the denominator first then numerator
    fRet &= Program4.SetParameter(Program::enTexture, "fnorm", (void *) fnorm.Id());
    fRet &= Program4.SetParameter(Program::enTexture, "tnorm", (void *) tnorm[i - 1].Id());
    fRet &= Program4.SetParameter(Program::enTexture, "Snorm2", (void *) Snorm2.Id());
    fRet &= Program4.SetParameter(Program::enTexture, "Tnorm2", (void *) tnorm2[i - 1].Id());
    fRet &= Program4.Run(&y[i - 1]);

    fRet &= y[i - 1].CopyFromGPU();
	  imf.Import(y[i - 1].getData(), imf.Cols()); 
    imf.Write("c:\\image\\y.pgm");

    // 8. accumulate a maximum of absolute values in results
    fRet &= Program5.SetParameter(Program::enTexture, "acc", (void *) result.Id());
    fRet &= Program5.SetParameter(Program::enTexture, "y", (void *) y[i - 1].Id());
    fRet &= Program5.Run(&result);

  }
  // absolute values of results, scaled 255x times, are now ready in 'result' array. we can now use them ...

  // copy results to CImage and save them on disk as image. Note that Import truncates data to int and scales it to 255. 
  fRet &= result.CopyFromGPU();
	res.Import(result.getData(), res.Cols()); 

  return fRet;
}

