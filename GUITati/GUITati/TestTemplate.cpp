#include"VectorDinamicTemplate.h"
#include<assert.h>

void test_template() {

	VectorD<int> primul; 

	assert(primul.size() == 0);

	primul.push_back(1);
	primul.push_back(2);
	primul.push_back(3);
	primul.push_back(4);

	assert(primul.size() == 4);

	assert(primul.get(1) == 2); 

	primul.set(1, 3);

	assert(primul.get(1) == 3);

	primul.set(1, 2);

	int a = 1;

	for (const auto& p : primul) {

		assert(p == a);
		a++;
	}


	primul.push_back(3);
	primul.push_back(3);
	primul.push_back(3);
	primul.push_back(3);

	assert(primul.size() == 8);

	try {

		primul.get(12);
		assert(false);
	}
	catch (exception&) {

		assert(true);
	}

	try {


		primul.erase(20);
		assert(false);
	}
	catch (exception&) {

		assert(true);
	}


	try {

		primul.set(12,5);
		assert(false);
	}
	catch (exception&) {

		assert(true);
	}

	IteratorD<int> it{ primul };

	assert (it.valid() == true);

	IteratorD<int> it2{ primul,9 };

	assert(it2.valid() == false);

}