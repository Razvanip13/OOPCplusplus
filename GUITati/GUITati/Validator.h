#pragma once
#include<vector>
#include<string>
#include"Entity.h"
#include"VectorDinamicTemplate.h"


using std::vector;
using std::string;

class ValidatorException {

	const vector<string>& msg;

public:

	ValidatorException(const vector<string>& mesaje) noexcept : msg{mesaje} {}

	const vector<string>& getMsg() const noexcept;

};

class Validator {


	vector<string> mesaje;

public:
	Validator() = default; 

	void validate(const Activitate& act);

};


void test_AllValidator();