#ifndef _VISION_IMAGE

#define _NO_INIT 0x80
typedef unsigned char BYTE;

class CImage {
public:
	CImage() {m_pdata = NULL; };
	~CImage() {if (m_pdata) delete [] m_pdata;};
	bool Read(char *);
	bool Write(char *);
	bool Create(unsigned int, unsigned int, BYTE bMaxValue = 255, BYTE bInitialValue = 0);
	template <class T> bool Import(T *, unsigned int);
  template <class T> bool Import(T *, unsigned int, unsigned int);
	bool Add(CImage &);
	bool ScaleTo(BYTE);
	bool Flip();
	BYTE Max();
	BYTE& At(unsigned int row, unsigned int col) // upper left corner is (1,1)
	{
		if (row <= 0 || row > m_dwRows || col <= 0 || col > m_dwCols) return bOutsideOfDataArea;
		else return m_pdata[(row - 1) * m_dwCols + col - 1];
	};
  unsigned int Cols() { return m_dwCols;};
  unsigned int Rows() { return m_dwRows;};

private:
	BYTE *m_pdata;
	unsigned int m_dwCols;
	unsigned int m_dwRows;
	BYTE m_bMaxValue;
  static BYTE bOutsideOfDataArea;

	bool ReadPGM(FILE *);
	bool WritePGM(FILE *);
};

template <class T>
bool CImage::Import(T *pExtData, unsigned int dwTotalCols)
{
	T res = pExtData[0];
	for (unsigned int i = 1; i <= m_dwRows; i++)
	{
		for (unsigned int j = 1; j <= m_dwCols; j++)
		{
			if (res < pExtData[(i-1) * dwTotalCols + (j-1)]) res = pExtData[(i-1) * dwTotalCols + (j-1)];
		}
	}

	float fpScaleRatio = res / (float) m_bMaxValue;
	if (fpScaleRatio <= 1)
	{
		fpScaleRatio = 1;
	}
	for (unsigned int i = 1; i <= m_dwRows; i++)
	{
		for (unsigned int j = 1; j <= m_dwCols; j++)
		{
			At(i, j) = pExtData[((i-1) * dwTotalCols + (j-1))] / fpScaleRatio;
		}
	}
	return true;
}

// this is an import from color 4-rgb image, from column C (one of RGBA columns)
template <class T>
bool CImage::Import(T *pExtData, unsigned int dwTotalCols, unsigned int dwCol)
{
	T res = pExtData[0];
	for (unsigned int i = 1; i <= m_dwRows; i++)
	{
		for (unsigned int j = 1; j <= m_dwCols; j++)
		{
			if (res < pExtData[((i-1) * dwTotalCols + (j-1)) * 4 + (dwCol - 1)]) res = pExtData[((i-1) * dwTotalCols + (j-1)) * 4 + (dwCol - 1)];
		}
	}

	float fpScaleRatio = res / (float) m_bMaxValue;
	if (fpScaleRatio <= 1)
	{
		fpScaleRatio = 1;
	}
	for (unsigned int i = 1; i <= m_dwRows; i++)
	{
		for (unsigned int j = 1; j <= m_dwCols; j++)
		{
			At(i, j) = pExtData[(((i-1) * dwTotalCols + (j-1))) * 4 + (dwCol - 1)] / fpScaleRatio;
		}
	}
	return true;
}


#define _VISION_IMAGE
#endif

