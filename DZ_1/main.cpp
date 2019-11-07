#include <iostream>
#include <iomanip>
using namespace std;

short prec = 100;//precision

class Fraction
{
private:

	short sign;
	unsigned long int_part;
	unsigned short dec_part;

public:

	explicit Fraction(double val = 0.)
	{
		if (val >= 0)
		{
			sign = 1;
			int_part = val;
			dec_part = (val - int_part) * prec;
		}
		else
		{
			sign = -1;
			int_part = sign * val;
			dec_part = (sign * val - int_part) * prec;
		}
	}

	Fraction(Fraction & copy)
	{
		sign = copy.sign;
		int_part = copy.int_part;
		dec_part = copy.dec_part;
	}

	Fraction(const Fraction & copy)
	{
		sign = copy.sign;
		int_part = copy.int_part;
		dec_part = copy.dec_part;
	}

	Fraction(Fraction && move) noexcept
	{
		sign = move.sign;
		int_part = move.int_part;
		dec_part = move.dec_part;
		move.sign = 0;
		move.int_part = 0;
		move.dec_part = 0;
	}

	friend Fraction operator+(Fraction rv_1, const Fraction & rv_2)
	{
		if (rv_1.sign == rv_2.sign)
		{
			rv_1.int_part += rv_2.int_part;
			rv_1.dec_part += rv_2.dec_part;
			if (rv_1.dec_part >= prec)
			{
				rv_1.int_part += 1;
				rv_1.dec_part -= prec;
			}
			return rv_1;
		}
		else
			return operator-(rv_1, rv_2);
	}

	friend Fraction operator-(Fraction rv_1, const Fraction & rv_2)
	{
		if (rv_1.sign == rv_2.sign)
		{
			if ((rv_1.int_part > rv_2.int_part) || ((rv_1.int_part == rv_2.int_part) && (rv_1.dec_part >= rv_2.dec_part)))
			{
				rv_1.int_part -= rv_2.int_part;
				if (rv_1.dec_part >= rv_2.dec_part)
				{
					rv_1.dec_part -= rv_2.dec_part;
				}
				else
				{
					rv_1.int_part -= 1;
					rv_1.dec_part += prec;
					rv_1.dec_part -= rv_2.dec_part;
				}
			}
			else
			{
				rv_1 = rv_2 - rv_1;
				rv_1.sign *= -1;
			}
			return rv_1;
		}
		else
			return operator+(rv_1, rv_2);
	}

	friend Fraction operator*(Fraction rv_1, const Fraction & rv_2)
	{
		if ((rv_1.sign == rv_2.sign == -1) || (rv_1.sign == 1 && rv_2.sign == -1))
		{
			rv_1.sign *= -1;
		}

		rv_1.int_part *= rv_2.int_part;
		rv_1.dec_part *= rv_2.dec_part;
		rv_1.dec_part /= prec;

		return rv_1;
	}

	friend Fraction operator/(Fraction rv_1, const Fraction & rv_2)
	{

		if ((rv_1.sign == rv_2.sign == -1) || (rv_1.sign == 1 && rv_2.sign == -1))
		{
			rv_1.sign *= -1;
		}

		unsigned long tmp_1 = rv_1.int_part*prec + rv_1.dec_part;
		unsigned long tmp_2 = rv_2.int_part*prec + rv_2.dec_part;
		if (tmp_2 == 0)
		{
			cout << "Деление на ноль.\n";
			return rv_1;
		}
		tmp_1 = (double)tmp_1 / (double)tmp_2 * prec;
		rv_1.int_part = tmp_1 / prec;
		rv_1.dec_part = tmp_1 % prec;

		return rv_1;
	}

	Fraction & operator=(const Fraction & equals)
	{
		sign = equals.sign;
		int_part = equals.int_part;
		dec_part = equals.dec_part;
		return *this;
	}

	bool operator>(const Fraction & compared)
	{
		if (sign > compared.sign || int_part > compared.int_part || (int_part == compared.int_part && dec_part > compared.dec_part))
			return 1;
		else
			return 0;
	}

	bool operator<(const Fraction & compared)
	{
		if (sign < compared.sign || int_part < compared.int_part || (int_part == compared.int_part && dec_part < compared.dec_part))
			return 1;
		else
			return 0;
	}

	bool operator==(const Fraction & compared)
	{
		if (sign == compared.sign && int_part == compared.int_part && dec_part == compared.dec_part)
			return 1;
		else
			return 0;
	}

	bool operator!=(const Fraction & compared)
	{
		if (sign != compared.sign || int_part != compared.int_part || dec_part != compared.dec_part)
			return 1;
		else
			return 0;
	}

	friend ostream & operator<<(ostream & p_Out, const Fraction & note)
	{
		if (note.sign == -1)
		{
			p_Out << "-";
		}
		p_Out << note.int_part << ".";

		for (int i = prec / 10; i >= 1; i = i / 10)
		{
			p_Out << (note.dec_part / i) % 10;
		}
		return p_Out;
	}

	friend istream & operator>>(istream & p_In, Fraction & note)
	{
		double val;
		p_In >> val;
		if (val >= 0)
		{
			note.sign = 1;
			note.int_part = val;
			note.dec_part = (val - note.int_part) * prec;
		}
		else
		{
			note.sign = -1;
			note.int_part = note.sign * val;
			note.dec_part = (note.sign * val - note.int_part) * prec;
		}
		return p_In;
	}

	void Show()
	{
		cout << sign << endl;
		cout << int_part << endl;
		cout << dec_part << endl;
	}

	~Fraction()
	{

	}

};

class Calculator
{

public:

	Calculator()
	{

	}

	void Run()
	{
		short option;
		cout << "Выберите дейстиве:\n";
		cout << "1 - сложение.\n";
		cout << "2 - вычитание.\n";
		cout << "3 - умножение.\n";
		cout << "4 - деление.\n";
		cin >> option;
		system("cls");
		switch (option)
		{
		case 1:
		{
			Fraction res, rv_1, rv_2;
			cout << "Введите значение 1 элемента:	";
			cin >> rv_1;
			cout << "Введите значение 2 элемента:	";
			cin >> rv_2;
			res = rv_1 + rv_2;
			cout << rv_1 << " + " << rv_2 << " = " << res << endl;
			break;
		}
		case 2:
		{
			Fraction res, rv_1, rv_2;
			cout << "Введите значение 1 элемента:	";
			cin >> rv_1;
			cout << "Введите значение 2 элемента:	";
			cin >> rv_2;
			res = rv_1 - rv_2;
			cout << rv_1 << " - " << rv_2 << " = " << res << endl;
			break;
		}
		case 3:
		{
			Fraction res, rv_1, rv_2;
			cout << "Введите значение 1 элемента:	";
			cin >> rv_1;
			cout << "Введите значение 2 элемента:	";
			cin >> rv_2;
			res = rv_1 * rv_2;
			cout << rv_1 << " * " << rv_2 << " = " << res << endl;
			break;
		}
		case 4:
		{

			Fraction res, rv_1, rv_2;
			cout << "Введите значение 1 элемента:	";
			cin >> rv_1;
			cout << "Введите значение 2 элемента:	";
			cin >> rv_2;
			res = rv_1 / rv_2;
			cout << rv_1 << " / " << rv_2 << " = " << res << endl;
			break;
		}
		}
	}

	~Calculator()
	{

	}


};

int main()
{
	setlocale(0, "");

	Calculator app;
	app.Run();

	system("pause");
}