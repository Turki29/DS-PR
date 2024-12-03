#pragma once
#include <iostream>
using namespace std;

class Student
{

public:
	
	int id;
	string firstname;
	string lastname;
	string email;
	string phone;
	string major;
	string level;
	double GPA;



	void PrintStudentInfo()
	{
		cout << "Student ID         : " << id << endl;
		cout << "Student First Name : " << firstname << endl;
		cout << "Student Last Name  : " << lastname << endl;
		cout << "Student Email      : " << email << endl;
		cout << "Student Phone      : " << phone << endl;
		cout << "Student Major      : " << major << endl;
		cout << "Student Level      : " << level << endl;
		cout << "Student GPA        : " << GPA << endl;
		cout << "--------------------------------" << endl;
	}

};