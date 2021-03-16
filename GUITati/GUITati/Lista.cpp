#include"Lista.h"
#include<vector>
#include<exception>

using std::exception;
using std::vector;

MyVector::MyVector():capacity{ 5 }, length{ 0 }, vectoras{ new Activitate[5] } {}


MyVector::MyVector(const MyVector& ot) : capacity{ ot.capacity }, length{ ot.length }, vectoras{ new Activitate[ot.capacity] } {

	for (int index = 0; index < ot.capacity; index++)
		vectoras[index] = ot.vectoras[index];
}


void MyVector::operator=(const MyVector& ot) {

	delete[] vectoras;

	capacity = ot.capacity;
	length = ot.length;

	vectoras = new Activitate[ot.capacity];

	for (int index = 0; index < ot.capacity; index++)
		vectoras[index] = ot.vectoras[index];



}

void MyVector::push_back(const Activitate& act) {

	if (capacity == length) {

		const int new_capacity = 2 * capacity; 
		Activitate* new_vectoras = new Activitate[new_capacity]; 

		if (new_vectoras != nullptr) {

			for (int index = 0; index < capacity; index++) {

				new_vectoras[index] = vectoras[index];
			}

			delete[] vectoras;
			vectoras = new_vectoras;

			capacity = new_capacity;
		}
	}

	vectoras[length++] = act;

}

void MyVector::erase(int position) {

	if (position >= length || position < 0)
		throw exception("Nu exista pozitia");

	for (int index = position; index < length - 1; index++)
		vectoras[index] = vectoras[index + 1]; 
	
	length--;
}


int MyVector::size() const noexcept{

	return this->length;
}

Activitate& MyVector::get(int poz) const {

	if (poz < length) {

		return vectoras[poz];
	}

	throw exception("Nu exista element pe pozitia respectiva");
}

void MyVector::set(int poz, const Activitate& act) {

	if (poz < length) {

		vectoras[poz] = act;
		return;
	}

	throw exception("Nu exista element pe pozitia respectiva");
}

Iterator MyVector::begin() noexcept {

	return Iterator{ *this };
}

Iterator MyVector::end() noexcept {

	return Iterator{ *this,length };
}


MyVector::~MyVector() {

	delete[] vectoras;
}

Iterator::Iterator(MyVector& vec) noexcept : VectorList{ vec }  {

	curent = 0;
}

Iterator::Iterator(MyVector& vec, int lg) noexcept : VectorList{ vec } {

	curent = lg;
}


bool Iterator::valid() noexcept{

	if (curent < VectorList.length)
		return true; 

	return false;
}

void Iterator::next() noexcept {
	
	curent++;
}


Activitate& Iterator::elem() noexcept{


	return VectorList.vectoras[curent];
}


Activitate& Iterator::operator*() noexcept{

	return elem();
}

Iterator& Iterator::operator++() noexcept{

	next(); 
	return (*this);
}

bool Iterator::operator==(const Iterator& ot) noexcept {

	return curent == ot.curent;
}

bool Iterator::operator!=(const Iterator& ot) noexcept {

	return !(curent==ot.curent);
}