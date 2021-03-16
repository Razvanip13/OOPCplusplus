#include"Service.h"
#include<assert.h>
#include <type_traits>
#include"EntityDTO.h"
#include<algorithm>
#include<numeric>
using std::cout;
using std::to_string;
using std::pair;
using std::copy_if;
using std::sort;
using std::accumulate;

const vector<Activitate>& Service::getAll() {


	return repo.getAll();

}


void Service::addActivity(const string& titlu, const string& descriere, const string& tip, const float& durata) {

	Activitate act{ titlu,descriere,tip,durata }; 

	this->val.validate(act); 


	this->repo.store(act); 
	
	undoActions.push_back(std::make_unique<UndoAdauga>(act, repo));

}

void Service::deleteActivity(const string& titlu) {

	Activitate act=repo.find(titlu); 

	repo.sterge(titlu);

	undoActions.push_back(std::make_unique<UndoSterge>(act, repo));
}

void Service::modfifyActivity(const string& titlu, const string& titlu_nou, const string& descriere, const string& tip, const float& durata) {

	Activitate act_vechi=repo.find(titlu); 

	Activitate act{ titlu_nou,descriere,tip,durata };

	val.validate(act);

	repo.update(titlu, act);

	undoActions.push_back(std::make_unique<UndoModify>(act_vechi, act, repo));
}


void Service::undo() {


	if (undoActions.empty())
		throw RepoException("Nu mai exista operatii de undo\n"); 

	undoActions.back()->doUndo(); 
	undoActions.pop_back();

}

void Service::undo_secund() {


	if (undo2.empty())
		throw RepoException("Nu mai exista operatii de undo\n");

	undo2.back()->doUndo();
	undo2.pop_back();

}

const Activitate& Service::find(string titlu) const {

	return repo.find(titlu);
}


const vector<Activitate> Service::filtreaza(function<bool(const Activitate&)> fct) {


	vector<Activitate> lista_filtrata; 
	vector<Activitate> auxiliar = repo.getAll();

	copy_if(auxiliar.begin(), auxiliar.end(), std::back_inserter(lista_filtrata), fct);



	return lista_filtrata;

}


const vector<Activitate> Service::filtreazaTip(string tip) {

	return filtreaza([tip](const Activitate& act) {

		return act.get_tip() == tip;
	});

}

const vector<Activitate> Service::filtreazaDescriere(string descriere) {

	return filtreaza([descriere](const Activitate& act) {

		return act.get_descriere() == descriere;
	});

}


vector<Activitate> Service::sortByTitle() {

	auto auxiliar= repo.getAll() ;
	
	sort(auxiliar.begin(), auxiliar.end(),[](const Activitate& p1, const Activitate& p2) {

		return p1.get_titlu() < p2.get_titlu();

	});


	return auxiliar;
}

vector<Activitate> Service::sortByDescription() {

	auto auxiliar = repo.getAll();

	sort(auxiliar.begin(), auxiliar.end(), [](const Activitate& p1, const Activitate& p2) {

		return p1.get_descriere() < p2.get_descriere();

	});

	return auxiliar;
	
}

vector<Activitate> Service::sortByTypeAndTime() {


	auto the_only_fct_I_need = [](const Activitate& p1, const Activitate& p2){

		if (p1.get_tip() == p2.get_tip())
			return p1.get_durata() < p2.get_durata();

		return p1.get_tip() < p2.get_tip();

	}; 

	auto auxiliar = repo.getAll(); 

	sort(auxiliar.begin(), auxiliar.end(), the_only_fct_I_need);

	return auxiliar;

}


