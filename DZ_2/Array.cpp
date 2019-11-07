#include "Array.h"

Array::Array()
{
	Arr = nullptr;
	amount_of_elems = 0;
}

Array::Array(int size, unsigned char init_val = '0')
{
	amount_of_elems = size;
	Arr = new unsigned char[size];
	for (int i = 0; i < size; i++)
	{
		Arr[i] = init_val;
	}
}

Array::Array(int size, unsigned char * init_arr)
{
	amount_of_elems = size;
	Arr = new unsigned char[amount_of_elems];
	for (int i = 0; i < size; i++)
	{
		Arr[i] = init_arr[i];
	}
}

Array::Array(const Array & to_copy)
{
	Arr = new unsigned char[to_copy.amount_of_elems];
	amount_of_elems = to_copy.amount_of_elems;
	for (int i = 0; i < amount_of_elems; i++)
	{
		Arr[i] = to_copy.Arr[i];
	}
}

Array::Array(Array && to_move)
{
	Arr = to_move.Arr;
	amount_of_elems = to_move.amount_of_elems;
	to_move.Arr = nullptr;
};

int * Array::conversion_to_int(int * dest)
{
	for (int i = 0; i < amount_of_elems; i++)
	{
		dest[i] = Arr[i] - '0';
	}
	return dest;
}

int * Array::conversion_to_int(int * dest) const
{
	//delete[] dest;
	//dest = new int[amount_of_elems];

	for (int i = 0; i < amount_of_elems; i++)
	{
		dest[i] = Arr[i]-'0';
	}
	return dest;
}

unsigned char * Array::conversion_to_unch(int * source, unsigned char * dest, int amnt)
{
	for (int i = 0; i < amnt; i++)
	{
		dest[i] = source[i] + '0';
	}
	return dest;
} 

Array & Array::addition( Array & rv_1, Array & rv_2)
{
	int * int_rv1 = new int[rv_1.amount_of_elems];
	rv_1.conversion_to_int(int_rv1);
	int * int_rv2 = new int[rv_2.amount_of_elems];
	rv_2.conversion_to_int(int_rv2);

	int max_size;
	max_size = ((rv_1.amount_of_elems < rv_2.amount_of_elems) ? rv_2.amount_of_elems : rv_1.amount_of_elems) + 1;
	int * int_res_arr = new int[max_size];
	for (int i = 0; i < max_size; i++)
	{
		int_res_arr[i] = 0;
	}

	for (int i = 0; i < max_size - 1; i++)
	{
		if (i < rv_1.amount_of_elems)
		{
			int_res_arr[i + 1] += int_rv1[i];
		}
		if (i < rv_2.amount_of_elems)
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

unsigned char Array::operator[](int id)
{
	return *(Arr + id);
}

unsigned char Array::operator[](int id) const
{
	return *(Arr + id);
}

std::ostream & operator<<(std::ostream & p_Out, const Array & show)
{
	for (int i = 0; i < show.amount_of_elems; i++)
	{
		p_Out << show[i];
	}
	return p_Out;
}

Array::~Array()
{
	delete Arr;
}