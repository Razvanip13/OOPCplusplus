#pragma once
#include<iostream>
#include<string>
using std::string;
using std::cout;

using std::istream;
using std::ostream;

class Activitate {


private:

	string titlu;
	string descriere;
	string tip;
	float durata=0;


public:

	Activitate() = default;

	Activitate(const string titlu, const string descriere, const string tip, const float durata) : titlu{ titlu }, descriere{ descriere }, tip{ tip }, durata{ durata } {}
	
	Activitate(const Activitate& op) :titlu{ op.titlu }, descriere{ op.descriere }, tip{ op.tip }, durata{ op.durata } {}



	/*
		Returneaza titlul
		return: titlu
	*/
	string get_titlu() const;

	
	void set_titlu(string titlu);


	/*
	Returneaza descriere
	return: descriere
	*/
	string get_descriere() const;

	void set_descriere(string descriere);

	/*
	Returneaza: tip
	return: tip
	*/
	string get_tip() const;

	void set_tip(string tip);
	
	/*
	Returneaza: durata
	return: durata
	*/
	float get_durata() const noexcept;

	void set_durata(float durata) noexcept;

	friend istream& operator>>(istream& stream, Activitate& act);
	friend ostream& operator<<(ostream& stream, const Activitate& act);

};
