#ifndef _MATH_MATRIX

template <class T>
class CMatrix {
public:
	int m_nRows;
	int m_nCols;
	T *pdata;

	CMatrix() {pdata = NULL;};
	~CMatrix() {if (pdata) delete pdata;};
	void Create(int, int);
	T& At(int row, int col) {return pdata[(row - 1) * m_nCols + col - 1];}; // upper left corner is (1,1)

	CMatrix(CMatrix<T>& src) 
	{ 
		pdata = NULL;
		Create(src.m_nRows, src.m_nCols);
		memcpy(pdata, src.pdata, src.m_nRows * src.m_nCols * sizeof(T));
	}

	CMatrix<T>& operator =(CMatrix<T>& src) 
	{ 
		Create(src.m_nRows, src.m_nCols);
		memcpy(pdata, src.pdata, src.m_nRows * src.m_nCols * sizeof(T));
		return *this;
	}

	CMatrix<T> operator /(T div)
	{
		CMatrix<T> res;
		res.Create(m_nRows, m_nCols);
		for (int i = 1; i <= m_nRows; i++)
		{
			for (int j = 1; j <= m_nCols; j++)
			{
				res.At(i, j) = At(i, j) / div;
			}
		}
		return res;
	}

	CMatrix<T> operator *(CMatrix<T>& op2) 
	{ 
		CMatrix<T> res;
		res.Create(m_nRows, op2.m_nCols);
		if(op2.m_nRows != m_nCols)
		{
			// error, return empty matrix
			printf("matrix dimensions do not agree\n");
			return res;
		}

		for (int i = 1; i <= m_nRows; i++)
		{
			for (int j = 1; j <= op2.m_nCols; j++)
			{
				for (int k = 1; k <= m_nCols; k++)
				{
					res.At(i, j) += At(i, k) * op2.At(k, j);
				}
			}
		}
		return res;
	}

	CMatrix<T> Transpose() 
	{ 
		CMatrix<T> res;
		res.Create(m_nCols, m_nRows);
		for (int i = 1; i <= m_nRows; i++)
		{
			for (int j = 1; j <= m_nCols; j++)
			{
				res.At(i, j) = At(j, i);
			}
		}
		return res;
	}

	T Min()
	{
		T res = At(1, 1);
		for (int i = 1; i <= m_nRows; i++)
		{
			for (int j = 1; j <= m_nCols; j++)
			{
				if (res > At(i, j)) res = At(i, j);
			}
		}
		return res;
	}

	T Max()
	{
		T res = At(1, 1);
		for (int i = 1; i <= m_nRows; i++)
		{
			for (int j = 1; j <= m_nCols; j++)
			{
				if (res < At(i, j)) res = At(i, j);
			}
		}
		return res;
	}


private:
	
};

template <class T>
void CMatrix<T>::Create(int nRows, int nCols) 
{
	if (pdata != NULL)
	{
		delete pdata;
		pdata = NULL;
	}

	m_nRows = nRows;
	m_nCols = nCols;

	pdata = new T[m_nRows * m_nCols];
	memset(pdata, 0, m_nRows * m_nCols * sizeof(T));
}

#define _MATH_MATRIX
#endif
