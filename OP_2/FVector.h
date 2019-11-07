#pragma once
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

	FVector(); // FVector a;


	explicit FVector(int len, float init_value = 0.); // FVector a(3,2) 2 2 2

	FVector(FVector & a);


	FVector(FVector && a) noexcept;//c=a+b+g


	float len();


	float len() const;

	int getsize();

	int getsize() const;


	FVector & operator=(FVector & a);
	FVector & operator=(FVector && a) noexcept;


	FVector & operator+=(const FVector &a);


	FVector & operator-=(const FVector &a);// c-=a; c=c-a;


	friend FVector & operator-(FVector a, const FVector &b); //c=a-b;
	

	FVector & operator-();


	friend FVector & operator+(FVector a, const FVector &b); //c=a+b

	FVector & operator+();


	FVector & operator*(float l);


	friend FVector operator*(float l, FVector a);


	float operator*(const FVector &a);


	float & operator[](size_t idx);
	const float & operator[](size_t idx) const;
	friend ostream & operator<<(ostream & p_Out, const FVector & a);

	friend istream & operator>>(istream & p_In, const FVector & a);


	~FVector();

};
