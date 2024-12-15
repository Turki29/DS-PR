//#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "student.h"
#include "LinkedList.h"
using namespace std;

enum enStudentOps {
	StudentOps_ShowStudents = 1,
	StudentOps_ShowStudent,
	StudentOps_AddStudent,
	StudentOps_EditStudent,
	StudentOps_RemoveStudent,
	StudentOps_Exit
};

class StudentManager
{

private:


	clsLinkedList<Student> _linkedList;
	string _filename = "students.txt";

	bool _fReadStudents()
	{
		// نفتح الملف للقراءة
		fstream file(_filename, ios::in);

		if (!file) {
			cout << "File could not be opened!\n";
			return false;
		}

		// هنا نقوم بقراءة الطلاب من الملف
		while (!file.eof())
		{



			Student student;
			file >> student.id;
			file.ignore(2); // Ignore the double delimiter (##)

			// Read the rest of the fields
			getline(file, student.firstname, '#');
			file.ignore(); // Ignore the second '#'

			if (student.firstname.length() == 0)
			{
				break;
			}

			getline(file, student.lastname, '#');
			file.ignore();

			getline(file, student.major, '#');
			file.ignore();

			getline(file, student.email, '#');
			file.ignore();

			getline(file, student.phone, '#');
			file.ignore();

			file >> student.GPA;
			file.ignore(2); // Ignore '##' after GPA

			getline(file, student.level, '#');
			file.ignore(); // Ignore the second '#'
			_linkedList.AddNode(student);
			
		}

		file.close(); // نغلق الملف
		return true;
	}

public:


	// منشئ الكلاس
	StudentManager(string filename)
	{
		_filename = filename;
		_fReadStudents();
	}

	// يضيف الطالب للملف
	bool fAddStudent(Student student)
	{
		// نفتح الملف للإلحاق
		fstream file(_filename, ios::out | ios::app);

		if (!file) {
			cout << "File could not be opened!\n";
			return false;
		}

		// هنا نضيف الطالب للملف
		file << student.id << "##" << student.firstname << "##" << student.lastname << "##" << student.major << "##" << student.email << "##" << student.phone << "##" << student.GPA << "##" << student.level << "##" << '\n';




		file.close(); // نغلق الملف
	}

	// يضيف الطالب للملف
	bool fAddAllStudents()
	{
		// نفتح الملف للإلحاق
		fstream file(_filename, ios::out);

		if (!file) {
			cout << "File could not be opened!\n";
			return false;
		}

		// هنا نضيف الطالب للملف
		clsNode<Student>* temp = _linkedList.head;
		while (temp != nullptr)
		{
			Student student = temp->data;
			file << student.id << "##" << student.firstname << "##" << student.lastname << "##" << student.major << "##" << student.email << "##" << student.phone << "##" << student.GPA << "##" << student.level << "##" << '\n';
			temp = temp->next;
		}




		file.close(); // نغلق الملف
	}

	// تضيف الطالب في القوائم المترابطة والملف
	void AddStudent()
	{
		Student student;
		cout << "Enter Student ID: ";
		cin >> student.id;
		cin.ignore();
		cout << "Enter Student First Name: ";
		getline(cin, student.firstname);
		cout << "Enter Student Last Name: ";
		getline(cin, student.lastname);
		cout << "Enter Student Email: ";
		getline(cin, student.email);
		cout << "Enter Student Phone: ";
		cin >> student.phone;
		cin.ignore();
		cout << "Enter Student Major: ";
		getline(cin, student.major);
		cout << "Enter Student Level: ";
		cin >> student.level;
		cout << "Enter Student GPA: ";
		cin >> student.GPA;


		fAddStudent(student);
		_linkedList.AddNode(student);

	}
	

	// يعدّل الطالب في القوائم المترابطة
	bool EditStudent()
	{
		cout << "Enter Student ID: ";
		int id;
		cin >> id;
		cin.ignore();
		Student student = _linkedList.Search(id);
		if (student.firstname.empty())
		{
			cout << "Student not found" << endl;
			return false;
		}

		student.PrintStudentInfo();


		cout << "Are you sure you want to Edit this student? (Y/N): ";
		char confirm;
		cin >> confirm;
		if (confirm == 'N' || confirm == 'n')
		{
			
			return false;
		}
		cin.ignore();
		cout << "Enter Student First Name: ";
		getline(cin, student.firstname);
		cout << "Enter Student Last Name: ";
		getline(cin, student.lastname);
		cout << "Enter Student Email: ";
		getline(cin, student.email);
		cout << "Enter Student Phone: ";
		cin >> student.phone;
		cin.ignore();
		cout << "Enter Student Major: ";
		getline(cin, student.major);
		cout << "Enter Student Level: ";
		cin >> student.level;
		cout << "Enter Student GPA: ";
		cin >> student.GPA;

		
		_linkedList.Update(student);
		return true;
	}

	// يطبع الطلاب كلهم
	void PrintStudents()
	{
		_linkedList.Traverse();
	}

	// يطبع طالب معين 
	void PrintStudent()
	{
		cout << "Enter Student ID: ";
		int id;
		cin >> id;
		Student student = _linkedList.Search(id);
		if (student.firstname == "")
		{
			cout << "Student not found" << endl;
		}
		else
		{
			student.PrintStudentInfo();
		}
	}

	// يحذف طالب
	bool RemoveStudent()
	{
		cout << "Enter Student ID: ";
		int id;
		cin >> id;
		Student student = _linkedList.Search(id);
		if (student.firstname.empty())
		{
			cout << "Student not found" << endl;
			return false;
		}

		cin.ignore();

		student.PrintStudentInfo();
		cout << "Are you sure you want to delete this student? (Y/N): ";
		char confirm;
		cin >> confirm;
		if (confirm == 'Y' || confirm == 'y')
		{
			_linkedList.DeleteById(student.id);
			return true;
		}

		return false;
	}

	// القائمة الرئيسة
	int Prompt()
	{

		int promptResult;

		cout << "1. Show Students" << endl;
		cout << "2. Search Student" << endl;
		cout << "3. Add Student" << endl;
		cout << "4. Edit Student" << endl;
		cout << "5. Remove Student" << endl;
		cout << "6. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> promptResult;

		return promptResult;

	}

	// منظم الأوامر
	void ActionResult(int promptResult)
	{

		switch (promptResult)
		{

		case enStudentOps::StudentOps_ShowStudents:
		{
			PrintStudents();
			break;
		}

		case enStudentOps::StudentOps_ShowStudent:
		{

			PrintStudent();

			break;
		}


		case enStudentOps::StudentOps_AddStudent:
		{
			AddStudent();
			break;
		}

		case enStudentOps::StudentOps_EditStudent:
		{
			EditStudent();


			break;
		}

		case enStudentOps::StudentOps_RemoveStudent:
		{
			RemoveStudent();

			break;
		}


		case enStudentOps::StudentOps_Exit:
		{
			fAddAllStudents();
			exit(0);
			break;
		}


		default:
			break;
		}


	}

	// يشغل البرنامج
	void Run()
	{
		int promptResult;
		while (1)
		{
			promptResult = Prompt();
			ActionResult(promptResult);
			system("pause");
			system("cls");

		}
	}

	~StudentManager()
	{
		fAddAllStudents();
		
		while (_linkedList.head != nullptr)
		{
			clsNode<Student>* next = _linkedList.head->next;
			delete _linkedList.head;
			_linkedList.head = next;
		}
	}
};

int main()
{
    
	StudentManager studentManager("students.txt");
	
	
	studentManager.Run();



	return 0;



}

