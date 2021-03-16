

#include"UI.h"
#include<iostream>
#include<string>

using std::string; 
using std::cout;
using std::cin;
using std::getline;

void UI::interfata() {

	cout << "Bun venit:\n";
	cout << "1. Adauga activitate noua\n"; 
	cout << "2. Sterge activitate\n";
	cout << "3. Modificare activitate\n";
	cout << "4. Cauta o activitate\n";
	cout << "5. Filtrare activitati:\n";
	cout << "	5a. Dupa descriere\n";
	cout << "	5b. Dupa tip\n";
	cout << "6. Sortare activitati:\n";
	cout << "	6a. Dupa titlu\n";
	cout << "	6b. Dupa descriere\n";
	cout << "	6c. Dupa tip+durata\n";
	cout << "7. Afiseaza lista\n";
	cout << "8. Functionalitate din laboratorul trecut\n";
	cout << "9. Afisare comenzi meniu lista utilizator\n";
	cout << "undo. Face undo\n";
	cout << "0. Exit\n";

}

void UI::interfata2() {
	
	cout << "Meniu lista:\n";
	cout << "11. Goleste lista\n";
	cout << "12. Adauga in lista:\n";
	cout << "13. Adauga in lista aleator:\n";
	cout << "14. Salveaza lista in fisierul dat\n";
	
}


void UI::show_all(const vector<Activitate>& lista){

	for (const auto& act : lista) {
		cout << act.get_titlu() << ", " << act.get_descriere() << ", " << act.get_tip() << ", " << act.get_durata() << "\n";
	}

}

void UI::show_all2(vector<Activitate> lista) {

	for (const auto& act : lista) {
		cout << act.get_titlu() << ", " << act.get_descriere() << ", " << act.get_tip() << ", " << act.get_durata() << "\n";
	}

}

void UI::show_all3(const vector<EntityDTO>& lista) {

	for (const auto& act : lista) {
		cout << "Nume: " << act.get_identificator() << "---Tip: " << act.get_criteriu() << "---Type Count: " << act.get_count() << "\n";
	}

}

void UI::adauga() {

	string titlu, descriere, tip,new_line;
	float durata; 

	
	cout << "Titlu:";
	getline(cin, titlu);
	cout << "Descriere:";
	getline(cin, descriere);
	cout << "Tip:";
	getline(cin, tip);
	cout << "Durata:";
	cin >> durata;
	getline(cin, new_line);
	

	service.addActivity(titlu, descriere, tip, durata);

	show_all(service.getAll());

	cout << "Activitate inregistrata\n";

}

void UI::sterge() {

	string titlu;

	cout << "Titlu:";
	getline(cin, titlu);

	service.deleteActivity(titlu);


	show_all(service.getAll()); 

	cout << "Activitate stearsa\n";

}

void UI::modifica() {

	string titlu,titlu_nou, descriere, tip,new_line;
	float durata;

	cout << "Titlu:";
	getline(cin,titlu); 

	cout << "Titlu nou:";
	getline(cin,titlu_nou);
	cout << "Descriere:";
	getline(cin,descriere);
	cout << "Tip:";
	getline(cin,tip);
	cout << "Durata:";
	cin >> durata;
	getline(cin, new_line);

	service.modfifyActivity(titlu, titlu_nou, descriere, tip, durata); 

	
	show_all(service.getAll());

	cout << "Activitate modificata\n";

}

void UI::cauta() {

	string titlu;

	cout << "Titlu:";
	getline(cin, titlu);

	Activitate act = service.find(titlu); 

	cout << "Activitate gasita:\n"; 
	cout << act.get_titlu() << ", " << act.get_descriere() << ", " << act.get_tip() << ", " << act.get_durata() << "\n";

}


void UI::filtru_tip() {

	string tip; 

	cout << "Tipul:";

	getline(cin, tip); 

	show_all2(service.filtreazaTip(tip));

}

void UI::filtru_descriere() {

	string descriere;

	cout << "Descriere:";

	getline(cin, descriere);

	show_all2(service.filtreazaDescriere(descriere));
}

void UI::some_activites(){

	this->service.addActivity("Inot", "Vom inota cu pestisorii", "Sport", 2); 
	this->service.addActivity("Badminton", "Ne vom relaxa", "Sport", 1);
	this->service.addActivity("Gatit cu chef Scarlatescu", "Invatam de la maestru", "Gatit", 4);
	this->service.addActivity("Codat clasa tractor cu Csibula", "Tractoarele nu au aratat atat de bine pana acum", "Cod", 3);


}


void UI::adauga_in_lista() {


	
	string titlu;

	cout << "Titlul activitatii:"; 
	getline(cin, titlu);

	service.add_basket(titlu);

	show_all(service.get_basket());

	cout << "Activitate adaugata\n";
	
	
}

void UI::sterge_lista() noexcept{

	service.delete_basket();

}

void UI::adauga_random() {

	string new_line;
	int numar; 

	cout << "Spune un numar:"; 
	cin >> numar;
	getline(cin, new_line); 

	service.add_random_basket(numar);

	show_all(service.get_basket());

	cout << "Activitati noi notate in lista\n";

}

void UI::salveaza_in_fisier() {

	
	string fisier; 

	cout << "Numele fisierului:"; 
	getline(cin, fisier); 
	

	service.save_basket(fisier);

	cout << "Lista de activitati a fost salvata\n";

}

void UI::show_total_time() {

	int total;

	total = service.total_time();

	cout << "Timpul total va fi de: " << total << "ore\n";
}

void UI::make_undo() {

	service.undo();

	show_all(service.getAll());
}


void UI::make_undo2() {

	

	service.undo_secund();


	show_all(service.get_basket());

	
}


void UI::start() {

	//some_activites();

	interfata(); 

	string comanda,new_line;


	while (true) {


		cout << "Introduceti comanda: ";


		getline(cin, comanda);


		try {
			
			if (comanda == "0") break;
			
			if (comanda == "1") adauga();
			
			if (comanda == "2") sterge();
			
			if (comanda == "3") modifica(); 
					
			if (comanda == "4") cauta();

			if (comanda == "5a") filtru_descriere();
			
			if (comanda == "5b") filtru_tip();
			
			if (comanda == "6a") show_all(service.sortByTitle()); 
			
			if (comanda == "6b") show_all(service.sortByDescription()); 

			if (comanda == "6c") show_all(service.sortByTypeAndTime());
			
			if (comanda == "7") show_all(service.getAll());

			if (comanda == "8") show_all3(service.raport());

			if (comanda == "9") interfata2(); 

			if (comanda == "11") sterge_lista();

			if (comanda == "12") adauga_in_lista(); 

			if (comanda == "13") adauga_random(); 

			if (comanda == "14") salveaza_in_fisier();

			if (comanda == "15") show_total_time();
			
			if (comanda == "undo") make_undo();

			if (comanda == "undo2") make_undo2();


		}
		catch (RepoException ex) {


			cout << ex.getMessage();
		}
		catch (const ValidatorException ex) {

			
			for (const auto& mesaje : ex.getMsg()) {
				cout << mesaje << "\n";
			}

		}
		catch (exception&) {

			cout << "Probabilitate depasita\n";
		}
	}
	
}

