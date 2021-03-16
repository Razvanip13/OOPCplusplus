#pragma once
#include<vector>
#include<map>
#include"Entity.h"
#include"VectorDinamicTemplate.h"

using std::vector;
using std::ostream;
using std::map;


class AbstractRepo {

public:


	virtual void store(const Activitate& a) = 0;

	virtual void sterge(string titlu) = 0;

	virtual const Activitate& find(string titlu) = 0;


	virtual const vector<Activitate>& getAll() = 0;

	virtual void update(string titlu, const Activitate& p) = 0;

	virtual ~AbstractRepo() = default;

};





class Repo : public AbstractRepo {

private:

	vector<Activitate> lista;
	map<string, Activitate> dictionar;


public:

	Repo() = default;
	Repo(const Repo& op) = delete;

	~Repo()=default;
	

	/*
		Adauga o noua activitate in lista
		param a: const Activitate&
		return: activitate adaugata sau arunca exceptie daca nu a fost adaugata
	*/
	void store(const Activitate& a) override;

	/*
		Sterge o activitate cu titlul dat
		param titlu: string 
		return: activitatea este stearsa sau arunca exceptie daca nu exista
	*/
	void sterge(string titlu) override;

	/*
		Gaseste activitatea cu titlul dat 
		param titlu: string 
		return: activitatea sau exceptie daca nu o gaseste
	*/
	const Activitate& find(string titlu) override;

	/*
		Returneaza lista cu activitatile curente
	*/
	const vector<Activitate>& getAll() override;

	/*
		Modifica activitatea cu titlul dat 
		param titlu: string
		param p: const Activitate&
	*/
	void update(string titlu,const Activitate& p) override;

	
	
};


class RepoException {

private:
	
	string msg;

public:

	RepoException(string m) :msg{ m } {}

	/*
		Returneaza mesajul excpetiei
	*/
	string getMessage();
};


class RepoFile : public Repo {

private: 

	string fileName;

	void loadFromFile(); 
	void saveToFile();

	

public:

	RepoFile(string filename) : Repo(), fileName{ filename } {
		
		loadFromFile();
	};

	void store(const Activitate& a) override;

	void sterge(string titlu) override;

	void update(string titlu, const Activitate& p) override;
};


class RepoLab : public Repo {

	double probabilitate;

public:

	RepoLab(double prob) : Repo(), probabilitate{ prob } {};

	void store(const Activitate& a) override;

	void sterge(string titlu) override;

	void update(string titlu, const Activitate& p) override;

	const Activitate& find(string titlu) override;

	const vector<Activitate>& getAll() override;
	
};

void testAllRepo();