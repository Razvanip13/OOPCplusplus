#pragma once
#include"Entity.h"

class Iterator;

class MyVector {


	int capacity; 
	int length; 
	Activitate* vectoras;


public:

	friend class Iterator;

	MyVector();


	//#rule of 3

	//copy constructor
	MyVector(const MyVector& ot);


	//operatorul de assignment
	void operator=(const MyVector& ot);


	//destructor
	~MyVector();

	void push_back(const Activitate& act);

	int size() const noexcept;

	void erase(int position);
	
	Activitate& get(int poz) const; 

	void set(int poz,const Activitate& act);

	Iterator begin() noexcept; 

	Iterator end() noexcept;
};

class Iterator {

	MyVector& VectorList;
	int curent;

public:

	Iterator(MyVector& vec) noexcept;
	Iterator(MyVector& vec, int lg) noexcept;

	Activitate& operator*() noexcept;
	Iterator& operator++() noexcept;

	bool operator==(const Iterator& ot) noexcept;

	bool operator!=(const Iterator& ot) noexcept;

	bool valid() noexcept;

	void next() noexcept;

	Activitate& elem() noexcept;

};


void test_list();