#include "stdafx.h"
#include "image.h" 
BYTE CImage::bOutsideOfDataArea = 0;

// Read image from file
bool CImage::Read(char *szFilename)
{
	bool fRet = true;
	FILE *F;

	if (m_pdata != NULL)
	{
		delete [] m_pdata;
		m_pdata = NULL;
	}

	char *szFileExt = strrchr(szFilename, '.');
	if (szFileExt == NULL)
	{
		return false;
	}

	F = fopen(szFilename, "rb");
	
	if (F == NULL)
	{
		return false;
	}

	if (stricmp(szFileExt, ".pgm") == 0)
	{
		fRet = ReadPGM(F);
	}
	else
	{
		// file format not supported
		fRet = false;
	}
	fclose(F);
	return fRet;
}

// Create and optionally fill new image
bool CImage::Create(unsigned int dwRows, unsigned int dwCols, BYTE bMaxValue, BYTE bInitialValue)
{
	if (m_pdata != NULL)
	{
		delete [] m_pdata;
		m_pdata = NULL;
	}

	m_dwCols = dwCols;
	m_dwRows = dwRows;
	m_bMaxValue = bMaxValue;

	m_pdata = new BYTE[m_dwRows * m_dwCols];
  if (bInitialValue != _NO_INIT)
  {
	  memset(m_pdata, bInitialValue, m_dwRows * m_dwCols * sizeof(BYTE));
  }

	return true;
}

// Read binary pgm (P5 format)
bool CImage::ReadPGM(FILE *F)
{
	fseek(F, 0, SEEK_SET);

	// these are arrays for pgm header, sized according to pgm standard
  char szSignature[5]; char szWidth[10]; char szHeight[10]; char szMaxvalue[10]; char szComment[71]; 

	do {
		fscanf(F, "%5s", szSignature);
		if (strcmp(szSignature, "#") == 0) fgets(szComment, 254, F);
	} while (strcmp(szSignature, "#") == 0);

	if (stricmp(szSignature, "P5") != 0)
	{
		return false;
	}

	do {
		fscanf(F, "%9s", szWidth);
		if (strcmp(szWidth, "#") == 0) fgets(szComment, 254, F);
	} while (strcmp(szWidth, "#") == 0);

	do {
		fscanf(F, "%9s", szHeight);
		if (strcmp(szHeight, "#") == 0) fgets(szComment, 254, F);
	} while (strcmp(szHeight, "#") == 0);

	int ret = fscanf(F, "%9s", szMaxvalue);

	m_dwCols = atoi(szWidth);
	m_dwRows = atoi(szHeight);
	m_bMaxValue = atoi(szMaxvalue);
	if (! (m_dwRows && m_dwCols && m_bMaxValue))
	{
		return false;
	}

	m_pdata = new BYTE[m_dwRows * m_dwCols];
  fread(m_pdata, 1, 1, F); // read end of line
	size_t dwBytesRead = fread(m_pdata, 1, m_dwRows * m_dwCols, F);
	if (dwBytesRead != m_dwRows * m_dwCols)
	{
		delete [] m_pdata;
		m_pdata = NULL;
		return false;
	}
	return true;
}

// Write file to a disk
bool CImage::Write(char *szFilename)
{
	bool fRet = true;
	if (m_pdata == NULL)
	{
		return false;
	}

  FILE *F;

	char *szFileExt = strrchr(szFilename, '.');
	if (szFileExt == NULL)
	{
		return false;
	}

	F = fopen(szFilename, "wb");
	
	if (F == NULL)
	{
		return false;
	}

	if (stricmp(szFileExt, ".pgm") == 0)
	{
		fRet = WritePGM(F);
	}
	else
	{
		// file format not supported
		fRet = false;
	}
	fclose(F);
	return fRet;
}

// Write binary pgm (P5)
bool CImage::WritePGM(FILE *F)
{
	fseek(F, 0, SEEK_SET);

	char szWidth[10]; char szHeight[10]; char szMaxvalue[10];
	itoa(m_dwCols, szWidth, 10);
	itoa(m_dwRows, szHeight, 10);
	itoa(m_bMaxValue, szMaxvalue, 10);
	fprintf(F, "P5 %s %s %s\n", szWidth, szHeight, szMaxvalue);

	size_t dwBytesWritten = fwrite(m_pdata, 1, m_dwRows * m_dwCols, F);
	if (dwBytesWritten != m_dwRows * m_dwCols)
	{
		return false;
	}
	return true;
}

// flips an image along Y axis
bool CImage::Flip()
{
  BYTE tmp;
	for (unsigned int row = 1; row <= m_dwRows / 2; row ++)
	{
		for (unsigned int col = 1; col <= m_dwCols; col ++)
		{
			tmp = At(row, col);
			At(row, col) = At(m_dwRows - row + 1, col);
			At(m_dwRows - row + 1, col) = tmp;
		}
	}
	return true;
}

bool CImage::Add(CImage& image)
{
	for (unsigned int i = 1; i <= m_dwRows; i++)
	{
		for (unsigned int j = 1; j <= m_dwCols; j++)
		{
			At(i, j) += image.At(i, j);
		}
	}
	return true;
}

BYTE CImage::Max()
{
	BYTE bMax = At(1, 1);
	for (unsigned int i = 1; i <= m_dwRows; i++)
	{
		for (unsigned int j = 1; j <= m_dwCols; j++)
		{
			if (bMax < At(i, j)) bMax = At(i, j);
		}
	}
	return bMax;
}

bool CImage::ScaleTo(BYTE bMax)
{
	float fpScaleRatio = Max() / (float) bMax;
	if (fpScaleRatio <= 1) 
	{
		return true;
	}
	for (unsigned int i = 1; i <= m_dwRows; i++)
	{
		for (unsigned int j = 1; j <= m_dwCols; j++)
		{
			At(i, j) /= fpScaleRatio;
		}
	}
	return true;
}
