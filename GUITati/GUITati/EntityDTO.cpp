#include"EntityDTO.h"


EntityDTO::EntityDTO(string identificator, string criteriu, int count) :identificator{ identificator }, criteriu{ criteriu }, count{ count } {}

string EntityDTO::get_identificator() const {

	return identificator;
}



string EntityDTO::get_criteriu() const {

	return criteriu;
}

int EntityDTO::get_count() const noexcept{

	return count;
}

void EntityDTO::set_count(int new_count) noexcept{

	count = new_count;
	
}