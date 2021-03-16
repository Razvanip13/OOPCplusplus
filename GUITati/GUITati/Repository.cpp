

#include"Repository.h"
#include<iostream>
#include<string>
#include<cassert>
#include"VectorDinamicTemplate.h"
#include<algorithm>
#include<fstream>
#include<random>

using std::string;
using std::find_if;
using std::replace_if;
using std::transform;

void Repo::store(const Activitate& a) {


	if (dictionar.find(a.get_titlu()) == dictionar.end())
		dictionar[a.get_titlu()] = a; 
	else
		throw RepoException("Exista o activitate cu titlul respectiv");


}

const Activitate& Repo::find(string titlu)  {



	map<string,Activitate>::iterator it = find_if(dictionar.begin(), dictionar.end(), [titlu](std::pair<string,Activitate> act) {
		return titlu == act.second.get_titlu();
	});

	if (it != dictionar.end())
		return it->second;

	throw RepoException("Nu exista activitate cu titlul: " + titlu + "\n");
}


void Repo::sterge(string titlu) {

	
	for(const auto& act :dictionar)
		if (act.second.get_titlu() == titlu) {

			dictionar.erase(titlu); 
			break;
		}
}


void Repo::update(string titlu,const Activitate &p) {


	for (auto& act : dictionar)
		if (act.second.get_titlu() == titlu) {
			
			act.second.set_titlu(p.get_titlu());
			act.second.set_descriere(p.get_descriere());
			act.second.set_tip(p.get_tip());
			act.second.set_durata(p.get_durata());
		}
	
}



const vector<Activitate>& Repo::getAll(){
	
	
	lista.clear();

	auto functie = [](std::pair<string, Activitate> element) {

		return element.second;
	};
	
	transform(dictionar.begin(), dictionar.end(), std::back_inserter(lista), functie);

	return lista;

}

string RepoException::getMessage() {
	
	return msg;
}


void RepoFile::loadFromFile() {




	std::ifstream f;

	f.open(fileName); 

	if (!f.is_open()) {

		throw RepoException("Nu s-a deschis\n"); 
	}

	while (!f.eof()) {

		Activitate act("", "", "", 0);

		f >> act; 
			
		if (f.eof()) break;
	
		Repo::store(act);
	}


	f.close();

}

void RepoFile::saveToFile() {

	std::ofstream f; 
	
	f.open(fileName); 

	if (!f.is_open()) {

		throw RepoException("Nu s-a deschis\n");
	}
	
	vector<Activitate> activitati = Repo::getAll();

	for (const auto& act : activitati) {
		
		f << act << "\n";
	}

	f.close();
}


void RepoFile::store(const Activitate& a){

	Repo::store(a); 

	saveToFile();
}

void RepoFile::sterge(string titlu) {

	Repo::sterge(titlu); 
	
	saveToFile();
}

void RepoFile::update(string titlu, const Activitate& p) {

	Repo::update(titlu, p);
	saveToFile();
}


void RepoLab::store(const Activitate& a) {

	const double rand_value = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
	
	if (rand_value < probabilitate) {

		string s = std::to_string(probabilitate);
		throw exception("Peste probabilitate");

	}

	Repo::store(a);

}

void RepoLab::sterge(string titlu) {

	const double rand_value = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
	
	if (rand_value < probabilitate) {

		string s = std::to_string(probabilitate);
		throw exception("Peste probabilitate");

	}

	Repo::sterge(titlu);

}


void RepoLab::update(string titlu, const Activitate& p) {


	const double rand_value = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);

	if (rand_value < probabilitate) {

		//string s = std::to_string(probabilitate); 
		throw exception("Peste probabilitate");

	}
		

	Repo::update(titlu, p);

}


const Activitate& RepoLab::find(string titlu) {

	const double rand_value = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);

	if (rand_value < probabilitate) {

		string s = std::to_string(probabilitate);
		throw exception("Peste probabilitate");

	}

	return Repo::find(titlu);

}



const vector<Activitate>& RepoLab::getAll() {

	const double rand_value = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);

	if (rand_value < probabilitate) {

	
		throw exception("Probabilitate depasita");

	}

     return	Repo::getAll();

}


void test_store() {


	std::ofstream f("auxiliar.txt"); 

	f << ""; 

	f.close();


	RepoFile rep{ "auxiliar.txt" };
	string auxiliar;



	rep.store(Activitate("Tenis", "Vom juca tenis", "Sport", 2));

	assert(rep.getAll().size() == 1); 

	rep.store(Activitate("Te", "Vom juca tenis", "Sport", 2));

	assert(rep.getAll().size() == 2);

	try {


		rep.store(Activitate("Tenis", "Vom juca tenis", "Sport", 2));

		assert(false);
	}
	catch (RepoException& ex) {

		assert(true);
		auxiliar= ex.getMessage();
		
	}
}

void test_find() {


	std::ofstream f("auxiliar.txt");

	f << "";

	f.close();


	RepoFile rep{"auxiliar.txt"};

	rep.store(Activitate("Tenis", "Vom juca tenis", "Sport", 2));
	rep.store(Activitate("Masa", "Luam masa", "Destindere", 3.5));

	assert(rep.getAll().size() == 2);

	Activitate p = rep.find("Masa");

	assert(p.get_titlu() == "Masa");
	assert(p.get_descriere() == "Luam masa");
	assert(p.get_tip() == "Destindere");
	assert(p.get_durata() == 3.5);

	try {

		p = rep.find("Boy");
		assert(false);
	}
	catch (RepoException&) {

		assert(true);
	}
	

}

void test_sterge() {


	std::ofstream f("auxiliar.txt");

	f << "";

	f.close();


	RepoFile rep{"auxiliar.txt"};

	rep.store(Activitate("Tenis", "Vom juca tenis", "Sport", 2));
	rep.store(Activitate("Masa", "Luam masa", "Destindere", 3.5));
	rep.store(Activitate("Dor", "Luam masa", "Destindere", 3.5));

	assert(rep.getAll().size() == 3);


	rep.sterge("Masa"); 

	assert(rep.getAll().size() == 2); 


	try {

		Activitate act = rep.find("Masa");
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

}

void test_update() {

	std::ofstream f("auxiliar.txt");

	f << "";

	f.close();


	RepoFile rep{"auxiliar.txt"};

	rep.store(Activitate("Tenis", "Vom juca tenis", "Sport", 2));
	rep.store(Activitate("Masa", "Luam masa", "Destindere", 3.5));

	assert(rep.getAll().size() == 2); 

	rep.update("Tenis", Activitate("Dogeball", "Vom juca dogeball", "Sport", 2)); 

	assert(rep.getAll().size() == 2);

	Activitate p = rep.find("Dogeball"); 

	assert(p.get_titlu() == "Dogeball");
	assert(p.get_descriere() == "Vom juca dogeball");
	assert(p.get_tip() == "Sport");
	assert(p.get_durata() == 2);


	try {

		rep.find("Tenis");
		assert(false);

	}
	catch (RepoException&) {

		assert(true);
	}

}
void test_read_from_file() {

	std::ifstream f("testread.txt");


	Activitate act;

	f >> act;

	f.close();

	assert(act.get_titlu() == "Bun");
	assert(act.get_descriere() == "Bun");
	assert(act.get_tip() == "bos");
	assert(act.get_durata() == 2);

}

void testAllRepo() {

	test_store();
	test_find();
	test_sterge();
	test_update();
	test_read_from_file();
}

