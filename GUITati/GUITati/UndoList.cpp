#include"UndoList.h"
#include"Testing.h"

void UndoAdauga::doUndo() {

	rep.sterge(act.get_titlu());
} 

void UndoSterge::doUndo() {

	rep.store(act);
}


void UndoModify::doUndo(){

	rep.update(act_nou.get_titlu(), act_vechi);
}


void UndoBasket::doUndo() {

	bas.stergere(act.get_titlu());

}