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


bool fAddStudent(Student student )
{
	// نفتح الملف للإلحاق
    fstream file("students.txt", ios::out | ios::app); 

    if (!file) {
        cout << "File could not be opened!\n";
        return false;
    }

    // هنا نضيف الطالب للملف
    file << student.id << "##" << student.firstname<< "##" << student.lastname<< "##" << student.major<< "##" << student.email << "##" << student.phone << "##" << student.GPA << "##" << student.level << "##" << '\n';

    

    
    file.close(); // نغلق الملف
}

bool fReadStudents(clsLinkedList<Student> &linkedList)
{
	// نفتح الملف للقراءة
	fstream file("students.txt", ios::in);

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
		linkedList.AddNode(student);
		//student.PrintStudentInfo();
	}

	file.close(); // نغلق الملف
}

bool AddAllStudents(clsLinkedList<Student> &linkedList)
{
	// نفتح الملف للإلحاق
	fstream file("students.txt", ios::out );

	if (!file) {
		cout << "File could not be opened!\n";
		return false;
	}

	// هنا نضيف الطالب للملف
	clsNode<Student>* temp = linkedList.head;
	while(temp != nullptr)
	{
		Student student = temp->data;
		file << student.id << "##" << student.firstname << "##" << student.lastname << "##" << student.major << "##" << student.email << "##" << student.phone << "##" << student.GPA << "##" << student.level << "##" << '\n';
		temp = temp->next;
	}




	file.close(); // نغلق الملف
}

void AddStudent(clsLinkedList<Student> &linkedList)
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
	linkedList.AddNode(student);

}


int Prompt()
{

	int promptResult;

	cout << "1. Show Students" << endl;
	cout << "2. Show Student" << endl;
	cout << "3. Add Student" << endl;
	cout << "4. Edit Student" << endl;
	cout << "5. Remove Student" << endl;
	cout << "6. Exit" << endl;
	cout << "Enter your choice: ";
	cin >> promptResult;

	return promptResult; 

}

void ActionResult(int promptResult, clsLinkedList<Student> &linkedList)
{

	switch (promptResult)
	{

	case enStudentOps::StudentOps_ShowStudents:
	{
		linkedList.Traverse();
		break;
	}

	case enStudentOps::StudentOps_ShowStudent:
	{
	
		cout << "Enter Student ID: ";
		int id;
		cin >> id;
		Student student = linkedList.Search(id);
		if (student.firstname == "")
		{
			cout << "Student not found" << endl;
		}
		else
		{
			student.PrintStudentInfo();
		}

		break;
	}


	case enStudentOps::StudentOps_AddStudent:
	{
		AddStudent(linkedList);
		break;
	}

	case enStudentOps::StudentOps_EditStudent:
	{
		cout << "Enter Student ID: ";
		int id;
		cin >> id;
		cin.ignore();
		Student student = linkedList.Search(id);
		student.PrintStudentInfo();
		
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
		
		linkedList.Update(student);
		

			
		break;
	}

	case enStudentOps::StudentOps_RemoveStudent:
	{
		cout << "Enter Student ID: ";
		int id;
		cin >> id;
		Student student = linkedList.Search(id);
		student.PrintStudentInfo();
		cout << "Are you sure you want to delete this student? (Y/N): ";
		char confirm;
		cin >> confirm;
		if (confirm == 'Y' || confirm == 'y')
		{
			linkedList.DeleteById(student.id);
		}
		
		break;
	}


	case enStudentOps::StudentOps_Exit:
	{
		AddAllStudents(linkedList);
		exit(0);
		break;
	}


	default:
		break;
	}


}

int main()
{
    
	clsLinkedList<Student> linkedList;
	fReadStudents(linkedList);
	
	
	int promptResult;

	while (1)
	{
		promptResult = Prompt();
		ActionResult(promptResult, linkedList);


	}



	return 0;



}

