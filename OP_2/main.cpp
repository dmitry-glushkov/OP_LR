#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
using namespace std;

class FVector
{
private:

	int size;
	float *fv;

public:

	FVector() // FVector a;
	{
		size = 1;
		fv = new float[size];
	}

	explicit FVector(int len, float init_value = 0.) // FVector a(3,2) 2 2 2
	{
		size = len;
		fv = new float[size];
		for (int i = 0; i < size; i++)
		{
			fv[i] = init_value;
		}
	}
	
	FVector(FVector & a)
	{
		size = a.size;
		fv = new float[size];
		for (int i = 0; i < size; i++)
		{
			fv[i] = a.fv[i];
		}
	}

	FVector(FVector && a) noexcept
	{
		size = a.size;
		fv = a.fv;
		a.fv=nullptr;
		a.size = 0;
	}

	float len()
	{
		float sum = 0;
		for (int i = 0; i < size; i++)
		{
			sum += fv[i] * fv[i];
		}
		return sqrt(sum);
	}

	float len() const
	{
		float sum = 0;
		for (int i = 0; i < size; i++)
		{
			sum += fv[i]*fv[i];
		}
		return sqrt(sum);
	}

	int getsize()
	{
		return size;
	}

	int getsize() const
	{
		return size;
	}

	FVector & operator=(FVector & a) 
	{
		size = a.size;
		delete[] fv;
		fv = new float[size];
		for (int i = 0; i < size; i++) 
		{
			fv[i] = a.fv[i];
		}
		return *this;
	}

	FVector & operator=(FVector && a) noexcept
	{
		size = a.size;
		delete[] fv;
		fv = new float[size];
		for (int i = 0; i < size; i++)
		{
			fv[i] = a.fv[i];
		}
		return *this;
	}

	FVector & operator+=(const FVector &a)
	{
		if (size == a.size)
		{
			for (int i = 0; i < size; i++)
			{
				fv[i] += a.fv[i];
			}
			return *this;
		}
	}

	FVector & operator-=(const FVector &a)// c-=a; c=c-a;
	{
		if (size == a.size)
		{
			for (int i = 0; i < size; i++)
			{
				fv[i] -= a.fv[i];
			}
			return *this;
		}
	}

	friend FVector & operator-(FVector a, const FVector &b) //c=a-b;
	{
		if (a.size == b.size)
		{
			for (int i = 0; i < a.size; i++)
			{
				a.fv[i] = a.fv[i] - b.fv[i];
			}
			return a;
		}
	}

	FVector & operator-()
	{
		FVector tmp;
		tmp.size = size;
		tmp.fv = new float[size];
		for (int i = 0; i < size; i++)
		{
			tmp.fv[i] = -1*fv[i];
		}
		return tmp;
	}
	
	friend FVector & operator+(FVector a,const FVector &b) //c=a+b
	{
		if (a.size == b.size)
		{
			for (int i = 0; i < a.size; i++)
			{
				a.fv[i] = a.fv[i] + b.fv[i];
			}
			return a;
		}
	}

	FVector & operator+()
	{
		FVector tmp;
		tmp.size = size;
		tmp.fv = new float[size];
		for (int i = 0; i < size; i++)
		{
			tmp.fv[i] = fv[i];
		}
		return tmp;
	}

	FVector & operator*(float l) 
	{
		FVector c(*this);
		for (int i = 0; i < size; i++)
		{
			c.fv[i] *= l;
		}
		return c;
	}

	friend FVector operator*(float l, FVector a)
	{
		FVector c;
		c.size = a.size;
		c.fv = new float[c.size];
		for (int i = 0; i < a.size; i++)
		{
			c.fv[i] = a.fv[i]*l;
		}
		return c;
	}

	float operator*(const FVector &a)
	{
		float scalar=0;
		if (size == a.size)
		{
			for (int i = 0; i < size; i++)
			{
				scalar += fv[i] * a.fv[i];
			}
			return scalar;
		}
	}  

	float & operator[](size_t idx)
	{
		return *(fv + idx);
	}

	const float & operator[](size_t idx) const 
	{
		return *(fv + idx);
	}

	friend ostream & operator<<(ostream & p_Out,const FVector & a)
	{
		for (int i = 0; i < a.size; i++)
		{
			p_Out << a.fv[i] << "  ";
		}
		return p_Out;
	}

	friend istream & operator>>(istream & p_In, const FVector & a)
	{
		for (int i = 0; i < a.size; i++)
		{
			p_In >> a.fv[i];
		}
		return p_In;
	}

	~FVector()
	{
		delete[] fv;
	}
	
};

class FMatrix
{
private:

	int n;//size
	float *aelem;
	int aelem_size;
	int *jptr;
	int *iptr;
	int iptr_size;

public:

	FMatrix()
	{
		n = 0;
		aelem = new float[n];
		jptr = new int[n];
		iptr = new int[n+2];
	}

