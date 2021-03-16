#include"ReadOnlyGUI.h"
#include<cstdlib>

ReadOnlyGUI::ReadOnlyGUI(Service& service) : service{ service } {

	service.addObserver(this);
}

void ReadOnlyGUI::update() {

	repaint();

}

void ReadOnlyGUI::paintEvent(QPaintEvent* ev) {


	QPainter p{ this }; 

	int x, y;
	int the_height, the_width;

	for (const auto& act : service.get_basket()) {

		x = rand() % 500;
		y = rand() % 500;
		the_height = rand() % 500;
		the_width = rand() % 500;

		if (x > the_height) {
			auto aux = x; 
			x = the_height; 
			the_height = aux;
		}

		if (y > the_width) {
			auto aux = y; 
			y = the_width; 
			the_width = aux;
		}
		
		p.drawRect(x, y, the_width, the_height);
	}
}

ReadOnlyGUI::~ReadOnlyGUI() {


	service.removeObservere(this);
}