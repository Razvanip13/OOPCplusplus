#pragma once
#include<QAbstractTableModel>

#include"Entity.h"
#include<vector>

using std::vector;

class MyModel : public QAbstractTableModel {

	vector<Activitate> rep;

public:
	MyModel(vector<Activitate>& rep) : rep{ rep } {};

	int rowCount(const QModelIndex& parent ) const override;

	int columnCount(const QModelIndex& parent ) const override;
	
	QVariant data(const QModelIndex& index, int role) const override;

	void semnaleaza(const vector<Activitate> nou);

};