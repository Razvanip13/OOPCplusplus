#include"Basket.h"

#include<random>

#include<fstream>
#include<algorithm>
#include<string>

using std::vector;
using std::ostream;
using std::istream;


void Basket::add_activity(const Activitate& act) {

	cos.push_back(act);
}

void Basket::delete_all_activities() noexcept {

	cos.clear();

}

const vector<Activitate>& Basket::get_user_list() const noexcept {

	return cos;

}


void Basket::random_activities(int numar, vector<Activitate> activitati) {

	int counter = 0;

	std::shuffle(activitati.begin(), activitati.end(), std::default_random_engine(std::random_device{}()));

	while (counter < numar && activitati.size()>0) {

		if (std::find_if(cos.begin(), cos.end(), [activitati](const Activitate& act) {

			return activitati.back().get_titlu() == act.get_titlu();

		}) == cos.end()) {

			cos.push_back(activitati.back());
			counter++;
		}

		activitati.pop_back();

		
	}

}




void Basket::save_basket_to_file(string filename) {

	std::ofstream f(filename);

	if (!f.is_open()) {
		
		throw RepoException("Nu s-a deschis fisierul");
	}
	else {

		for (const auto& act : cos) {

			f << act<<"\n";
		}

	}

	f.close();

}

void Basket::stergere(string title) {

	int counter = 0;

	for (const auto& act : cos) {
		if (act.get_titlu() == title) {

			cos.erase(cos.begin() + counter);

			break;
		}

		counter++;
	}
	
}


