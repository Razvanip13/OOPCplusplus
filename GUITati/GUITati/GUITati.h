#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GUITati.h"

class GUITati : public QMainWindow
{
	Q_OBJECT

public:
	GUITati(QWidget *parent = Q_NULLPTR);

private:
	Ui::GUITatiClass ui;
};
