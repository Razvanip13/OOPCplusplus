
#include"ListService.h"
#include<assert.h>

void ListService::add_activity(string titlu) {

	auto act=lista_u.add_activity(titlu);

	lista_undo.push_back(std::make_unique<UndoAdaugaList>(act,lista_u));

}

void ListService::delete_all_activities() noexcept{

	lista_u.delete_activities();
}

void ListService::random_activities(int numar) {

	lista_u.say_a_number(numar);
}

void ListService::save_activities_to_file(string filename) {

	lista_u.saveToFile(filename,lista_u.get_lista());

}

const vector<Activitate>& ListService::get_user_list()const noexcept{

	return lista_u.get_lista();
}


void ListService::undo() {


	if (lista_undo.empty())
		throw RepoException("Nu mai exista operatii de undo\n");

	lista_undo.back()->doUndo();
	lista_undo.pop_back();

}



void test_add_activity() {

	Repo rep; 

	rep.store(Activitate("inot", "sincronic", "un tip", 3));
	rep.store(Activitate("boy", "sincronic", "zoinks", 1));
	rep.store(Activitate("bob", "sincronic", "un tip", 2));

	ListaDeActivitati lista{ rep };

	ListService service{ lista }; 


	assert(service.get_user_list().size() == 0);

	service.add_activity("inot"); 


	assert(service.get_user_list().size() == 1);

	assert(service.get_user_list().at(0).get_titlu() == "inot");
}
void test_delete_all_activities() {


	Repo rep;

	rep.store(Activitate("inot", "sincronic", "un tip", 3));
	rep.store(Activitate("boy", "sincronic", "zoinks", 1));
	rep.store(Activitate("bob", "sincronic", "un tip", 2));

	ListaDeActivitati lista{ rep };

	ListService service{ lista };

	assert(service.get_user_list().size() == 0);

	service.add_activity("inot");
	service.add_activity("bob");

	assert(service.get_user_list().size() == 2);

	service.delete_all_activities();

	assert(service.get_user_list().size() == 0);

}
void test_add_random() {

	Repo rep;

	rep.store(Activitate("inot", "sincronic", "un tip", 3));
	rep.store(Activitate("boy", "sincronic", "zoinks", 1));
	rep.store(Activitate("bob", "sincronic", "un tip", 2));

	ListaDeActivitati lista{ rep };

	ListService service{ lista };


	assert(service.get_user_list().size() == 0);

	service.random_activities(2); 

	assert(service.get_user_list().size() == 2);
}
void test_save_to_file_service() {

	Repo rep;

	rep.store(Activitate("inot", "sincronic", "un tip", 3));
	rep.store(Activitate("boy", "sincronic", "zoinks", 1));
	rep.store(Activitate("bob", "sincronic", "un tip", 2));

	ListaDeActivitati lista{ rep };

	ListService service{ lista };

	assert(service.get_user_list().size() == 0);

	service.add_activity("inot");
	service.add_activity("bob");

	assert(service.get_user_list().size() == 2);

	try {

		service.save_activities_to_file("test2.csv");
		assert(true);
	}
	catch (UserListException&) {
		assert(false);
	}

}
void test_all_list_service() {

	test_add_activity();
	test_delete_all_activities();
	test_add_random();
	test_save_to_file_service();

}
