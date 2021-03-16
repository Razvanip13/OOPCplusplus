#include"ListaActivitati.h"
#include<random>
#include<assert.h>
#include<fstream>

using std::ofstream;
using std::endl;
using std::stof;

void ListaDeActivitati::delete_activities() noexcept{
	
	lista_utilizator.clear();

}


void ListaDeActivitati::sterge(string name) {

	int position = 0;

	for (const auto& act : lista_utilizator) {

		if (act.get_titlu() == name){

			lista_utilizator.erase(lista_utilizator.begin() + position);
			return;
		}
		
		position++;
	}


	throw RepoException("Nu exista pozitia respectiva");
}

Activitate ListaDeActivitati::add_activity(string titlu){


	const auto& act = rep.find(titlu); 

	if (std::find_if(lista_utilizator.begin(), lista_utilizator.end(), [titlu](const Activitate& act2) {

		return titlu == act2.get_titlu();

	}) != lista_utilizator.end())
		throw UserListException("Ai introdus deja activitatea");


	lista_utilizator.push_back(act);

	return act;
}

void ListaDeActivitati::say_a_number(int nr) {



	if ((rep.getAll().size() - lista_utilizator.size()) < size_t(nr))
		throw UserListException("Nu avem destule activitati cat sa satisfaca cererea ta");

	std::mt19937 mt{ std::random_device{}() };
	const std::uniform_int_distribution<> dist(0, rep.getAll().size() - 1);

	vector<int> frequency;

	int contor=0;
	int randomNumber=0;
	
	vector<Activitate> lista = rep.getAll();



	while (contor < nr) {

		randomNumber = dist(mt);
		
		if (std::find(frequency.begin(), frequency.end(), randomNumber) == frequency.end()) {


			Activitate posibil_act = lista.at(randomNumber); 

			if (std::find_if(lista_utilizator.begin(), lista_utilizator.end(), [posibil_act](Activitate& act) {

				return act.get_titlu() == posibil_act.get_titlu();

			}) == lista_utilizator.end()) {


				frequency.push_back(randomNumber);
				contor++;

				lista_utilizator.push_back(lista.at(randomNumber));

			}

		}

	}
}

const vector<Activitate>& ListaDeActivitati::get_lista() const noexcept{

	return lista_utilizator;

	
}

void ListaDeActivitati::saveToFile(string filename,const vector<Activitate>& listuta) const {

	std::ofstream fisier(filename.c_str());
	
	if (!fisier.is_open()) {

		throw UserListException("Fisierul nu s-a deschis");
	}
	else {

		for (const auto& p : listuta) {
			fisier << p.get_titlu() << "," << p.get_descriere() << "," << p.get_tip() << "," << p.get_durata()<<","<<endl;
		}
	}


	fisier.close();

}

void ListaDeActivitati::loadFromFile(string filename) {
	
	std::ifstream fisier(filename.c_str());

	string linie;

	if (fisier.fail()) {

		throw UserListException("Fisierul nu s-a deschis");
	}
	else {

		while (fisier.good()) {

			Activitate act;

			std::getline(fisier, linie,','); 
			act.set_titlu(linie);

			if (linie == "\n") break;
			
			std::getline(fisier, linie, ',');
			act.set_descriere(linie);

			std::getline(fisier, linie, ',');
			act.set_tip(linie);

			std::getline(fisier, linie, ',');


			act.set_durata(stof(linie));

			lista_utilizator.push_back(act);
		}

	}

	

	fisier.close();

}




string UserListException::getMsg() const {

	return msg;
}

/*
void test_add_activities() {

	Repo rep; 

	ListaDeActivitati lista_u{ rep }; 

	assert(lista_u.get_lista().size() == 0); 


	rep.store(Activitate("inot", "sincronic", "un tip", 3));
	rep.store(Activitate("boy", "sincronic", "zoinks", 1));
	rep.store(Activitate("bob", "sincronic", "un tip", 2));

	lista_u.add_activity("inot"); 

	assert(lista_u.get_lista().size() == 1);

	try {


		lista_u.add_activity("nu exista");
		assert(false);

	}
	catch (RepoException&) {
		assert(true);
	}

	try {

		lista_u.add_activity("inot");
		assert(false);
	}
	catch(UserListException&){
		assert(true);
	}
}
void test_list_delete() {


	Repo rep;

	ListaDeActivitati lista_u{ rep };

	assert(lista_u.get_lista().size() == 0);


	rep.store(Activitate("inot", "sincronic", "un tip", 3));
	rep.store(Activitate("boy", "sincronic", "zoinks", 1));
	rep.store(Activitate("bob", "sincronic", "un tip", 2));

	lista_u.add_activity("inot");
	lista_u.add_activity("bob"); 

	assert(lista_u.get_lista().size() == 2);

	lista_u.delete_activities(); 

	assert(lista_u.get_lista().size() == 0);

}

void test_random_add() {

	Repo rep;

	ListaDeActivitati lista_u{ rep };

	assert(lista_u.get_lista().size() == 0);


	rep.store(Activitate("inot", "sincronic", "un tip", 3));
	rep.store(Activitate("boy", "sincronic", "zoinks", 1));
	rep.store(Activitate("zog", "sincronic", "un tip", 2));
	rep.store(Activitate("nog", "sincronic", "un tip", 2));
	rep.store(Activitate("lob", "sincronic", "un tip", 2));
	rep.store(Activitate("dob", "sincronic", "un tip", 2));
	rep.store(Activitate("bob", "sincronic", "un tip", 2));

	lista_u.say_a_number(4); 

	assert(lista_u.get_lista().size() == 4);

	vector<string> frequency; 

	vector<Activitate> lista = lista_u.get_lista(); 

	for (const auto& act : lista) {

		if (std::find(frequency.begin(), frequency.end(), act.get_titlu()) == frequency.end()) {
			
			frequency.push_back(act.get_titlu());
		}
		else {

			assert(false);
		}

	}

	assert(true);


	try {

		lista_u.say_a_number(30);
	}
	catch(UserListException& ex){

		string mesaj = ex.getMsg();

		assert(true);
	}

}
void test_save_to_file() {


	Repo rep;

	ListaDeActivitati lista_u{ rep };

	assert(lista_u.get_lista().size() == 0);


	rep.store(Activitate("inot", "sincronic", "un tip", 3));
	rep.store(Activitate("boy", "sincronic", "zoinks", 1));
	rep.store(Activitate("zog", "sincronic", "un tip", 2));
	rep.store(Activitate("nog", "sincronic", "un tip", 2));
	rep.store(Activitate("lob", "sincronic", "un tip", 2));
	rep.store(Activitate("dob", "sincronic", "un tip", 2));
	rep.store(Activitate("bob", "sincronic", "un tip", 2));


	vector<Activitate> gol; 

	lista_u.saveToFile("test.csv", gol);

	lista_u.say_a_number(4); 

	lista_u.saveToFile("test.csv", lista_u.get_lista());

	lista_u.delete_activities(); 

	assert(lista_u.get_lista().size() == 0); 

	lista_u.loadFromFile("test.csv"); 

	assert(lista_u.get_lista().size() == 4);



}

void test_all_new_list() {

	test_add_activities();
	test_list_delete();
	test_random_add();
	test_save_to_file();
}
*/