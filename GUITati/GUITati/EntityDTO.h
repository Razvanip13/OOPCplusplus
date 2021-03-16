#pragma once
#include<map>
#include<string>
#include"Entity.h"

using std::string;
using std::map;
using std::pair;
class EntityDTO {

	string identificator; 
	string criteriu;
   
	int count=0;


public:

	

	EntityDTO() = default;

	EntityDTO(string identificator, string criteriu, int count);

	string get_identificator() const;
	string get_criteriu() const; 
	int get_count() const noexcept;
	void set_count(int new_coun) noexcept;

};