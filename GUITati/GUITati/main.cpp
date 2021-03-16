#include<QtWidgets/qwidget.h>
#include<QtWidgets/qapplication.h>
#define _CRTDBG_MAP_ALLOC
#include<crtdbg.h>
#include<stdlib.h>
#include"Repository.h"
#include"Validator.h"
#include"Service.h"
#include"UI.h"
#include"Lista.h"
#include"VectorDinamicTemplate.h"
#include"MyGUI.h"

void test_all() {

	testAllRepo();
	test_AllValidator();
	test_AllService();
	test_list();
	test_template();


}

int main(int argc, char *argv[])
{

	test_all();

	QApplication a(argc, argv);


	RepoFile repository{"baza.txt"};
	Validator val;
	Basket basc;

	Service service{ repository,val,basc };

	BasketGUI b_gui{ service };
	MyGUI gui{service,b_gui};

	gui.show();

	return a.exec();


}
