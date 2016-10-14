#pragma once
#include"Student.h"
#include "DAO.h"
#include<iostream>
class StudentCtr
{
public:
	bool checkID(int);
	void add(string);
	void showAll();
	StudentCtr();
	void searchID();
	void searchName();
	void searchSum();
	void searchMath();
	void searchPhys();
	void searchChem();
	bool edit();
	bool del();
	void thongke();
	void swap(Student, Student);
	void sort(list<Student>);
	~StudentCtr();
};
