#include"Entity.h"
#include<vector> 
#include<string>

using std::vector; 
using std::string;

string Activitate::get_titlu() const{
	
	return titlu;
}


string Activitate::get_descriere() const{
	
	return descriere;
}

string Activitate::get_tip() const{
	
	return tip;
}

float Activitate::get_durata() const noexcept{

	return durata;
}


void Activitate::set_titlu(string titlu_s) {
	
	this->titlu = titlu_s;
}

void Activitate::set_descriere(string descriere_s) {

	this->descriere = descriere_s;
}

void Activitate::set_tip(string tip_s) {
	
	this->tip = tip_s;
}

void Activitate::set_durata(float durata_s) noexcept{

	this->durata = durata_s;
}

ostream& operator<<(ostream& stream, const Activitate& act) {

	stream << act.get_titlu() << ";";
	stream << act.get_descriere() << ";";
	stream << act.get_tip() << ";";
	stream << act.get_durata();

	return stream;

}

istream& operator>>(istream& stream, Activitate& act) {


	string line;
	std::getline(stream, line);
	vector<string> parts;

	size_t position = 0;


	//pune pe linii separate!

	while ((position = line.find(";")) != string::npos) {

		string part = line.substr(0, position);
		parts.push_back(part);

		line.erase(0, position + 1);

	}

	parts.push_back(line);

	if (parts.size() != 4)
		return stream;

	act.titlu = parts.at(0);
	act.descriere = parts.at(1);
	act.tip = parts.at(2);
	act.durata = stof(parts.at(3));

	return stream;
}