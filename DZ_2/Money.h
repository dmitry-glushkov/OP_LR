#ifndef MONEY_H
#define MONEY_H

#include "Array.h"

class Money : public Array
{
public:

	Money();

	Money(int, unsigned char);

	Money(int, unsigned char *);

	Money(const Money &);

	Money(Money &&);

	Array & addition(Array &, Array &) override;

};

#endif MONEY_H