#pragma once
#include <iostream>
#include "student.h"
template <class T>
class clsNode
{

public:
    T data;
    clsNode<T>* next;


    clsNode()
    {
        next = nullptr;
    }

};

template <class T>
class clsLinkedList
{
private:



   
   

public:
    clsNode<T>* head;
    clsNode<T>* tail;
    int length = 0;
    clsLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    void AddNode(T &value)
    {

        
        clsNode<T>* node = new clsNode<T>();

        node->data = value;
		
        node->next = nullptr;

        if (head == nullptr)
        {
            head = node;
            tail = head;
            length++;
            return;
        }

        tail->next = node;
        tail = node;
        length++;

    }

   

    void Traverse()
    {
        if (head == nullptr)
        {
            std::cout << "List is Empty" << std::endl;
            return;
        }
        clsNode<T>* temp = head;
        while (temp->next != nullptr)
        {
            //std::cout << temp->data << ", ";
			temp->data.PrintStudentInfo();
            temp = temp->next;
        }

        //std::cout << temp->data;
		temp->data.PrintStudentInfo();


    }

	Student Search(int id)
	{
		clsNode<T>* temp = head;
		while (temp != nullptr)
		{
			if (temp->data.id == id)
			{
				return temp->data;
			}
			temp = temp->next;
		}

		return Student();
	}


   

  
    
    bool IsEmpty()
    {
        return head == nullptr;
    }

    void Delete(T value)
    {

        if (IsEmpty()) return;

        if (head != nullptr && head->data == value)
        {
            clsNode<T>* temp2 = head;
            head = head->next;
            delete temp2;
            return;  // إنهاء الدالة بعد حذف الرأس
        }

        clsNode<T>* temp = head;
        while (temp != nullptr && temp->next != nullptr)
        {
            if (temp->next->data == value)
            {
                clsNode<T>* temp2 = temp->next;

                temp->next = temp->next->next;
                delete temp2;
                std::cout << "Value Deleted Successfully" << std::endl << std::endl;
                return;
            }

            temp = temp->next;
            length--;
        }


        std::cout << "Value Not Found" << std::endl << std::endl;



    }

    void DeleteById(int id)
    {

        if (IsEmpty()) return;

        if (head != nullptr && head->data.id == id)
        {
            clsNode<T>* temp2 = head;
            head = head->next;
            delete temp2;
            length--;
            return;  // إنهاء الدالة بعد حذف الرأس
        }

        clsNode<T>* temp = head;
        while (temp != nullptr && temp->next != nullptr)
        {
            if (temp->next->data.id == id)
            {
                clsNode<T>* temp2 = temp->next;

                temp->next = temp->next->next;
                delete temp2;

                std::cout << "Value Deleted Successfully" << std::endl << std::endl;
                length--;
                return;
            }

            temp = temp->next;
            
        }
    }

    void Update(Student student)
    {

		clsNode<T>* temp = head;
		while (temp != nullptr)
		{
			if (temp->data.id == student.id)
			{
		       

				temp->data = student;
				return;
			}
			temp = temp->next;
		}

		

    }

    void DeleteFirst()
    {
        if (IsEmpty()) return;

        clsNode<T>* temp = head;
        head = head->next;
        length--;
        delete temp;
    }

    void DeleteLast()
    {
        if (IsEmpty()) return;

        delete tail;

        clsNode<T>* temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }


        tail = temp;
        tail = temp;
        length--;
    }


};