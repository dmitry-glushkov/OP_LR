#include "FVector.h"

FVector::FVector() // FVector a;
{
	size = 1;
	fv = new float[size];
}

FVector::	 FVector(int len, float init_value = 0.) // FVector a(3,2) 2 2 2
{
	size = len;
	fv = new float[size];
	for (int i = 0; i < size; i++)
	{
		fv[i] = init_value;
	}
}

FVector::FVector(FVector & a)
{
	size = a.size;
	fv = new float[size];
	for (int i = 0; i < size; i++)
	{
		fv[i] = a.fv[i];
	}
}

FVector::FVector(FVector && a) noexcept//c=a+b+g
{
	size = a.size;
	fv = new float[size];
	for (int i = 0; i < size; i++)
	{
		fv[i] = a.fv[i];
	}
}

FVector::  float len()
{
	float sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += fv[i] * fv[i];
	}
	return sqrt(sum);
}

FVector::	float len() const
{
	float sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += fv[i] * fv[i];
	}
	return sqrt(sum);
}

FVector::	int getsize()
{
	return size;
}

FVector::	int getsize() const
{
	return size;
}

FVector::FVector & operator=(FVector & a)
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

FVector::FVector & operator=(FVector && a) noexcept
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

FVector::FVector & operator+=(const FVector &a)
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

FVector::FVector & operator-=(const FVector &a)// c-=a; c=c-a;
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

FVector::	FVector & operator-(FVector a, const FVector &b) //c=a-b;
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

FVector::FVector & operator-()
{
	FVector tmp;
	tmp.size = size;
	tmp.fv = new float[size];
	for (int i = 0; i < size; i++)
	{
		tmp.fv[i] = -1 * fv[i];
	}
	return tmp;
}

FVector::	friend FVector & operator+(FVector a, const FVector &b) //c=a+b
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

FVector::FVector & operator+()
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

FVector::FVector & operator*(float l)
{
	FVector c(*this);
	for (int i = 0; i < size; i++)
	{
		c.fv[i] *= l;
	}
	return c;
}

FVector::	friend FVector operator*(float l, FVector a)
{
	FVector c;
	c.size = a.size;
	c.fv = new float[c.size];
	for (int i = 0; i < a.size; i++)
	{
		c.fv[i] = a.fv[i] * l;
	}
	return c;
}

FVector::	float operator*(const FVector &a)
{
	float scalar = 0;
	if (size == a.size)
	{
		for (int i = 0; i < size; i++)
		{
			scalar += fv[i] * a.fv[i];
		}
		return scalar;
	}
}

FVector::	float & operator[](size_t idx)
{
	return *(fv + idx);
}

FVector::const float & operator[](size_t idx) const
{
	return *(fv + idx);
}

FVector::friend ostream & operator<<(ostream & p_Out, const FVector & a)
{
	for (int i = 0; i < a.size; i++)
	{
		p_Out << a.fv[i] << "  ";
	}
	return p_Out;
}

FVector::friend istream & operator>>(istream & p_In, const FVector & a)
{
	for (int i = 0; i < a.size; i++)
	{
		p_In >> a.fv[i];
	}
	return p_In;
}

FVector::~FVector()
{
	delete[] fv;
}

};