vector<EntityDTO> Service::raport() {

	vector<Activitate> listuta = repo.getAll();
	
	map<string, EntityDTO> dictionar;

	for(const auto& p:listuta)
		if (dictionar.find(p.get_tip()) == dictionar.end()) {

			dictionar[p.get_tip()].set_count(1);
		}
		else {

			dictionar[p.get_tip()].set_count(dictionar[p.get_tip()].get_count() + 1);
		}


	vector<EntityDTO> vec; 

	for (const auto& p : dictionar) {
		
		string tip = p.first; 
		EntityDTO obiect = p.second; 
		const int count = obiect.get_count(); 

		for (const auto& act : listuta) {
			
			if (act.get_tip() == tip) {
				EntityDTO new_object{ act.get_titlu(),tip,count };
				vec.push_back(new_object);
			}

		}

	}

	return vec;

}

int Service::total_time() {

	vector<Activitate> activitati = repo.getAll(); 

	auto lambda = [](int a,const Activitate& act) noexcept {


		return a + static_cast<int>(act.get_durata());
	};

	const int sum = accumulate(activitati.begin(), activitati.end(), 0, lambda); 

	return sum;

}

void Service::add_basket(const string& title) {



	auto actul = repo.find(title);


	auto lista = basket.get_user_list(); 

	for (auto& act : lista) {

		if (act.get_titlu() == title) {

			throw RepoException("Exista activitatea in cos");
		}
	}

	basket.add_activity(actul);
	undo2.push_back(std::make_unique<UndoBasket>(actul, basket));

	notify();
}

void Service::delete_basket() noexcept{

	basket.delete_all_activities();

	notify();
}

void Service::add_random_basket(const int& number) {

	basket.random_activities(number, repo.getAll());

	notify();
}

const vector<Activitate>& Service::get_basket() const noexcept {

	return basket.get_user_list();
}

void Service::save_basket(string filename) {
	
	basket.save_basket_to_file(filename);
}


void test_total_time() {

	
	std::ofstream f("auxiliar.txt");
	f << "";
	f.close();

	RepoFile rep{ "auxiliar.txt" };
	Validator val;
	Basket basket;
	Service service{ rep,val,basket };

	service.addActivity("Bun", "Bun", "bos", 2);
	service.addActivity("Bold", "Bi", "di", 3); 

	assert(service.total_time() == 5);
}

void test_undo() {


	std::ofstream f("auxiliar.txt"); 

	f << ""; 
	
	f.close();

	RepoFile rep{ "auxiliar.txt" };
	Validator val;
	Basket basket;
	Service service{ rep,val, basket };

	service.addActivity("Bun", "Bun", "bos", 2);

	assert(service.getAll().size() == 1);

	service.undo();


	assert(service.getAll().size() == 0);

	try {

		service.undo();
		assert(false);

	}
	catch (RepoException&) {

		assert(true);
	}

	service.addActivity("Bun", "Bun", "bos", 2);
	assert(service.getAll().size() == 1); 
	service.deleteActivity("Bun");
	assert(service.getAll().size() == 0);

	service.undo(); 

	assert(service.getAll().size() == 1);

	service.modfifyActivity("Bun", "bos", "bob", "bol", 3); 

	service.undo(); 

	try {

		service.find("bos");
	
		assert(false);
	}
	catch(RepoException&){
		assert(true);
	}


	Activitate act = service.find("Bun");

	assert(act.get_titlu() == "Bun");
	assert(act.get_descriere() == "Bun");
	assert(act.get_tip() == "bos");
	assert(act.get_durata() == 2);

	service.delete_basket();


	assert(service.get_basket().size() == 0);

	service.add_basket("Bun");

	assert(service.get_basket().size() == 1);


	service.undo_secund();

	assert(service.get_basket().size() == 0);
}


void test_basket() {

	std::ofstream f("auxiliar.txt");
	f << "";
	f.close();

	RepoFile rep{ "auxiliar.txt" };
	Validator val;
	Basket basket;
	Service service{ rep,val,basket };

	service.addActivity("Bun", "Bun", "bos", 2);
	service.addActivity("Bold", "Bi", "di", 3);

	service.add_basket("Bun");

	const Activitate act = service.get_basket().at(0);

	assert(act.get_titlu() == "Bun");

	service.add_random_basket(1);

	assert(service.get_basket().size() <= 2);

	service.save_basket("auxiliar2.txt");

	service.delete_basket();
}


