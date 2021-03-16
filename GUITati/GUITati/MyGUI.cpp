#include"MyGUI.h"
#include<qbrush.h>
#include<memory>


void MyGUI::innitConnect() {



	//adaugare
	QObject::connect(add_one, &QPushButton::clicked, [&]() {

		try {

			auto titlul = titlu->text().toStdString();
			auto descrierea = descriere->text().toStdString();
			auto tipul = tip->text().toStdString();

			float timpul=-1;

			if (durata->text().toStdString() == "")
				timpul = -1;
			else
				timpul = std::stof(durata->text().toStdString());


			reset_text_boxes();

			service.addActivity(titlul, descrierea, tipul, timpul);

			show_all(service.getAll());

			//adaugaButoane(service.getAll());


			QMessageBox::information(nullptr, "Succes", "Activitate adaugata ^^");

		}
		catch (RepoException& ex) {


			QString mesaj = "";
			
			mesaj = QString::fromStdString(ex.getMessage());

			QMessageBox::warning(nullptr, "Eroare repositor", mesaj+" :(");

		}
		catch (const ValidatorException ex) {

			QString mesajul="";

			


			for (const auto& mesaj : ex.getMsg()) {

				mesajul = mesajul + "\n" + QString::fromStdString(mesaj);
			}

			QMessageBox::warning(nullptr, "Eroare validare", mesajul);
		}

	});

	//afisare
	QObject::connect(showbtn, &QPushButton::clicked, [&]() {

		try {

			show_all(service.getAll());

		}
		catch (RepoException ex) {

			QString mesaj = "";

			mesaj = QString::fromStdString(ex.getMessage());

			QMessageBox::information(nullptr, "Eroare repositor", mesaj);

		}
		catch (const ValidatorException ex) {

			QString mesajul = "";

			for (const auto& mesaj : ex.getMsg()) {

				mesajul = mesajul + "\n" + QString::fromStdString(mesaj);
			}

			QMessageBox::information(nullptr, "Eroare validare", mesajul);
		}


	});

	//stergere
	QObject::connect(stergeBtn, &QPushButton::clicked, [&]() {


		try {

			auto titlul = titlu->text().toStdString();

			service.deleteActivity(titlul);

			show_all(service.getAll());

			//adaugaButoane(service.getAll());

			QMessageBox::information(nullptr, "Succes", "Activitate stearsa ^^");


		}
		catch (RepoException ex) {

			QString mesaj = "";

			mesaj = QString::fromStdString(ex.getMessage());

			QMessageBox::information(nullptr, "Eroare repositor", mesaj);

		}
		catch (const ValidatorException ex) {

			QString mesajul = "";

			for (const auto& mesaj : ex.getMsg()) {

				mesajul = mesajul + "\n" + QString::fromStdString(mesaj);
			}

			QMessageBox::information(nullptr, "Eroare validare", mesajul);
		}


	});

	//update
	QObject::connect(updateBtn, &QPushButton::clicked, [&]() {

		try {



			auto titlul = titlu->text().toStdString();
			auto descrierea = descriere->text().toStdString();
			auto tipul = tip->text().toStdString();

			float timpul=-1;

			if (durata->text().toStdString() == "")
				timpul = -1;
			else
				timpul = std::stof(durata->text().toStdString());

			auto titlu_vechi = ex_activity->text().toStdString(); 


			reset_text_boxes();

			service.modfifyActivity(titlu_vechi, titlul, descrierea, tipul, timpul);

			show_all(service.getAll());

			QMessageBox::information(nullptr, "Succes", "Activitate modificata ^^");

		}
		catch (RepoException ex) {


			QString mesaj = "";

			mesaj = QString::fromStdString(ex.getMessage());

			QMessageBox::information(nullptr, "Eroare repositor", mesaj + " :(");

		}
		catch (const ValidatorException ex) {

			QString mesajul = "";




			for (const auto& mesaj : ex.getMsg()) {

				mesajul = mesajul + "\n" + QString::fromStdString(mesaj);
			}

			QMessageBox::information(nullptr, "Eroare validare", mesajul);
		}

	});

	//cautare
	QObject::connect(cautaBtn, &QPushButton::clicked, [&]() {

		try {

			auto titlul = titlu->text().toStdString();

			Activitate act = service.find(titlul); 


			reset_text_boxes();

			QString mesaj=""; 

			mesaj =mesaj+ QString::fromStdString(act.get_titlu()) + ",";
			mesaj = mesaj + QString::fromStdString(act.get_descriere()) + ", ";
			mesaj = mesaj + QString::fromStdString(act.get_tip()) + ", ";
			mesaj = mesaj + QString::fromStdString(std::to_string(act.get_durata()));

			lista->clear();

			lista->addItem(mesaj);

			QMessageBox::information(this, "Succes", "Am gasit activitatea ^^");

		}
		catch (RepoException ex) {


			QString mesaj = "";

			mesaj = QString::fromStdString(ex.getMessage());

			QMessageBox::information(nullptr, "Eroare repositor", mesaj + " :(");

		}
		catch (const ValidatorException ex) {

			QString mesajul = "";




			for (const auto& mesaj : ex.getMsg()) {

				mesajul = mesajul + "\n" + QString::fromStdString(mesaj);
			}

			QMessageBox::information(nullptr, "Eroare validare", mesajul);
		}



	});

	//filtru descriere
	QObject::connect(filtru_descriere_btn, &QPushButton::clicked, [&]() {


		try {

			auto cheie = descriere->text().toStdString();

			reset_text_boxes();


			if (cheie != "") {

				show_all(service.filtreazaDescriere(cheie));


			}
		}
		catch (RepoException ex) {


			QString mesaj = "";

			mesaj = QString::fromStdString(ex.getMessage());

			QMessageBox::information(nullptr, "Eroare repositor", mesaj + " :(");

		}
		catch (const ValidatorException ex) {

			QString mesajul = "";




			for (const auto& mesaj : ex.getMsg()) {

				mesajul = mesajul + "\n" + QString::fromStdString(mesaj);
			}

			QMessageBox::information(nullptr, "Eroare validare", mesajul);
		}


	});


	//filtru tip
	QObject::connect(filtru_tip_btn, &QPushButton::clicked, [&]() {


		try {
			auto cheie = tip->text().toStdString();

			reset_text_boxes();


			if (cheie != "") {

				show_all(service.filtreazaTip(cheie));

			}


		}
		catch (RepoException ex) {


			QString mesaj = "";

			mesaj = QString::fromStdString(ex.getMessage());

			QMessageBox::information(nullptr, "Eroare repositor", mesaj + " :(");

		}
		catch (const ValidatorException ex) {

			QString mesajul = "";




			for (const auto& mesaj : ex.getMsg()) {

				mesajul = mesajul + "\n" + QString::fromStdString(mesaj);
			}

			QMessageBox::information(nullptr, "Eroare validare", mesajul);
		}


	});


	QObject::connect(sortare_titlu_btn, &QPushButton::clicked, [&]() {


		try {
			
			
			show_all(service.sortByTitle());

			adaugaButoane(service.sortByTitle());

		}
		catch (RepoException ex) {


			QString mesaj = "";

			mesaj = QString::fromStdString(ex.getMessage());

			QMessageBox::information(nullptr, "Eroare repositor", mesaj + " :(");

		}
		catch (const ValidatorException ex) {

			QString mesajul = "";




			for (const auto& mesaj : ex.getMsg()) {

				mesajul = mesajul + "\n" + QString::fromStdString(mesaj);
			}

			QMessageBox::information(nullptr, "Eroare validare", mesajul);
		}


	});


	QObject::connect(sortare_descriere_btn, &QPushButton::clicked, [&]() {


		try {


			show_all(service.sortByDescription());

			adaugaButoane(service.sortByDescription());

		}
		catch (RepoException ex) {


			QString mesaj = "";

			mesaj = QString::fromStdString(ex.getMessage());

			QMessageBox::information(nullptr, "Eroare repositor", mesaj + " :(");

		}
		catch (const ValidatorException ex) {

			QString mesajul = "";




			for (const auto& mesaj : ex.getMsg()) {

				mesajul = mesajul + "\n" + QString::fromStdString(mesaj);
			}

			QMessageBox::information(nullptr, "Eroare validare", mesajul);
		}


	});


	QObject::connect(sortare_tip_durata_btn, &QPushButton::clicked, [&]() {


		try {


			show_all(service.sortByTypeAndTime());

			adaugaButoane(service.sortByTypeAndTime());

		}
		catch (RepoException ex) {


			QString mesaj = "";

			mesaj = QString::fromStdString(ex.getMessage());

			QMessageBox::information(nullptr, "Eroare repositor", mesaj + " :(");

		}
		catch (const ValidatorException ex) {

			QString mesajul = "";




			for (const auto& mesaj : ex.getMsg()) {

				mesajul = mesajul + "\n" + QString::fromStdString(mesaj);
			}

			QMessageBox::information(nullptr, "Eroare validare", mesajul);
		}


	});

	QObject::connect(check_blanao, &QCheckBox::clicked, [&]() {


		if (check_blanao->isChecked())
			undoBtn->setEnabled(true);
		else
			undoBtn->setEnabled(false);

	});

	//generare cosuri
	QObject::connect(basketBtn, &QPushButton::clicked, [this]() {


		//unique_ptr<BasketGUI> newBask = std::make_unique<BasketGUI>(service);
	
		auto newBask = new BasketGUI{ service };
		newBask->show();


	});

	QObject::connect(lista, &QListWidget::itemSelectionChanged, [&]() {

		auto selectate = lista->selectedItems(); 

		if (selectate.isEmpty()) {
			titlu->setText("");
			descriere->setText("");
			tip->setText ("");
			durata->setText("");
		}
		else {


			auto selItem = selectate.at(0);
			auto title = selItem->text();


			auto act = service.find(title.toStdString());

			titlu->setText(QString::fromStdString(act.get_titlu()));
			descriere->setText(QString::fromStdString(act.get_descriere()));
			tip->setText(QString::fromStdString(act.get_tip()));
			durata->setText(QString::number(act.get_durata()));
			ex_activity->setText(QString::fromStdString(act.get_titlu()));
		}

	});


	QObject::connect(undoBtn, &QPushButton::clicked, [&]() {

		this->do_undo();
	});

	QObject::connect(rdonlyBtn, &QPushButton::clicked, [&]() {

		auto newRd = new ReadOnlyGUI{ service }; 

		newRd->show();

	});

	QObject::connect(golire_cos, &QPushButton::clicked, [&]() {

		service.delete_basket(); 
		service.notify();

	});

	QObject::connect(add_aleator, &QPushButton::clicked, [&]() {

		auto numar = gime_number->text().toInt(); 

		service.add_random_basket(numar); 
		service.notify();


		reset_text_boxes();

	});

	QObject::connect(new_view->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {

		if (new_view->selectionModel()->selectedIndexes().isEmpty()) {
			reset_text_boxes();
			return;
		}


		int selRow = new_view->selectionModel()->selectedIndexes().at(0).row();

		auto cell1 = new_view->model()->index(selRow, 0); 
		auto value = new_view->model()->data(cell1, Qt::DisplayRole).toString();

		auto act = service.find(value.toStdString());
		
		titlu->setText(QString::fromStdString(act.get_titlu()));
		descriere->setText(QString::fromStdString(act.get_descriere()));
		tip->setText(QString::fromStdString(act.get_tip()));
		durata->setText(QString::number(act.get_durata()));

	});

	QObject::connect(new_table->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {

		if (new_table->selectionModel()->selectedIndexes().isEmpty()) {
			reset_text_boxes();
			return;
		}


		int selRow = new_table->selectionModel()->selectedIndexes().at(0).row();

		auto cell1 = new_table->model()->index(selRow, 0);
		auto title = new_table->model()->data(cell1, Qt::DisplayRole).toString();

		 cell1 = new_table->model()->index(selRow, 1);
		auto the_desc = new_table->model()->data(cell1, Qt::DisplayRole).toString();

		 cell1 = new_table->model()->index(selRow, 2);
		auto the_tip = new_table->model()->data(cell1, Qt::DisplayRole).toString();

		cell1 = new_table->model()->index(selRow, 3);
		auto the_time = new_table->model()->data(cell1, Qt::DisplayRole).toString();

		//auto act = service.find(value.toStdString());

		titlu->setText(title);
		descriere->setText(the_desc);
		tip->setText(the_tip);
		durata->setText(the_time);

	});


}


