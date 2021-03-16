#pragma once
//#include<QtWidgets\qapplication.h>
#include<qwidget.h>
#include<QtWidgets/qboxlayout.h>
#include<QtWidgets/qlineedit.h>
#include<QtWidgets/qformlayout.h>
#include<QtWidgets/qlistwidget.h>
#include<QtWidgets/qpushbutton.h>
#include<QtWidgets\qlabel.h>
#include<QtWidgets\qmessagebox.h>

#include<vector>


using std::vector;



#include"Entity.h"
#include"Service.h"


class BasketGUI : public QWidget, public Observer {


private:



	Service& service;

	QLineEdit* titluTxt = new QLineEdit; 
	QLineEdit* descriereTxt = new QLineEdit;
	QLineEdit* tipTxt = new QLineEdit;
	QLineEdit* durataTxt = new QLineEdit;
	QLineEdit* numarTxt = new QLineEdit;
	QLineEdit* fisierTxt = new QLineEdit;
	QListWidget* lista_cos = new QListWidget;
	QListWidget* lista_activitati = new QListWidget;
	
	QPushButton* arataBtn = new QPushButton{"Arata cosul"};
	QPushButton* addBtn = new QPushButton{ "Adauga" };
	QPushButton* delete_basketBtn = new QPushButton{ "Sterge cos" };
	QPushButton* random_numberBtn = new QPushButton{ "Aleator" };
	QPushButton* undoBtn = new QPushButton{ "Undo" };
	QPushButton* saveBtn = new QPushButton{ "Salveaza" };
	
	void initGUI();

	void innitConnect();

	void show_all(const vector<Activitate> lista);

	void reset_text_boxes();

	void load_data();

	void update() override;


public:

	BasketGUI(Service& service);
	BasketGUI() = delete;

	~BasketGUI();
};


