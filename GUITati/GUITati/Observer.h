#pragma once

#include<vector>
#include<algorithm>
using std::vector;

class Observer {

public: 

	virtual void update() = 0;

	virtual ~Observer() = default;
};


class Observable {

	vector<Observer*> observers;

public:

	void addObserver(Observer* obs); 

	void removeObservere(Observer* obs);

	void notify();


};

