#pragma once
#include"Repository.h"
#include"Validator.h"
#include"Entity.h"
#include<functional>
#include"VectorDinamicTemplate.h"
#include"EntityDTO.h"
#include"UndoList.h"
#include"Basket.h"
#include"Testing.h"
#include"Observer.h"

using std::function;
using std::unique_ptr;

class Service: public Observable {

	AbstractRepo& repo; 
	Validator& val;
	Basket& basket;
	
	vector<unique_ptr<ActiuneUndo>> undoActions;
	vector<unique_ptr<ActiuneUndo>> undo2;

	// filtru template
	const vector<Activitate> filtreaza(function<bool(const Activitate&)> fct);

	//vector<Activitate> generic_bubble(bool (*key)(const Activitate&,const Activitate&));

	//sorteaza dupa doua chei date
	//vector<Activitate> generic_bubble_double(bool (*MaiMicFct1)(const Activitate&, const Activitate&),bool (*MaiMicFct2)(const Activitate&,const Activitate&), bool (*Equal)(const Activitate&, const Activitate&));


public:

	/*
		Constructor
	*/
	
	Service(AbstractRepo& repo, Validator& val, Basket& basket) noexcept : repo{ repo }, val{ val }, basket{ basket } {}

	Service(Service& op) = delete;

	void undo();

	void undo_secund();

	/*
		Returneaza o lista cu toate activitatile
		return: lista cu activitati
	*/
	const vector<Activitate>& getAll(); 

	/*
		Adauga o noua activitate in lista 
		param titlu: string
		param descriere: string
		param tip: tip 
		param durata: float
		return: elementul introdus sau exceptie daca nu a reusit
	*/
	void addActivity(const string& titlu,const string& descriere, const string& tip, const float& durata);


	/*
		Sterge activitatea cu titlul dat 
		param titlu: string
		return: activitatea eliminata sau arunca exceptie daca nu a gasit-o
	*/
	void deleteActivity(const string& titlu);

	/*
		Modifica activitatea cu titlu dat
		param titlu: string
		param titlu_nou: string
		param descriere: string
		param tip: tip
		param durata: float
		return: elementul introdus sau exceptie daca nu a reusit
	*/
	void modfifyActivity(const string& titlu, const string& titlu_nou, const string& descriere, const string& tip, const float& durata);
	
	/*
		Cauta activitatea cu titlul dat
		param titlu:string
		return: activitatea daca o gaseste sau arunca exceptie
	*/
	const Activitate& find(string titlu) const;

	/*
		filtreaza dupa tip-ul dat
		param tip: string
		return: lista filtrata
	*/
	const vector<Activitate> filtreazaTip(string tip);

	/*
	filtreaza dupa descrierea data
	param descriere: string
	return: lista filtrata
	*/
	const vector<Activitate> filtreazaDescriere(string descriere);

	// return: lista sortata dupa titlu
	vector<Activitate> sortByTitle();

	// return: lista sortata dupa descriere
	vector<Activitate> sortByDescription();

	// return: lista sortata dupa tip si timp
	vector<Activitate> sortByTypeAndTime(); 

	//return: raport de la lab8
	vector<EntityDTO> raport();


	void add_basket(const string& title);

	void delete_basket() noexcept;

	void add_random_basket(const int& number);

	const vector<Activitate>& get_basket() const noexcept;

	void save_basket(string filename);

	int total_time();

};


void test_AllService();

