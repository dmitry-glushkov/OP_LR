#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include "FVector.h"
using namespace std;
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

	FMatrix();

	FMatrix(int dim, float** Mat);
	

	FMatrix(const FMatrix & tmp);
	

	void out();
	

	int get_size();


	int count_of_non_zero();


	friend FVector operator*(const FMatrix & rv_1, const FVector & a);


	FMatrix & operator*(float l);


	friend FMatrix & operator*(float l, FMatrix & a);
	
	void fill(int size, float** tmp);
	

	friend ostream & operator<<(ostream & p_Out, const FMatrix &a);
	

	friend istream & operator>>(istream & p_In, FMatrix & a); //ifstream f(""); f>>a;
	

	~FMatrix();
	
};