#include "Money.h"

Money::Money() : Array()
{

}

Money::Money(int size, unsigned char init_val = '0') : Array(size, init_val)
{

}

Money::Money(int size, unsigned char * init_arr) : Array(size, init_arr)
{

}

Money::Money(const Money & to_copy) : Array(to_copy)
{

}

Money::Money(Money && to_move) : Array(to_move)
{

}

Array & Money::addition(Array & rv_1, Array & rv_2)
{
	Money & rv_1_tmp = dynamic_cast<Money&>(rv_1);
	Money & rv_2_tmp = dynamic_cast<Money&>(rv_2);
	int * int_rv1 = new int[rv_1_tmp.amount_of_elems];
	rv_1.conversion_to_int(int_rv1);
	int * int_rv2 = new int[rv_2_tmp.amount_of_elems];
	rv_2.conversion_to_int(int_rv2);

	int max_size;
	max_size = ((rv_1_tmp.amount_of_elems < rv_2_tmp.amount_of_elems) ? rv_2_tmp.amount_of_elems : rv_1_tmp.amount_of_elems) + 1;
	int * int_res_arr = new int[max_size];
	for (int i = 0; i < max_size; i++)
	{
		int_res_arr[i] = 0;
	}

	for (int i = 0; i < max_size - 1; i++)
	{
		if (i < rv_1_tmp.amount_of_elems)
		{
			int_res_arr[i + 1] += int_rv1[i];
		}
		if (i < rv_2_tmp.amount_of_elems)
		{
			int_res_arr[i + 1] += int_rv2[i];
		}
	}

	for (int i = max_size - 1; i > 0; i--)
	{
		if (int_res_arr[i] > 9)
		{
			int_res_arr[i] = int_res_arr[i] % 10;
			int_res_arr[i - 1] += 1;
		}
	}

	if (int_res_arr[0] == 0)
	{
		max_size--;
	}

	unsigned char * _res_arr = new unsigned char[max_size];
	conversion_to_unch(int_res_arr, _res_arr, max_size);

	Arr = new unsigned char[max_size];
	amount_of_elems = max_size;
	for (int i = 0; i < amount_of_elems; i++)
	{
		Arr[i] = _res_arr[i];
	}

	delete[] int_rv1;
	delete[] int_rv2;
	delete[] int_res_arr;

	return *this;
}