#include <iostream>
#include <iomanip>
#include "Array.h"
#include "BitString.h"
#include "Money.h"

using namespace std;
const int Max = 100;


int main()
{
	BitString test(3, '1');
	BitString testSum(3, '1');
	Array testA(3, '2');
	BitString res;
	res.addition(test, testSum);
	Array * pB = &test;
	Array * pB1 = new BitString;
	pB1->addition(test, testSum);
	cout << *pB1;
	cout << endl;
	cout << dynamic_cast<Array&>(res);
	cout << endl;
	delete pB1;
	system("pause");
}