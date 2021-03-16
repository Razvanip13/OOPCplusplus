#include"Lista.h"
#include<assert.h>
using std::exception;

using std::cout;

void test_list() {

	MyVector vec;

	assert(vec.size() == 0); 

	vec.push_back(Activitate("a", "a", "a", 2));
	vec.push_back(Activitate("a", "a", "a", 2));
	vec.push_back(Activitate("a", "a", "a", 2));
	vec.push_back(Activitate("a", "a", "a", 2));

	assert(vec.size() == 4);

	vec.push_back(Activitate("a", "a", "a", 2));
	vec.push_back(Activitate("a", "a", "a", 2));

	assert(vec.size() == 6);

	MyVector vec2; 

	vec2 = vec;

	vec.erase(3);

	assert(vec.size() == 5);


	MyVector vec3; 

	vec3.push_back(Activitate("a", "a", "a", 2));
	vec3.push_back(Activitate("b", "a", "a", 2));
	vec3.push_back(Activitate("c", "a", "a", 2));
	vec3.push_back(Activitate("d", "a", "a", 2));

	assert(vec3.size() == 4);


	for (const auto& p : vec3) {
		
		assert(p.get_durata() == 2);
	}

	try {
		
		vec3.get(7);
		assert(false);
	}
	catch (exception&) {
		
		assert(true);
	}

	Activitate act = vec3.get(1);

	assert(act.get_titlu() == "b");
	assert(act.get_descriere() == "a");
	assert(act.get_tip() == "a");
	assert(act.get_durata() == 2);

	MyVector vec4{ vec3 };
	Activitate act2{ "a","a","a",2 };

	vec4.set(1, act2);

	
	try {

		vec4.set(20, act2);

		assert(false);
	}
	catch (exception&) {

		assert(true);
	}
	
	try {

		vec4.erase(40);

		assert(false);
	}
	catch (exception&) {
		
		assert(true);
	}

	Iterator it{ vec4 };
	const Iterator it2{ vec3 }; 

	if (it == it2) {
		assert(true);
	}
	else {
		assert(false);
	}


	while (it.valid()) {

		it.next();
	}
}