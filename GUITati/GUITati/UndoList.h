#pragma once
#include"Entity.h"
#include"Repository.h"
#include"Basket.h"

class ActiuneUndo {

public:

	virtual void doUndo() = 0;

	virtual ~ActiuneUndo() = default;

};


class UndoAdauga : public ActiuneUndo {

	Activitate act;
	AbstractRepo& rep;

public:

	UndoAdauga(Activitate& act, AbstractRepo& rep) : act{ act }, rep{ rep } {}

	void doUndo() override;

};


class UndoSterge : public ActiuneUndo {

	Activitate act;
	AbstractRepo& rep;

public:
	UndoSterge(Activitate& act, AbstractRepo& rep) : act{ act }, rep{ rep } {}

	void doUndo() override;

};

class UndoModify : public ActiuneUndo {

	Activitate act_vechi;
	Activitate act_nou;
	AbstractRepo& rep;

public:
	UndoModify(Activitate& act_vechi, Activitate& act_nou, AbstractRepo& rep) : act_vechi{ act_vechi }, act_nou{ act_nou }, rep{ rep } {}

	void doUndo() override;

};



