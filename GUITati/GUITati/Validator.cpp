#include"Validator.h"
#include"Entity.h"
#include<assert.h>


const vector<string>& ValidatorException::getMsg()const noexcept{

	return msg;
}


void Validator::validate(const Activitate& act) {


	mesaje.clear();

	int cod = true; 

	if (act.get_titlu() == "") {
		cod = false; 
		mesaje.push_back("Nu ai introdus un titlu");
	}

	if (act.get_descriere() == "") {

		cod = false;
		mesaje.push_back("Nu ai introdus o descriere");
	}

	if (act.get_tip() == "") {

		cod = false; 
		mesaje.push_back("Nu ai introdus un tip");
	}

	if (act.get_durata() <= 0) {
		cod = false;

		mesaje.push_back("Durata nu poate fi un numar negativ");
	}

	if (!cod) throw ValidatorException(mesaje);

}


void test_validator() {

	Activitate act{ "Workshop","Mare","Psiho",2 };

	Validator val; 
	vector<string> msg;

	val.validate(act); 

	try {

		val.validate(Activitate("", "", "", -2));

		assert(false);
	}
	catch (const ValidatorException& ex) {

		assert(true);

		msg = ex.getMsg(); 


		assert(msg.at(0) == "Nu ai introdus un titlu");
		assert(msg.at(1) == "Nu ai introdus o descriere");
		assert(msg.at(2) == "Nu ai introdus un tip");
		assert(msg.at(3) == "Durata nu poate fi un numar negativ");
	}

}

void test_AllValidator() {

	test_validator();
}
