#include "stdafx.h"
#include "gpu.h"

GLenum g_errGL;
GLuint g_fb;
CGcontext g_cgContext;
bool g_fGPUInitialized = false;
bool g_fScreenOutput = true;
bool g_fcgError = false;
#define CG_NOERROR {g_fcgError = false;}
#define GL_ERROR_CHECK(ClassName, ProcName) if((g_errGL = glGetError()) != GL_NO_ERROR && g_fScreenOutput) {printf("MinGPU error in "#ClassName"::"#ProcName": %s\n", gluErrorString(g_errGL)); return false;}

static void cgErrorCallback()
{
  CGerror cgError = cgGetError();

  if(cgError && g_fScreenOutput)
  {
    std::printf("MinGPU Cg Error: %s\n", cgGetErrorString(cgError));
    if (cgError == CG_COMPILER_ERROR)
    {
      std::printf("%s\n", cgGetLastListing(g_cgContext));
    }
    g_fcgError = true;
  }
}

bool MinGPUInit(bool fScreenOutput)
{
  g_fScreenOutput = fScreenOutput;

  int argc = 1; char *arg0 = ""; g_fb = 0;
	glutInit(&argc, &arg0);
  if(!glutCreateWindow(""))
	{
    GL_ERROR_CHECK(MinGPUInit,)
		return false;
	}

  int nRet = glewInit();
  if (GLEW_OK != nRet)
	{
        if (fScreenOutput) printf((char*)glewGetErrorString(nRet));
        return false;
	}

  // create off-screen framebuffer object
  glGenFramebuffersEXT(1, &g_fb);

  // bind offscreen buffer
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, g_fb);

  // create an error callback for Cg library
  cgSetErrorCallback(cgErrorCallback);

  return true;
}

bool Array::Create(CImage& image, BYTE bMode)
{
	if (m_tex != 0)
	{
		if (g_fScreenOutput) printf("cannot call Array::Create more than once");
		return false;
	}

	// convert image to float
  switch (bMode)
  {
  case enLuminance:
    m_pBuf = new float[image.Cols() * image.Rows() * sizeof(float)];
  	for (unsigned int i = 1; i <= image.Rows(); i++)
	  {
		  for (unsigned int j = 1; j <= image.Cols(); j++)
		  {
			  m_pBuf[(i - 1) * image.Cols() + (j - 1)] = image.At(i, j);
		  }
	  }
    break;
  case enRGBA:
    m_pBuf = new float[image.Cols() * image.Rows() * sizeof(float) * 4];
  	for (unsigned int i = 1; i <= image.Rows(); i++)
	  {
		  for (unsigned int j = 1; j <= image.Cols(); j++)
		  {
        for (unsigned int k = 0; k < 4; k++)
        {
			    m_pBuf[4 * ((i - 1) * image.Cols() + (j - 1)) + k] = image.At(i, j);
        }
		  }
	  }
    break;
  default:
    return false;
  }
  return Create(m_pBuf, image.Cols(), image.Rows(), bMode);
}

bool Array::Create(float *pData, unsigned int dwCols, unsigned int dwRows, BYTE bMode)
{
	if (m_tex != 0)
	{
		if (g_fScreenOutput) printf("cannot call Array::Create more than once");
		return false;
	}

	m_pData = pData;
	m_dwCols = dwCols;
	m_dwRows = dwRows;
  m_bMode = bMode;

	glGenTextures (1, &m_tex); GL_ERROR_CHECK(Array, Create)

	// bind the array name to a texture
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, m_tex); GL_ERROR_CHECK(Array, Create)

	// turn off filtering and set proper wrap mode
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST); GL_ERROR_CHECK(Array, Create)
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST); GL_ERROR_CHECK(Array, Create)
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP); GL_ERROR_CHECK(Array, Create)
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP); GL_ERROR_CHECK(Array, Create)
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// allocate graphics memory
  switch (bMode)
  {
    case enLuminance:
      m_nColorMode = GL_LUMINANCE;
     	glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_FLOAT_R32_NV, dwCols, dwRows, 0, m_nColorMode, GL_FLOAT, 0);	GL_ERROR_CHECK(Array, Create)
      break;
    case enRGBA:
      m_nColorMode = GL_RGBA;
     	glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_FLOAT_RGBA32_NV, dwCols, dwRows, 0, m_nColorMode, GL_FLOAT, 0);	GL_ERROR_CHECK(Array, Create)
      break;
    default:
		  if (g_fScreenOutput) printf("Unknown color mode specified in call to Array::Create");
  		return false;
  }
	return true;
}

bool Array::CopyToGPU()
{
	// bind the array name to an array target
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, m_tex); GL_ERROR_CHECK(Array, CopyToGPU)

	// transfer an array to a GPU
  if (m_pData != NULL)
  {
	  glTexSubImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, 0, 0, m_dwCols, m_dwRows, m_nColorMode, GL_FLOAT, (void *) m_pData); GL_ERROR_CHECK(Array, CopyToGPU)
  }

	return true;
}

bool Array::CopyFromGPU()
{
	if (m_pData == NULL)
	{
    switch (m_bMode)
    {
      case enLuminance:
        m_pData = m_pBuf = new float[m_dwCols * m_dwRows * sizeof(float)];
        break;
      case enRGBA:
        m_pData = m_pBuf = new float[m_dwCols * m_dwRows * sizeof(float) * 4];
        break;
      default:
        return false;
    }
	}

  // read an array from a GPU
  glReadBuffer(GL_COLOR_ATTACHMENT0_EXT); GL_ERROR_CHECK(Array, CopyFromGPU)
	glReadPixels(0, 0, m_dwCols, m_dwRows, m_nColorMode, GL_FLOAT, m_pData); GL_ERROR_CHECK(Array, CopyFromGPU)

	return true;
}