void test_add() {

	
	std::ofstream f("auxiliar.txt");
	f << "";
	f.close();

	RepoFile rep{ "auxiliar.txt" };
	Validator val; 
	Basket basket;
	Service service{ rep,val,basket}; 

	service.addActivity("Bun", "Bun", "bos", 2); 

	
	assert(service.getAll().size() == 1);

	try {

		service.addActivity("", "", "", -2);

		assert(false);
	}
	catch (ValidatorException&) {

		assert(true);
	}

}

void test_delete() {

	std::ofstream f("auxiliar.txt");
	f << "";
	f.close();

	RepoFile rep{ "auxiliar.txt" };
	Validator val;
	Basket basket;
	Service service{ rep,val,basket };

	service.addActivity("a", "a", "a", 2); 
	service.addActivity("b", "a", "a", 2);
	service.addActivity("c", "a", "a", 2);

	assert(service.getAll().size() == 3); 

	service.deleteActivity("b"); 

	assert(service.getAll().size() == 2);

	try {

		service.find("b");

		assert(false);
	}
	catch(RepoException&){

		assert(true);

	}

}

void test_modify() {

	std::ofstream f("auxiliar.txt");
	f << "";
	f.close();

	RepoFile rep{ "auxiliar.txt" };
	Validator val;
	Basket basket;
	Service service{ rep,val,basket };

	service.addActivity("a", "a", "a", 2);
	service.addActivity("b", "a", "a", 2);
	service.addActivity("c", "a", "a", 2);

	assert(service.getAll().size() == 3);

	service.modfifyActivity("b", "d", "a", "a", 3);

	assert(service.getAll().size() == 3);

	service.find("d");

	try {

		service.find("b");

		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}


}

void test_filterType() {
	
	std::ofstream f("auxiliar.txt");
	f << "";
	f.close();

	RepoFile rep{ "auxiliar.txt" };
	Validator val;
	Basket basket;
	Service service{ rep,val,basket };
	vector<Activitate> lista_filtrata;

	service.addActivity("a", "a", "a", 2);
	service.addActivity("b", "a", "b", 2);
	service.addActivity("c", "a", "a", 2);

	lista_filtrata = service.filtreazaTip("a"); 

	assert(lista_filtrata.size() == 2);
 
	Activitate p = lista_filtrata.at(0);

	assert(p.get_titlu() == "a");
	assert(p.get_descriere() == "a");
	assert(p.get_tip() == "a");
	assert(p.get_durata() == 2);

	p = lista_filtrata.at(1);
	
	assert(p.get_titlu() == "c");
	assert(p.get_descriere() == "a");
	assert(p.get_tip() == "a");
	assert(p.get_durata() == 2);
}

void test_filterDescription() {

	std::ofstream f("auxiliar.txt");
	f << "";
	f.close();

	RepoFile rep{ "auxiliar.txt" };
	Validator val;
	Basket basket;
	Service service{ rep,val,basket };
	vector<Activitate> lista_filtrata;

	service.addActivity("a", "a", "a", 2);
	service.addActivity("b", "a", "b", 2);
	service.addActivity("c", "b", "a", 2);

	lista_filtrata = service.filtreazaDescriere("a");

	assert(lista_filtrata.size() == 2);

	Activitate p = lista_filtrata.at(0);

	assert(p.get_titlu() == "a");
	assert(p.get_descriere() == "a");
	assert(p.get_tip() == "a");
	assert(p.get_durata() == 2);

	p = lista_filtrata.at(1);

	assert(p.get_titlu() == "b");
	assert(p.get_descriere() == "a");
	assert(p.get_tip() == "b");
	assert(p.get_durata() == 2);

}

