#pragma once

#include"UndoList.h"

#include<fstream>

using std::unique_ptr; 
using std::vector;
using std::ofstream;

class Basket {

private:

	vector<Activitate> cos;

public:

	

	Basket()=default;

	Basket(const Basket& op) = delete;

	void add_activity(const Activitate &act);

	void stergere(string title);
	
	void delete_all_activities() noexcept; 

	void random_activities(int numar, vector<Activitate> activitati); 


	const vector<Activitate>& get_user_list() const noexcept;
	
	void save_basket_to_file(string filename);

	friend ostream& operator<<(ostream& stream, const Activitate& act);


	~Basket() = default;

};




//void test_all_list_service();