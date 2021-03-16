#include"MyBasketGUI.h"


void BasketGUI::innitConnect() {
	


	//arata cosul
	QObject::connect(arataBtn, &QPushButton::clicked, [this]() {


		show_all(service.get_basket());


	});


	QObject::connect(addBtn, &QPushButton::clicked, [&]() {

		try {

			service.add_basket(titluTxt->text().toStdString());

			show_all(service.get_basket());

			reset_text_boxes();

		}
		catch(RepoException& ex){


			QString mesaj = "";

			mesaj = QString::fromStdString(ex.getMessage());

			QMessageBox::warning(nullptr, "Eroare repositor", mesaj + " :(");

		}
		catch (ValidatorException& ex) {

			QString mesajul = "";




			for (const auto& mesaj : ex.getMsg()) {

				mesajul = mesajul + "\n" + QString::fromStdString(mesaj);
			}

			QMessageBox::warning(nullptr, "Eroare validare", mesajul);

		}

	});

	QObject::connect(lista_activitati, &QListWidget::itemSelectionChanged, [&]() {

		auto selectate = lista_activitati->selectedItems(); 

		if (selectate.isEmpty()) {

			titluTxt->setText("");
			descriereTxt->setText("");
			tipTxt->setText("");
			durataTxt->setText("");
			numarTxt->setText("");
			fisierTxt->setText("");
			
		}
		else {

			numarTxt->setText(""); 
			fisierTxt->setText("");

			auto titlu = selectate.at(0);

			auto act = service.find(titlu->text().toStdString());

			titluTxt->setText(QString::fromStdString(act.get_titlu()));
			descriereTxt->setText(QString::fromStdString(act.get_descriere()));
			tipTxt->setText(QString::fromStdString(act.get_tip()));
			durataTxt->setText(QString::number(act.get_durata()));
		}

	});


	QObject::connect(lista_cos, &QListWidget::itemSelectionChanged, [&]() {

		auto selectate = lista_cos->selectedItems();

		if (selectate.isEmpty()) {

			titluTxt->setText("");
			descriereTxt->setText("");
			tipTxt->setText("");
			durataTxt->setText("");
			numarTxt->setText("");
			fisierTxt->setText("");

		}
		else {

			numarTxt->setText("");
			fisierTxt->setText("");

			auto titlu = selectate.at(0);

			
			for (const auto& act : service.get_basket()) {


				if (act.get_titlu() == titlu->text().toStdString()) {

					titluTxt->setText(QString::fromStdString(act.get_titlu()));
					descriereTxt->setText(QString::fromStdString(act.get_descriere()));
					tipTxt->setText(QString::fromStdString(act.get_tip()));
					durataTxt->setText(QString::number(act.get_durata()));
				}
			}
		}

	});


	QObject::connect(delete_basketBtn, &QPushButton::clicked, [&]() {

		service.delete_basket(); 

		reset_text_boxes();

		show_all(service.get_basket());


	});

	QObject::connect(random_numberBtn, &QPushButton::clicked, [&]() {

		if (numarTxt->text() != "") {


			service.add_random_basket(numarTxt->text().toInt()); 

			show_all(service.get_basket());


		}
		else {

			QMessageBox::warning(this, "Atentie!", "Trebuie sa specifici cate activitati vrei");
		}


	});

	QObject::connect(undoBtn, &QPushButton::clicked, [&]() {


		try {

			service.undo_secund(); 
			show_all(service.get_basket());

		}
		catch (RepoException& ex) {


			QString mesaj = "";

			mesaj = QString::fromStdString(ex.getMessage());

			QMessageBox::warning(nullptr, "Eroare repositor", mesaj + " :(");

		}
		catch (ValidatorException& ex) {

			QString mesajul = "";


			for (const auto& mesaj : ex.getMsg()) {

				mesajul = mesajul + "\n" + QString::fromStdString(mesaj);
			}

			QMessageBox::warning(nullptr, "Eroare validare", mesajul);

		}


	});


	QObject::connect(saveBtn, &QPushButton::clicked, [&]() {

		if (fisierTxt->text() != "") {

			service.save_basket(fisierTxt->text().toStdString()); 

			QMessageBox::information(this, "Succes", "Cos salvat in fisier");

		}
		else {

			QMessageBox::warning(this, "Atentie!", "Trebuie sa specifici fisierul");
		}

	});


}


void BasketGUI::initGUI() {

	auto principal = new QHBoxLayout; 
	auto stanga = new QVBoxLayout; 
	auto mijloc = new QVBoxLayout; 
	auto dreapta = new QVBoxLayout;
	auto grid_layout = new QGridLayout;
	auto layout_butoane = new QHBoxLayout;


	grid_layout->addWidget(new QLabel{ "Titlu" }, 0, 0);
	grid_layout->addWidget(titluTxt,0,1);
	grid_layout->addWidget(new QLabel{ "Descriere" }, 1, 0);
	grid_layout->addWidget(descriereTxt, 1, 1);
	grid_layout->addWidget(new QLabel{ "Tip" }, 2, 0);
	grid_layout->addWidget(tipTxt, 2, 1);
	grid_layout->addWidget(new QLabel{ "Durata" }, 3, 0);
	grid_layout->addWidget(durataTxt, 3, 1);
	grid_layout->addWidget(new QLabel{ "Numar" }, 4, 0);
	grid_layout->addWidget(numarTxt,4,1);
	grid_layout->addWidget(new QLabel{ "Fisier" }, 5, 0);
	grid_layout->addWidget(fisierTxt,5,1);


	layout_butoane->addWidget(arataBtn); 
	layout_butoane->addWidget(delete_basketBtn);
	layout_butoane->addWidget(undoBtn);
	layout_butoane->addWidget(saveBtn);
	layout_butoane->addWidget(addBtn);
	layout_butoane->addWidget(random_numberBtn);


	setLayout(principal); 

	principal->addLayout(stanga); 
	principal->addLayout(mijloc);
	principal->addLayout(dreapta);
	stanga->addWidget(new QLabel{ "Cosul tau" });
	stanga->addWidget(lista_cos);
	mijloc->addLayout(grid_layout);
	mijloc->addLayout(layout_butoane);
	dreapta->addWidget(new QLabel{ "Lista de activitati" }); 
	dreapta->addWidget(lista_activitati);


	titluTxt->setDisabled(true);
	descriereTxt->setDisabled(true);
	tipTxt->setDisabled(true);
	durataTxt->setDisabled(true);

}


void BasketGUI::show_all(const vector<Activitate> lista) {

	lista_cos->clear();

	for (const auto& act : lista) {

		lista_cos->addItem(QString::fromStdString(act.get_titlu()));
	}

}


void BasketGUI::reset_text_boxes() {

	titluTxt->setText(""); 
	descriereTxt->setText("");
	tipTxt->setText("");
	durataTxt->setText("");
	numarTxt->setText("");
	fisierTxt->setText("");

}

void BasketGUI::load_data() {

	auto list = service.getAll();
	
	for (const auto& act : list) {

		lista_activitati->addItem(QString::fromStdString(act.get_titlu()));

	}
}

void BasketGUI::update() {

	show_all(service.get_basket());
}

BasketGUI::BasketGUI(Service& service) : service{ service } {

	service.addObserver(this); 

	initGUI();
	load_data();
	innitConnect();
	reset_text_boxes();
	
}

BasketGUI::~BasketGUI() {

	service.removeObservere(this);
}