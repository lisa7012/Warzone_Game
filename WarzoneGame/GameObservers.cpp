#pragma once
#include <stdio.h>
#include <string>
#include "GameObservers.h"
#include "Map.h"
#include "GameEngine.h"
#include "Player.h"

/*--------------------
* ---Phase Observer---
* --------------------
* PhaseObserver Class
*/
//Default Constructor
PhaseObserver::PhaseObserver() {
}
//Destructor
PhaseObserver::~PhaseObserver() {
}
//Copy Constructor
PhaseObserver::PhaseObserver(const PhaseObserver& pO) {
}
//Assignment Operator
PhaseObserver& PhaseObserver::operator=(const PhaseObserver& pO) {
	return *this;
}
//Stream Insertion Operator
ostream& operator<<(ostream& out, const PhaseObserver& pO) {
	return out;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

/*
* ConcretePhaseObserver Class, derived from PhaseObserver Class
*/
//Default Constructor
ConcretePhaseObserver::ConcretePhaseObserver() {
	_phaseSubject = nullptr;
}
//Parametrized constructor
ConcretePhaseObserver::ConcretePhaseObserver(Player* p) {
	_phaseSubject = p;
	_phaseSubject->phaseAttach(this);
}
//Destructor
ConcretePhaseObserver::~ConcretePhaseObserver() {
	_phaseSubject->phaseDetach(this);
}
//Copy Constructor
ConcretePhaseObserver::ConcretePhaseObserver(const ConcretePhaseObserver& pO) {
	this->_phaseSubject = pO._phaseSubject;
}
//Assignment Operator
ConcretePhaseObserver& ConcretePhaseObserver::operator=(const ConcretePhaseObserver& pO) {
	this->_phaseSubject = pO._phaseSubject;
	return *this;
}
//Stream Insertion Operator
ostream& operator<<(ostream& out, const ConcretePhaseObserver& pO) {
	out << "ConcretePhaseObserver of: " << pO._phaseSubject;
	return out;
}
//Update attack method which override update attack from Phase Observer and calls the display method of the concrete phase observer
void ConcretePhaseObserver::updateAttack(string cntr, string cntrA, string nmA, int res, int roArm, string roCntr, int attArm, string name) {
	displayAttack(cntr, cntrA, nmA, res, roArm, roCntr, attArm, name);
}
//Update defense method which override update defense from Phase Observer and calls the display method of the concrete phase observer
void ConcretePhaseObserver::updateDefense(string cntr, string rCntr, int cArm, int fArm, string name) {
	displayDefense(cntr, rCntr, cArm, fArm, name);
}
//Update reinforce method which override update reinforce from Phase Observer and calls the display method of the concrete phase observer
void ConcretePhaseObserver::updateReinforce(int nbA, string cntr, string name) {
	displayReinforce(nbA, cntr, name);
}
//Method to display what happened during the attack phase with relevent information
void ConcretePhaseObserver::displayAttack(string c, string cA, string nA, int r, int roA, string roC, int attA, string name) {
	cout << endl << name << ": Attack phase" << endl << name << " attacked " << cA << ", which belongs to " << nA << ", from " << c << endl;
	if (r == 0) {
		cout << "After the attack " << name << " has " << roA << " on " << roC << "." << endl;
		cout << nA << " has " << attA << " on " << cA << "." << endl << endl;
	}
	else {
		cout << "After the attack " << name << " has " << roA << " on " << roC << "." << endl;
		cout << name << " conquered " << cA << "." << endl << endl;
	}
}
//Method to display what happened during the defense phase with relevent information
void ConcretePhaseObserver::displayDefense(string c, string rC, int cA, int fA, string name) {
	cout << endl << name << ": Defense phase" << endl << name << " chose armies from " << c << " and reinforced  " << rC << "." << endl;
	cout << c << " now has " << cA << " armies." << endl;
	cout << rC << " now has " << fA << " armies." << endl << endl;
}
//Method to display what happened during the reinforcement phase with relevent information
void ConcretePhaseObserver::displayReinforce(int nA, string c, string name) {
	cout << endl << name << ": Reinforcement phase" << endl << name << " put " << nA << " armies on the country " << c << "." << endl << endl;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

/*
* PhaseSubject Class
*/
//Default Constructor
PhaseSubject::PhaseSubject() {
	_phaseObservers = new vector<PhaseObserver*>;
}
//Destructor
PhaseSubject ::~PhaseSubject() {
}
//Copy Constructor
PhaseSubject::PhaseSubject(const PhaseSubject& pO) {
	this->_phaseObservers = pO._phaseObservers;
}
//Assignment Operator
PhaseSubject& PhaseSubject::operator=(const PhaseSubject& pO) {
	this->_phaseObservers = pO._phaseObservers;
	return *this;
}
//Stream Insertion Operator
ostream& operator<<(ostream& out, const PhaseSubject& pO) {
	out << "PhaseSubject of: " << pO._phaseObservers;
	return out;
}
//Detaching a phase observer (deleting it from the list)
void PhaseSubject::phaseDetach(PhaseObserver* Po) {
	for (int i = 0; i < (_phaseObservers->size()); i++) {
		if (_phaseObservers->at(i) == Po) {
			_phaseObservers->erase(_phaseObservers->begin() + i);
			break;
		}
	}
}
//Attaching a phase observer (adding it to the list)
void PhaseSubject::phaseAttach(PhaseObserver* Po) {
	_phaseObservers->push_back(Po);
}
/*
* The Subject class has a list or a collection of observers.
* When an event is triggered it calls the notify() operation which loops through all the observers by calling their update function.
*/
//Notify method for attack which will call the update attack for a phase observer
void PhaseSubject::notifyAttack(string country, string countryA, string nameA, int result, int roArmies, string roCountry, int attArmies, string name) {
	for (int i = 0; i < (_phaseObservers->size()); i++) {
		_phaseObservers->at(i)->updateAttack(country, countryA, nameA, result, roArmies, roCountry, attArmies, name);
	}
}
//Notify method for defense which will call the update defense for a phase observer
void PhaseSubject::notifyDefense(string country, string rCountry, int cArmies, int fArmies, string name) {
	for (int i = 0; i < (_phaseObservers->size()); i++) {
		_phaseObservers->at(i)->updateDefense(country, rCountry, cArmies, fArmies, name);
	}
}
//Notify method for reinforce which will call the update reinforce for a phase observer
void PhaseSubject::notifyReinforce(int nbArmies, string country, string name) {
	for (int i = 0; i < _phaseObservers->size(); i++) {
		_phaseObservers->at(i)->updateReinforce(nbArmies, country, name);
	}
}












/*------------------------------
* ---Game Statistics Observer---
* ------------------------------
StatisticObserver Class
*/
//Default Constructor
StatisticObserver::StatisticObserver() {
}
//Destructor
StatisticObserver::~StatisticObserver() {
}
//Copy Constructor
StatisticObserver::StatisticObserver(const StatisticObserver& pO) {
}
//Assignment Operator
StatisticObserver& StatisticObserver::operator=(const StatisticObserver& pO) {
	return *this;
}
//Stream Insertion Operator
ostream& operator<<(ostream& out, const StatisticObserver& pO) {
	return out;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

/*
ConcreteStatisticObserver Class, derived from StatisticObserver Class
*/
//Default Constructor
ConcreteStatisticObserver::ConcreteStatisticObserver() {
}
//Parameterized Constructor
ConcreteStatisticObserver::ConcreteStatisticObserver(Map* map, GameEngine* g) {
	_subject = map;
	_subject->attach(this);
	gameEngine = g;
}
//Destructor
ConcreteStatisticObserver::~ConcreteStatisticObserver() {
	_subject->detach(this);
}
//Copy Constructor
ConcreteStatisticObserver::ConcreteStatisticObserver(const ConcreteStatisticObserver& pO) {
	this->_subject = pO._subject;
}
//Assignment Operator
ConcreteStatisticObserver& ConcreteStatisticObserver::operator=(const ConcreteStatisticObserver& pO) {
	this->_subject = pO._subject;
	return *this;
}
//Stream Insertion Operator
ostream& operator<<(ostream& out, const ConcreteStatisticObserver& pO) {
	out << "ConcreteStatisticObserver of: " << pO._subject;
	return out;
}
//Update
void ConcreteStatisticObserver::update() {
	display();
}
//Display
void ConcreteStatisticObserver::display() {
	vector<Player*> playerList = gameEngine->getPlayerList();
	Map* map = _subject;
	int size = map->getTerritoryList().size();
	vector<Territory*> a = map->getTerritoryList();

	switch (playerList.size()) {
	case 1:
		for (int j = 0; j < playerList.size(); j++) {
			double percent = (playerList.at(j)->getListOfTerritories().size() / (double)size) * 100;
			cout << "Player " << playerList.at(j)->getPosition() << " has " << playerList.at(j)->getListOfTerritories().size() << " territories. They own " << percent << "% of the map!" << endl;
		}
		cout << "The winner is Player " << playerList.at(0)->getPosition() << ". Congratulations!!" << endl;
		system("pause");
		break;
	default:
		for (int j = 0; j < playerList.size(); j++) {
			double percent = (playerList.at(j)->getListOfTerritories().size() / (double)size) * 100;
			cout << "Player " << playerList.at(j)->getPosition() << " has " << playerList.at(j)->getListOfTerritories().size() << " territories. They own " << percent << "% of the map!" << endl;
		}
	}
	cout << endl;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

/*
StatisticSubject Class
*/
//Default Constructor
StatisticSubject::StatisticSubject() {
	_observers = new list<StatisticObserver*>;
}
//Destructor
StatisticSubject::~StatisticSubject() {
	delete _observers;
}
//Copy Constructor
StatisticSubject::StatisticSubject(const StatisticSubject& pO) {
	this->_observers = pO._observers;
}

//Assignment Operator
StatisticSubject& StatisticSubject::operator=(const StatisticSubject& pO) 
{
	this->_observers = pO._observers;
	return *this;
}
//Stream Insertion Operator
ostream& operator<<(ostream& out, const StatisticSubject& pO) {
	out << "StatisticSubject of: " << pO._observers;
	return out;
}
//Attach
void StatisticSubject::attach(StatisticObserver* o) {
	_observers->push_back(o);
}
//Detach
void StatisticSubject::detach(StatisticObserver* o) {
	_observers->remove(o);
}
//Notify
void StatisticSubject::notify() {
	list<StatisticObserver*>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->update();
}