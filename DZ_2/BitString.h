#ifndef BITSTRING_H
#define BITSTRING_H

#include "Array.h"

class BitString : public Array
{
public:

	BitString();

	BitString(int, unsigned char);

	BitString(int, unsigned char *);

	BitString(const BitString &);

	BitString(BitString &&);

	Array & addition( Array &, Array &) override;

};

#endif BITSTRING_H