void MyGUI::reset_text_boxes() {


	titlu->setText("");
	descriere->setText("");
	tip->setText("");
	durata->setText("");
	ex_activity->setText("");
	gime_number->setText("");
	check_blanao->setChecked(false);
	ex_activity->setDisabled(true);
	undoBtn->setDisabled(true);
}


void MyGUI::show_all(const vector<Activitate>& lista_normala) {

	/*
	lista->clear();

	QString qact;

	for (const auto& act : lista_normala) {

		string normal = act.get_titlu(); //+ ", " + act.get_descriere() + ", " + act.get_tip() + ", " + std::to_string(act.get_durata());

		auto item = new QListWidgetItem(QString::fromStdString(normal));

		item->setBackground(QBrush{ Qt::yellow,Qt::SolidPattern });

		

		//qact = QString::fromStdString(normal);
		lista->addItem(item);

	}
	*/ 

	model->semnaleaza(lista_normala);

}

void MyGUI::do_undo() {

	try {

		service.undo();

		show_all(service.getAll());
	}
	catch (RepoException& ex) {

		QString mesaj = "";

		mesaj = QString::fromStdString(ex.getMessage());

		QMessageBox::warning(nullptr, "Eroare repositor", mesaj + " :(");

	}

}

void MyGUI::adaugaButoane(const vector<Activitate>& lista_normala) {
	

	/*
	for (int i = 0; i < this->butoane_dinamice->count(); i++) {

		QWidget* btn = butoane_dinamice->itemAt(i)->widget(); 

		if (btn != NULL) {
			
			btn->setVisible(false);
		}
	}
	*/

	while (butoane_dinamice->count() > 0) {

		auto btn = butoane_dinamice->itemAt(butoane_dinamice->count() - 1)->widget(); 

		if (btn != NULL) {
			delete btn;
		}
	}

	


	for (const auto& act : lista_normala) {


		auto btn = new QPushButton{ QString::fromStdString(act.get_titlu()) };

		butoane_dinamice->addWidget(btn);

		QObject::connect(btn, &QPushButton::clicked, [this,act,btn]() {

			service.deleteActivity(act.get_titlu()); 

			show_all(service.getAll());

			QMessageBox::information(this, "Succes", "Activitate stearsa");

			//butoane_dinamice->removeWidget(btn);

			delete btn;

		});
	}

	QObject::connect(exitBtn, &QPushButton::clicked, [&]() {

		close();

	});
	

}
void MyGUI::initGUI() {

	QHBoxLayout* principal= new QHBoxLayout;
	QVBoxLayout* stanga = new QVBoxLayout; 
	QHBoxLayout* layout_btn_sort = new QHBoxLayout;
	QHBoxLayout* undo_basket = new QHBoxLayout;
	auto dreapta = new QVBoxLayout;
	auto formular = new QFormLayout; 
	auto clasicele = new QHBoxLayout; 
	auto filtrari = new QHBoxLayout;
	auto grid_layout = new QGridLayout;
	auto another_layout = new QHBoxLayout;

	auto layout_table = new QHBoxLayout;

	another_layout->addWidget(rdonlyBtn);
	another_layout->addWidget(golire_cos);
	another_layout->addWidget(add_aleator);

	undo_basket->addWidget(basketBtn);
	undo_basket->addWidget(undoBtn);
	undo_basket->addWidget(exitBtn);


	grid_layout->addWidget(new QLabel("Titlu"), 0, 0);
	grid_layout->addWidget(titlu, 0, 1);
	grid_layout->addWidget(new QLabel("Descriere"), 1, 0);
	grid_layout->addWidget(descriere, 1, 1);
	grid_layout->addWidget(new QLabel("Tip"), 2, 0);
	grid_layout->addWidget(tip, 2, 1);
	grid_layout->addWidget(new QLabel("Durata"), 3, 0);
	grid_layout->addWidget(durata, 3, 1);
	grid_layout->addWidget(new QLabel("Vechea activitate"), 4, 0);
	grid_layout->addWidget(ex_activity, 4, 1);
	grid_layout->addWidget(new QLabel("Numar"), 5, 0);
	grid_layout->addWidget(gime_number, 5, 1);
	grid_layout->addWidget(check_blanao, 6, 0);


	clasicele->addWidget(add_one);
	clasicele->addWidget(stergeBtn);
	clasicele->addWidget(updateBtn);


	filtrari->addWidget(cautaBtn);
	filtrari->addWidget(filtru_descriere_btn);
	filtrari->addWidget(filtru_tip_btn);


	layout_btn_sort->addWidget(sortare_titlu_btn);
	layout_btn_sort->addWidget(sortare_descriere_btn);
	layout_btn_sort->addWidget(sortare_tip_durata_btn);
	layout_btn_sort->addWidget(showbtn);

	formular->addRow("Titlu", titlu); 
	formular->addRow("Descriere", descriere);
	formular->addRow("Tip", tip);
	formular->addRow("Durata", durata);
	formular->addRow("Vechea activitate", ex_activity);

	layout_table->addWidget(new_table);



	setLayout(principal);

	principal->addLayout(stanga);
	principal->addLayout(dreapta);
	//principal->addLayout(butoane_dinamice);

	principal->addLayout(layout_table);


	//stanga->addWidget(lista); 
	stanga->addWidget(new_view);
	stanga->addLayout(layout_btn_sort);



	dreapta->addLayout(grid_layout);
	dreapta->addLayout(clasicele); 
	dreapta->addLayout(filtrari);
	dreapta->addLayout(undo_basket);
	dreapta->addLayout(another_layout);



}

MyGUI::MyGUI(Service& service, BasketGUI& basketGUI) : service{ service }, basketGUI{ basketGUI } {

	initGUI();

	auto vec = service.getAll();
	model = new MyModel{ vec };

	new_view->setModel(model);
	new_table->setModel(model);


	innitConnect();

	reset_text_boxes();

	//adaugaButoane(this->service.getAll());

}