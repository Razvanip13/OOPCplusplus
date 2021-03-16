#include"MyModel.h"
#include<qdebug.h>
#include<qbrush.h>

int MyModel::rowCount(const QModelIndex& parent = QModelIndex()) const {

	return rep.size();
}


int MyModel::columnCount(const QModelIndex& parent = QModelIndex()) const {

	return 4;

}

QVariant MyModel::data(const QModelIndex& index, int role = Qt::DisplayRole) const {

	if (role == Qt::DisplayRole) {

		qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;

		Activitate act = rep[index.row()];

		if (index.column() == 0) {

			return QString::fromStdString(act.get_titlu());

		}

		if (index.column() == 1) {

			return QString::fromStdString(act.get_descriere());

		}

		if (index.column() == 2) {

			return QString::fromStdString(act.get_tip());

		}

		if (index.column() == 3) {

			return QString::number(act.get_durata());

		}
	}

	if (role == Qt::BackgroundRole) {

		if (index.column() == 0) {

			QBrush brush{ Qt::yellow,Qt::SolidPattern };

			return brush;
		}

		if (index.column() == 1) {

			QBrush brush{ Qt::green,Qt::SolidPattern };

			return brush;
		}
	}

	return QVariant{};
}


void MyModel::semnaleaza(const vector<Activitate> nou) {


	rep = nou;

	auto topLeftC = createIndex(0, 0);
	auto bottomRightC = createIndex(rowCount(), columnCount());

	emit dataChanged(topLeftC, bottomRightC);

}