bool Program::Create(char *szFilename, char *szEntryPoint)
{
	CG_NOERROR

  // set up Cg
	g_cgContext = cgCreateContext();
	cgProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
	cgGLSetOptimalOptions(cgProfile);
  cgGLSetManageTextureParameters(g_cgContext, CG_TRUE);

	// create a program
  char szFullname[_MAX_PATH] = {'\x0'};
  if (!LocateFile(szFilename, szFullname))
  {
		if (g_fScreenOutput) printf("File %s not found", szFilename);
		return false;
  }

  // verify binary file with the same or later date
  char szBinaryname[_MAX_PATH] = {'\x0'};
  sprintf(szBinaryname, "%s.%s.asm", szFullname, szEntryPoint);

  struct __stat64 SourceFileStatus;
  struct __stat64 BinaryFileStatus;
  int nRet1 = _stat64(szFullname, &SourceFileStatus);
  int nRet2 = _stat64(szBinaryname, &BinaryFileStatus);
  double dbTimeDiff = -1;
  if (nRet1 != -1 && nRet2 != -1)
  {
    dbTimeDiff = difftime(BinaryFileStatus.st_mtime, SourceFileStatus.st_mtime);
  }

  if (nRet1 != -1 && nRet2 != -1 && dbTimeDiff >= 0)
  {
    // if binary file does exist, and its date is later than source file, use it to create the program
    cgProgram = cgCreateProgramFromFile(g_cgContext, CG_OBJECT, szBinaryname, cgProfile, szEntryPoint, NULL);
  }
  else
  {
    // if binary file does not exist, or exists with older date, create it
    cgProgram = cgCreateProgramFromFile(g_cgContext, CG_SOURCE, szFullname, cgProfile, szEntryPoint, NULL);
    const char* szProgSrc = cgGetProgramString(cgProgram, CG_COMPILED_PROGRAM);
    long N = strlen(szProgSrc);
    FILE *F = fopen(szBinaryname, "wb");
    fwrite(szProgSrc, 1, N, F);
    fclose(F);
  }

	return !g_fcgError;
}

bool Program::SetParameter(int nType, char *szName, void *pValue)
{
	CG_NOERROR

  // get parameter handles by name
	CGparameter Param = cgGetNamedParameter(cgProgram, szName);

	switch (nType)
	{
	case enTexture:
		// set texture parameter
		cgGLSetTextureParameter(Param, * (int *)pValue);
		break;
	case enMatrixf:
		cgGLSetMatrixParameterfr(Param, (float *)pValue);
		break;
	case enArrayf:
		cgGLSetParameterArray1f(Param, 0, 0, (float *)pValue);
		break;
	case enFloat:
		cgGLSetParameter1f(Param, * (float *)pValue);
		break;
	default:
		return false;
	}

	return !g_fcgError;
}

bool Program::Run(Array *output)
{
  // load program
	cgGLLoadProgram(cgProgram);

	// enable fragment profile
	cgGLEnableProfile(cgProfile);

	// bind a program
	cgGLBindProgram(cgProgram);

  // set projection mode and viewport dimensions
  glMatrixMode(GL_PROJECTION); GL_ERROR_CHECK(Program, Run)
  glLoadIdentity(); GL_ERROR_CHECK(Program, Run)
  gluOrtho2D(0.0, output->Cols(), 0.0, output->Rows()); GL_ERROR_CHECK(Program, Run)
  glViewport(0, 0, output->Cols(), output->Rows()); GL_ERROR_CHECK(Program, Run)

  // attach output array
  glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_RECTANGLE_ARB, *output->Id(), 0); GL_ERROR_CHECK(Program, Run)

	// set the array as render target
	glDrawBuffer (GL_COLOR_ATTACHMENT0_EXT); GL_ERROR_CHECK(Program, Run)

	// make quad filled to hit every pixel/texel
	glPolygonMode(GL_FRONT, GL_FILL); GL_ERROR_CHECK(Program, Run)

	// render quad
	glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(0.0, 0.0);
    glTexCoord2f(output->Cols(), 0.0);
    glVertex2f(output->Cols(), 0.0);
    glTexCoord2f(output->Cols(), output->Rows());
    glVertex2f(output->Cols(), output->Rows());
    glTexCoord2f(0.0, output->Rows());
    glVertex2f(0.0, output->Rows());
	glEnd();

	GL_ERROR_CHECK(Program, Run)

  cgGLDisableProfile(cgProfile);

	return true;
}

bool Program::LocateFile(char *szFilename, char *szFullname)
{
  struct _stat buffer;
  char szWorkingDirectory[_MAX_PATH] = {'\x0'};
  char szPath[_MAX_PATH];

  getcwd(szWorkingDirectory, _MAX_PATH);
  if (szWorkingDirectory == NULL)
  {
    return false;
  }

  // look in current folder first
  sprintf(szPath, "%s\\%s", szWorkingDirectory, szFilename);

  if (_stat(szPath, &buffer) == 0)
  {
    strcpy(szFullname, szPath);
    return true;
  }
  // then look in 'scripts' subfolder
  sprintf(szPath, "%s\\%s\\%s", szWorkingDirectory, "scripts", szFilename);

  if (_stat(szPath, &buffer) == 0)
  {
    strcpy(szFullname, szPath);
    return true;
  }

  return false;
}
