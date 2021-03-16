#pragma once
#include"Observer.h"
#include"Service.h"
#include<qwidget.h>
#include<qpainter.h>

class ReadOnlyGUI: public QWidget,public Observer{


	Service& service;
	
public: 

	ReadOnlyGUI(Service& service);

	void update() override;

	void paintEvent(QPaintEvent* ev) override;

	~ReadOnlyGUI();

};