void test_sort_title_description() {

	std::ofstream f("auxiliar.txt");
	f << "";
	f.close();

	RepoFile rep{ "auxiliar.txt" };
	Validator val;
	Basket basket;
	Service service{ rep,val,basket };
	vector<Activitate> lista_filtrata;

	service.addActivity("b", "a", "a", 2);
	service.addActivity("a", "a", "b", 2);
	service.addActivity("c", "b", "a", 2);

	lista_filtrata = service.sortByTitle(); 

	assert(lista_filtrata.size() == 3);

	Activitate p{ lista_filtrata.at(0) };

	

	assert(p.get_titlu() == "a");
	assert(p.get_descriere() == "a");
	assert(p.get_tip() == "b");
	assert(p.get_durata() == 2);

	p = lista_filtrata.at(1);

	assert(p.get_titlu() == "b");
	assert(p.get_descriere() == "a");
	assert(p.get_tip() == "a");
	assert(p.get_durata() == 2);

	p = lista_filtrata.at(2);

	assert(p.get_titlu() == "c");
	assert(p.get_descriere() == "b");
	assert(p.get_tip() == "a");
	assert(p.get_durata() == 2);

	
	lista_filtrata = service.sortByDescription();

	p = lista_filtrata.at(0);
	
	assert(p.get_titlu() == "a");
	assert(p.get_descriere() == "a");
	assert(p.get_tip() == "b");
	assert(p.get_durata() == 2);


	p = lista_filtrata.at(1);

	assert(p.get_titlu() == "b");
	assert(p.get_descriere() == "a");
	assert(p.get_tip() == "a");
	assert(p.get_durata() == 2);

	p = lista_filtrata.at(2);

	assert(p.get_titlu() == "c");
	assert(p.get_descriere() == "b");
	assert(p.get_tip() == "a");
	assert(p.get_durata() == 2);
	

}

void test_doublesort() {

	std::ofstream f("auxiliar.txt");
	f << "";
	f.close();

	RepoFile rep{ "auxiliar.txt" };
	Validator val;
	Basket basket;
	Service service{ rep,val, basket };
	vector<Activitate> lista_filtrata;

	service.addActivity("b", "a", "a", 2);
	service.addActivity("a", "a", "b", 2);
	service.addActivity("c", "b", "a", 1);

	lista_filtrata = service.sortByTypeAndTime();

	assert(lista_filtrata.size() == 3);

	Activitate p{ lista_filtrata.at(0) };

	assert(p.get_titlu() == "c");
	assert(p.get_descriere() == "b");
	assert(p.get_tip() == "a");
	assert(p.get_durata() == 1);

	p = lista_filtrata.at(1);

	assert(p.get_titlu() == "b");
	assert(p.get_descriere() == "a");
	assert(p.get_tip() == "a");
	assert(p.get_durata() == 2);

	p = lista_filtrata.at(2);

	assert(p.get_titlu() == "a");
	assert(p.get_descriere() == "a");
	assert(p.get_tip() == "b");
	assert(p.get_durata() == 2);
}


void test_raport() {


	std::ofstream f("auxiliar.txt");
	f << "";
	f.close();

	RepoFile rep{ "auxiliar.txt" };
	Validator val;
	Basket basket;
	Service service{ rep,val, basket };

	service.addActivity("b", "a", "a", 2);
	service.addActivity("a", "a", "b", 2);
	service.addActivity("c", "b", "a", 1);

	vector<EntityDTO> vec = service.raport(); 

	auto p = vec.at(0); 

	assert(p.get_identificator() == "b"); 
	assert(p.get_criteriu() == "a"); 
	assert(p.get_count() == 2);

}

void test_AllService() {

	test_add();
	test_delete();
	test_modify();
	test_filterType();
	test_filterDescription();
	test_sort_title_description();
	test_doublesort();
	test_raport();
	test_undo();
	test_total_time();
	test_basket();
	
}

