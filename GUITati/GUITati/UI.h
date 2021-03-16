#pragma once
#include"Service.h"

class UI {

	Service& service; 

	//afiseaza interfata
	void interfata();

	//afisare interfata lista
	void interfata2();

	//adauga in lista utilizatorului o activitate
	void adauga_in_lista();

	//sterge din lista utilizatorului o activitate
	void sterge_lista() noexcept; 

	//adauga in lista utilizatorului activitati pseudoaleatorii
	void adauga_random(); 

	//salveaza intr-un fisier .csv lista utilizatorului
	void salveaza_in_fisier();

	// adauga niste activitati
	void some_activites();

	//adauga o noua activitiate
	void adauga();

	//sterge o activitate
	void sterge();

	//modifica o activitate
	void modifica();

	//cauta o activitate
	void cauta();

	/*
		afiseaza activitatile din lista
		param lista: vector<Activitate>&
		return: lista afisata
	*/
	void show_all(const vector<Activitate>& lista);


	/*
	afiseaza activitatile din lista
	param lista: vector<Activitate>
	return: lista afisata
	*/
	void show_all2(vector<Activitate> lista);

	/*
	afiseaza activitatile din lista
	param lista: vector<EntityDTO>&
	return: lista afisata
	*/
	void show_all3(const vector<EntityDTO>& lista);

	//filtreaza dupa tip
	void filtru_tip();

	//filtreaza dupa descriere
	void filtru_descriere();

	void show_total_time();

	void make_undo();

	void make_undo2();

public:

	UI(Service& service) noexcept :service{ service } {}

	UI(UI& ot) = delete;

	// porneste meniul utilizatorului
	void start();

	
};