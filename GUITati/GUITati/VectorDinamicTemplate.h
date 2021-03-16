#pragma once
#include<exception>
using std::exception;

template<typename TElem>
class IteratorD;

template<typename TElem>
class VectorD {

	TElem* vectoras;
	int capacity;
	int length;

public:

	friend class IteratorD<TElem>;

	VectorD() :capacity{ 5 }, length{ 0 }, vectoras{ new TElem[5] } {};

	VectorD(const VectorD& ot);

	void operator=(const VectorD& ot);

	~VectorD();

	// adauga un element nou
	void push_back(const TElem& act);

	//returneaza numarul de elemente
	size_t size() const noexcept;

	//sterge elementul de la pozitia respectiva
	void erase(int position);

	//returneaza elemtnul de la pozitia respectiva sau arunca exceptie daca nu exista
	TElem& get(int poz) const;

	//modifica elementul de la poziti respectiva sau arunca exceptie daca pozitia nu exista
	void set(int poz, const TElem& elem);

	//returneaza un iterator pozitionat la incepulul vectorului
	IteratorD<TElem> begin() noexcept;

	//returneaza un iterator pozitionat la sfarsitul vectorului
	IteratorD<TElem> end() noexcept;

};

template<typename TElem>
VectorD<TElem>::VectorD(const VectorD& ot) :capacity{ ot.capacity }, length{ ot.length }, vectoras{ new TElem[ot.capacity] } {

	for (int index = 0; index < ot.length; index++) {
		vectoras[index] = ot.vectoras[index];
	}
}


template<typename TElem>
VectorD<TElem>::~VectorD() {

	delete[] vectoras;
}

template<typename TElem>
void VectorD<TElem>::operator=(const VectorD& ot) {
	
	delete[] vectoras;

	capacity = ot.capacity;
	length = ot.length;

	vectoras = new TElem[ot.capacity];

	for (int index = 0; index < ot.capacity; index++)
		vectoras[index] = ot.vectoras[index];
}

template<typename TElem>
void VectorD<TElem>::push_back(const TElem& act) {

	if (capacity == length) {

		const int new_capacity = 2 * capacity;
		TElem* new_vectoras = new TElem[new_capacity];

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
template<typename TElem>
size_t VectorD<TElem>::size() const noexcept {

	return this->length;
}

template<typename TElem>
void VectorD<TElem>::erase(int position) {

	if (position >= length || position < 0)
		throw exception("Nu exista element pe pozitia respectiva");


	for (int index = position; index < length - 1; index++)
		vectoras[index] = vectoras[index + 1];

	length--;
}

template<typename TElem>
TElem& VectorD<TElem>::get(int poz) const {

	if (poz < length) {

		return vectoras[poz];
	}

	throw exception("Nu exista element pe pozitia respectiva");
}

template<typename TElem>
void VectorD<TElem>::set(int poz, const TElem& elem) {

	if (poz < length) {

		vectoras[poz] = elem;
		return;
	}

	throw exception("Nu exista element pe pozitia respectiva");
}

template<typename TElem>
IteratorD<TElem> VectorD<TElem>::begin() noexcept {

	return IteratorD<TElem>{ *this };
}

template<typename TElem>
IteratorD<TElem> VectorD<TElem>::end() noexcept {

	return IteratorD<TElem>{ *this, length};
}

// aici este clasa pentru Iterator

template<typename TElem>
class IteratorD {

	VectorD<TElem>& vector_reference;
	int curent; 

public:

	//constructori iteratorii
	IteratorD(VectorD<TElem>& vec) noexcept;

	IteratorD(VectorD<TElem>& vec, int lg) noexcept;

	//returneeaza true daca pozitia este valida
	bool valid() noexcept;

	//se muta pe urmatoarea pozitie
	void next() noexcept;

	// returneaza elementul de pe pozitia curenta a iteratorului
	TElem& elem() noexcept;

	//returneaza valoarea elementului de pe pozitia curenta a iteratorului
	TElem& operator*() noexcept;

	//se muta pe urmatoarea pozitie
	IteratorD<TElem>& operator++() noexcept;

	bool operator==(const IteratorD<TElem>& ot) noexcept;

	bool operator!=(const IteratorD<TElem>& ot) noexcept;

};

template<typename TElem>
IteratorD<TElem>::IteratorD(VectorD<TElem>& vec) noexcept : vector_reference{ vec } {

	curent = 0;
}
template<typename TElem>
IteratorD<TElem>::IteratorD(VectorD<TElem>& vec, int lg) noexcept :vector_reference{ vec } {

	curent = lg;
}

template<typename TElem>
bool IteratorD<TElem>::valid() noexcept {

	if (curent < vector_reference.length)
		return true;

	return false;
}

template<typename TElem>
void IteratorD<TElem>::next() noexcept {

	curent++;
}

template<typename TElem>
TElem& IteratorD<TElem>::elem() noexcept {


	return vector_reference.vectoras[curent];
}

template<typename TElem>
TElem& IteratorD<TElem>::operator*() noexcept {

	return elem();
}

template<typename TElem>
IteratorD<TElem>& IteratorD<TElem>::operator++() noexcept {

	next();
	return (*this);
}

template<typename TElem>
bool IteratorD<TElem>::operator==(const IteratorD<TElem>& ot) noexcept {

	return curent == ot.curent;
}

template<typename TElem>
bool IteratorD<TElem>::operator!=(const IteratorD<TElem>& ot) noexcept {

	return !(curent == ot.curent);
}

void test_template();