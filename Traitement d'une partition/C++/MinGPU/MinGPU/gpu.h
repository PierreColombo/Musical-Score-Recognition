#ifndef _MINGPU

#include <GL/glew.h>
#include <GL/glut.h>
#include <Cg/cgGL.h>
#include "../Vision/image.h"
#include <

extern GLenum errGL;
extern CGerror errCG;
extern 	GLuint fb;
extern bool g_fGPUInitialized;

#define INIT {if (g_fGPUInitialized == false) MinGPUInit(true); g_fGPUInitialized = true;}

bool MinGPUInit(bool);

class Array {
public:

  // Constructors
	Array() {INIT; m_tex = 0; m_pBuf = NULL; m_pData = NULL;};
  ~Array() {if (m_tex != 0) glDeleteTextures (1, &m_tex); if (m_pBuf != NULL) delete [] m_pBuf;};

  // Methods
  bool Create(CImage& , BYTE);
  bool Create(float *, unsigned int, unsigned int, BYTE);
	bool CopyToGPU();
	bool CopyFromGPU();

  // Accessors
  float *getData() {return m_pData;};
  unsigned int Cols() { return m_dwCols;};
  unsigned int Rows() { return m_dwRows;};
  GLuint *Id() { return &m_tex;};

  // Enumerators
  enum {enLuminance = 0, enRGBA};

private:
 	unsigned int m_dwCols, m_dwRows;
	GLuint m_tex;
  float *m_pBuf;    // if this pointer is not null, it contains a pointer to an allocated buffer
                    // which needs to be released by Array class destructor
	float *m_pData;   // if this pointer is not null, it contains a valid pointer to a properly sized buffer
                    // for an array. This buffer might have been created either inside or outside of Array class
  int m_bMode;
  int m_nColorMode;
};

class Program {
public:

  // Constructors
	Program() {INIT;};
	~Program() {};

  // Methods
	bool Create(char *, char *);
	bool SetParameter(int, char *, void *);
  bool Run(Array *);

  // Enumerators
	enum {enTexture = 0, enMatrixf = 1, enFloat, enArrayf};

private:
	CGprofile cgProfile;
  CGprogram cgProgram;

  bool LocateFile(char *, char *);
};

#define _MINGPU
#endif
