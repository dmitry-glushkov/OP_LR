#include <iostream>
#include <iomanip>
using namespace std;

class Curency 
{
private:
	float money;
public:
	Curency() {
		money = 0;
	}
	Curency(float val) {
		money = val;
	}
	float get_money() const {
		return money;
	}
	void set_money(float val) {
		money = val;
	}

	virtual float AmtToRub() const = 0;
	virtual void Show() const = 0;
	virtual ~Curency() = 0 { };
};
class Dollar : public Curency 
{
public:
		Dollar() : Curency() {};
		Dollar(float val) : Curency(val) {};
		float AmtToRub() const {
			float sum = get_money()*62.71;
			return sum;
		} 
		void Show() const {
			cout <<fixed<<setprecision(2)<< get_money()<<"$"<<endl;
		} 
};
class Euro : public Curency
{
public:
	Euro() : Curency() {};
	Euro(float val) : Curency(val) {};
	float AmtToRub() const {
		float sum = get_money()*75.46;
		return sum;
	}
	void Show() const {
		cout << fixed << setprecision(2) << get_money() << "eur"<<endl;
	}
};
class App {
private:
	int i;
public:
	App() {	}
	void Run() {
		while (i != 0) {
			cout << "Create Euro account: 1" << endl;
			cout << "Create Dollar account: 2" << endl;
			cout << "Finish : 0" << endl;
			cin >> i;
			system("cls");
			switch (i) {
			case 1: {
				float n;
				cout << "Input deposit: ";
				cin >> n;
				cin.ignore(1, '\n');
				Euro a(n);
				Curency *pBase = &a;
				while (i != 0) {
					cout << "Output deposit: 1" << endl;
					cout << "Output Ruble equivalent: 2" << endl;
					cout << "Finish work with Euro account: 0" << endl;
					cin >> i;
					system("cls");
					switch (i) {
					case 1: {
						pBase->Show();
						break;
					}
					case 2: {
						cout << pBase->AmtToRub() << "rub" << endl;
						break;
					}
					case 0: break;
					default: {
						cout << "Wrong number." << endl;
						break;
					}

					}
				}
				break;
			}
			case 2: {
				float n;
				cout << "Input deposit: ";
				cin >> n;
				Dollar a(n);
				Curency *pBase = &a;
				while (i != 0) {
					cout << "Output deposit: 1" << endl;
					cout << "Output Ruble equivalent: 2" << endl;
					cout << "Finish work with Dollar account: 0" << endl;
					cin >> i;
					system("cls");
					switch (i) {
					case 1: {
						pBase->Show();
						break;
					}
					case 2: {
						cout << pBase->AmtToRub() << "rub" << endl;
						break;
					}
					case 0: break;
					default: {
						cout << "Wrong number." << endl;
						break;
					}
					}
				}
				break;
			}
			case 0: break;
			default: {
				cout << "Wrong number." << endl;
			}
			}
			}
		}
};

int main() {
	App a;
	a.Run();
}