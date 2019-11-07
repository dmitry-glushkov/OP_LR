#ifndef ARRAY_H
#define ARRAY_H

#include <ostream>

class Array
{
protected:

	unsigned char * Arr;
	int amount_of_elems;

public:

	Array();

	Array(int, unsigned char);

	Array(int, unsigned char *);

	Array(const Array &);

	Array(Array &&);

	int * conversion_to_int(int * );

	int * conversion_to_int(int * ) const;

	unsigned char * conversion_to_unch(int *, unsigned char *, int);

	virtual Array & addition( Array & , Array & );

	unsigned char operator[](int);

	unsigned char operator[](int) const;

	friend std::ostream & operator<<(std::ostream & , const Array & );

	~Array();
};

#endif ARRAY_H