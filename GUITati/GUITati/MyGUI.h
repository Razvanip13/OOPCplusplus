#pragma once
#include<QtWidgets\qapplication.h>
#include<qwidget.h>
#include<QtWidgets/qboxlayout.h>
#include<QtWidgets/qlineedit.h>
#include<QtWidgets/qformlayout.h>
#include<QtWidgets/qlistwidget.h>
#include<QtWidgets/qpushbutton.h>
#include<qdebug.h>
#include<qstring.h>
#include<QtWidgets\qmessagebox.h>
#include<QtWidgets\qlabel.h>
#include<QtWidgets\qcheckbox.h>
#include<qbrush.h>
#include<qlistview.h>
#include<qtableview.h>

#include"Service.h"
#include"Repository.h"
#include"MyBasketGUI.h"
#include"ReadOnlyGUI.h"
#include"MyModel.h"


class MyGUI : public QWidget {


private:

	Service& service;
	BasketGUI& basketGUI;

	QPushButton* showbtn = new QPushButton{ "Arata tot" };
	QPushButton* add_one = new QPushButton{ "Adauga" };
	QPushButton* stergeBtn = new QPushButton{ "Sterge" };
	QPushButton* updateBtn = new QPushButton{ "Update" };
	QPushButton* cautaBtn = new QPushButton{ "Cauta" };
	QPushButton* filtru_descriere_btn = new QPushButton{ "Filtru descriere" };
	QPushButton* filtru_tip_btn = new QPushButton{ "Filtru tip" };
	QPushButton* sortare_titlu_btn = new QPushButton{ "Sortare titlu" };
	QPushButton* sortare_descriere_btn = new QPushButton{ "Sortare descriere" };
	QPushButton* sortare_tip_durata_btn = new QPushButton{ "Sortare tip si durata" };
	QPushButton* undoBtn = new QPushButton{ "Undo" };
	QListWidget* lista = new QListWidget;
	QLineEdit* titlu = new QLineEdit;
	QLineEdit* descriere = new QLineEdit;
	QLineEdit* tip = new QLineEdit;
	QLineEdit* durata = new QLineEdit;
	QLineEdit* ex_activity = new QLineEdit;
	QLineEdit* gime_number = new QLineEdit;
	QCheckBox* check_blanao = new QCheckBox("Deschide undo");
	QVBoxLayout* butoane_dinamice = new QVBoxLayout();
	QPushButton* exitBtn = new QPushButton{ "Exit" };
	QPushButton* rdonlyBtn = new QPushButton{ "Read Only" };

	QPushButton* basketBtn = new QPushButton{"Cosul"};
	QPushButton* golire_cos = new QPushButton{ "Golire cos" };
	QPushButton* add_aleator = new QPushButton{ "Aleator" };
	
	QListView* new_view=new QListView;
	QTableView* new_table = new QTableView;
	MyModel* model;


	void initGUI();

	void innitConnect();

	void show_all(const vector<Activitate>& lista);

	void reset_text_boxes();

	void do_undo();

	void adaugaButoane(const vector<Activitate>& lista);


public: 

	MyGUI(Service& service,BasketGUI& basketGUI);


};