	FMatrix(int dim, float** Mat)
	{
		n = dim;
		aelem = new float[n*n];
		jptr = new int[n*n];
		iptr = new int[n + 2];
		iptr[0] = 0;
		int k = 0;

		int l = 1;
		int ipptr_buf = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (Mat[i][j] != 0)
				{
					aelem[k] = Mat[i][j];
					jptr[k] = j;
					k++;
				}
			}
			iptr[l] = k;
			l++;
		}
		iptr[l] = k + 1;
		iptr_size = l;
		aelem_size = k;
	}

	FMatrix(const FMatrix & tmp)
	{
		n = tmp.n;
		aelem = new float[tmp.aelem_size];
		jptr = new int[tmp.aelem_size];
		iptr = new int[tmp.iptr_size];
		for (int i = 0; i < tmp.aelem_size; i++)
		{
			aelem[i] = tmp.aelem[i];
			jptr[i] = tmp.jptr[i];
		}
		for (int i = 0; i < tmp.iptr_size; i++)
		{
			iptr[i] = tmp.iptr[i];
		}
	}

	void out()
	{
		cout << "aelem" << endl;
		for (int i = 0; i < aelem_size; i++)
		{
			cout << aelem[i] << " ";
		}
		cout <<endl<<"jptr"<< endl;
		for (int i = 0; i < aelem_size; i++)
		{
			cout << jptr[i] << " ";
		}
		cout << endl << "iptr"<< endl;
		for (int i = 0; i < iptr_size; i++)
		{
			cout << iptr[i] << " ";
		}
	}

	int get_size()
	{
		return n;
	}

	int count_of_non_zero()
	{
		return aelem_size;
	}

	friend FVector operator*(const FMatrix & rv_1, const FVector & a)
	{
		FVector tmp(a.getsize());
		for (int i = 0; i < rv_1.n; i++)
		{
			for (int j = rv_1.iptr[i]; j < rv_1.iptr[i+1]; j++)
			{
				tmp[i] += a[rv_1.jptr[j]] * rv_1.aelem[j];
			}
		}
		return tmp;
	}

	FMatrix & operator*(float l)
	{
		for (int i = 0; i < aelem_size; i++)
		{
			aelem[i] *= l;
		}
		return *this;
	}

	friend FMatrix & operator*(float l, FMatrix & a)
	{
		FMatrix c;
		c = a * l;
		return c;
	}

	void fill(int size, float** tmp)
	{
		n = size;
		aelem = new float[n*n];
		jptr = new int[n*n];
		iptr = new int[n + 2];
		iptr[0] = 0;
		int k = 0;

		int l = 1;
		int ipptr_buf = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (tmp[i][j] != 0)
				{
					aelem[k] = tmp[i][j];
					jptr[k] = j;
					k++;
				}
			}
			iptr[l] = k;
			l++;
		}
		iptr[l] = k + 1;
		iptr_size = l;
		aelem_size = k;
	}

	friend ostream & operator<<(ostream & p_Out, const FMatrix &a)
	{
		int k = 0;
		for (int i = 0; i < a.n; i++)
		{
			for (int j = 0; j < a.n; j++)
			{
				if (j == a.jptr[k])
				{
					p_Out << setw(3) << a.aelem[k];
					k++;
				}
				else
				{
					p_Out << setw(3) << 0;
				}
			}
			p_Out << endl;
		}
		p_Out << endl;
		int i = 0;
		p_Out << "aelem : {";
		for (i = 0; i < a.aelem_size-1; i++)
		{
			p_Out << a.aelem[i] << "; ";
		}
		p_Out << a.aelem[i] << "}" << endl;
		p_Out << "jptr : {" ;
		for ( i = 0; i < a.aelem_size-1; i++)
		{
			p_Out << a.jptr[i] << "; ";
		}
		p_Out << a.jptr[i] << "}" << endl;
		p_Out << "iptr: {" ;
		for ( i = 0; i < a.iptr_size-1; i++)
		{
			p_Out << a.iptr[i] << "; ";
		}
		p_Out << a.iptr[i] << "}" << endl;
		return p_Out;
	}

	friend istream & operator>>(istream & p_In, FMatrix & a) //ifstream f(""); f>>a;
	{
		int size;
		p_In >> size;
		float **tmp = new float *[size];
		for (int i = 0; i < size; i++)
		{
			tmp[i] = new float[size];
			for (int j = 0; j < size; j++)
			{
				p_In >> tmp[i][j];
			}
		}
		a.fill(size,tmp);
		return p_In;
	}

	~FMatrix()
	{
		delete[] aelem;
		delete[] jptr;
		delete[] iptr;
	}
};

int main() 
{
	setlocale(0, "");
	srand(time(NULL));

	FVector vec1(2,1);
	cout <<"vec1:	" << vec1 << endl;;
	FMatrix mat1;
	ifstream ftr("abhaziya.txt",ios_base::beg);
	ftr >> mat1;
	cout <<"mat1:\n"<< mat1;
	FVector res;
	res = (mat1*10*vec1);
	cout << "res:\n" << res << endl;
	system("pause");
}