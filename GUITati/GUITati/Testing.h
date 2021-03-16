#pragma once

#include"Basket.h"
#include"UndoList.h"
#include"Entity.h"


class UndoBasket: public ActiuneUndo {

	Basket& bas;
	Activitate act;

public:

	UndoBasket(Activitate& act, Basket& bas) : act{ act }, bas{ bas } {};

	void doUndo() override;

};