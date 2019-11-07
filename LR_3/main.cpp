#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include "Vector.h"
#include "Algorithm.h"
using namespace std;

struct Student
{
	unsigned id;
	string group;
	double av_mark;
	string surname;
	friend ostream & operator<<(ostream & p_Out, const Student & rv)
	{
		p_Out << setw(3) << rv.id << " |";
		p_Out << setw(7) << rv.group << " |";
		p_Out << setw(15) << rv.av_mark << " |";
		p_Out << setw(8) << rv.surname ;
		p_Out << endl;
		return p_Out;
	}
};

string grp;

int main()
{
	setlocale(0, "");
	bool fl = 1;
	//������:
	vector<Student> students_tmp;
	int count = 1;
	while (fl)
	{
		cout << count << " �������:\n";
		Student tmp;	
		cout << "������� id:	";
		cin >> tmp.id;
		cout << "������� ������:	";
		cin >> tmp.group;
		cout << "������� ������� ������:	";
		cin >> tmp.av_mark;
		cout << "������� �������:	";
		cin >> tmp.surname;
		students_tmp.push_back(tmp);
		count++;
		cout << "���������� ����? ( 1-�� 0-��� )	";
		cin >> fl;
		system("cls");
	}
	Vector<Student> students(students_tmp.begin(), students_tmp.end());
	auto iter_beg = students.Begin();
	auto iter_end = students.End();
	cout << "�������������� ������ ���������:\n";
	cout << " id | ������ | ������� ������ | �������" << endl;
	ForEach(iter_beg, iter_end, [](Student to_print)
	{
		cout << to_print;
	});
	ofstream out("students.txt");
	CopyIf(iter_beg, iter_end, oIterator<Student>(out), [](const Student & check) ->bool
	{
		return 1;
	});
	cout << "\n������� ������ ��� ������:	";
	cin >> grp;
	auto first_student = FindIf(iter_beg, iter_end, [](Student check)
	{	
		if (check.group == grp) return 1;
		return 0;
	});

	cout << "������� ����� ������ ��� ������� ���������� ��������"<<"(Surname: "<<first_student->surname<<"):	";
	cin >> first_student->av_mark;
	
	int capacity = students.Size();
	Vector<Student> new_students(students.Size());
	Vector<Student>::iterator dest = new_students.Begin();
	auto it = CopyIf(iter_beg, iter_end, dest, [](Student check)
	{
		if (check.group == grp) return 1;
		return 0;
	});
	iter_beg = new_students.Begin();
	new_students.Resize(it - iter_beg);
	iter_beg = new_students.Begin();
	iter_end = new_students.End();
	cout << "\n��������������� �� ������ ������ ��������� ��� ������ " << grp << ":\n";
	cout << " id | ������ | ������� ������ | �������" << endl;
	Sort(iter_beg, iter_end, [](Student left, Student right)
	{
		return (left.av_mark > right.av_mark);
	});
	ForEach(iter_beg, iter_end, [](Student to_print)
	{
		cout << to_print;
	});


	system("pause");
}