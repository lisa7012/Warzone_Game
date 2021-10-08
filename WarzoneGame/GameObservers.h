#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;
class Player;
class GameEngine;
class Map;

/* Observer pattern are implemented.
   Map are used as a subject.
   It reports the number of territories a player owns and its percentage when finishing the execution phase.
   Also, when a player lose all its territories, it removes player from the gameboard. */

   /*--------------------
   * ---Phase Observer---
   * --------------------
   * PhaseObserver Class
   * The Observer is the parent class of the concrete observers.
   * It contains a subject instance. When an observer is initialized, it registers/attaches itself to the subject
   * Equivalent to the Observer
   */
class PhaseObserver {
protected:
	//Default constructor
	PhaseObserver();
	//Copy Constructor
	PhaseObserver(const PhaseObserver &pO);
	//Assignment Operator
	PhaseObserver& operator=(const PhaseObserver &pO);
	//Stream Insertion Operator
	friend std::ostream& operator<<(std::ostream& out, const PhaseObserver &pO);
public:
	//Destructor
	~PhaseObserver();
	//Virtual methods that will get overriden
	//Update: Observers update their state independently from other observers however their state might change depending on the triggered event.
	virtual void updateAttack(string cntr, string cntrA, string nmA, int res, int roArm, string roCntr, int attArm, string name) = 0;
	virtual void updateDefense(string cntr, string rCntr, int cArm, int fArm, string name) = 0;
	virtual void updateReinforce(int nbA, string cntr, string name) = 0;
};

//------------------------------------------------------------------------------------------------------------------------------------------------------

/*
* ConcretePhaseObserver Class, derived from PhaseObserver
* The ConcreteObservers are classes that contain information specific to the current instance.
* The update function is called by the subject’s notify() operation.
* The observers update independently based on their current state.
* Equivalent to the DigitalClock
*/
class ConcretePhaseObserver : public PhaseObserver {
public:
	//Default constructor
	ConcretePhaseObserver();
	//Parameterized constructor
	ConcretePhaseObserver(Player* p);
	//Destructor
	~ConcretePhaseObserver();
	//Copy Constructor
	ConcretePhaseObserver(const ConcretePhaseObserver& cPO);
	//Assignment Operator
	ConcretePhaseObserver& operator=(const ConcretePhaseObserver& cPO);
	//Stream Insertion Operator
	friend ostream& operator<<(ostream& out, const ConcretePhaseObserver& cPO);
	//Methods which override the virtual methods from PhaseObserver
	//Update: Observers update their state independently from other observers however their state might change depending on the triggered event.
	void updateAttack(string cntr, string cntrA, string nmA, int res, int roArm, string roCntr, int attArm, string name);
	void updateDefense(string cntr, string rCntr, int cArm, int fArm, string name);
	void updateReinforce(int nbA, string cntr, string name);
	//Methods to display the phase
	void displayAttack(string c, string cA, string nA, int r, int roA, string roC, int attA, string name);
	void displayDefense(string c, string rC, int cA, int fA, string name);
	void displayReinforce(int nA, string c, string name);
private:
	//Player that belongs to the instantiated ConcretePhaseObserver
	Player* _phaseSubject;

};

//------------------------------------------------------------------------------------------------------------------------------------------------------

/*
PhaseSubject Class
Has a list or a collection of observers.
When an event is triggered it calls the notify() operation which loops
* through all the observers by calling their update function.
* Equivalent to the Subject
*/
class PhaseSubject
{
public:
	//Default constructor
	PhaseSubject();
	//Destructor
	~PhaseSubject();
	//Copy Constructor
	PhaseSubject(const PhaseSubject& pS);
	//Assignment Operator
	PhaseSubject& operator=(const PhaseSubject& pS);
	//Stream Insertion Operator
	friend ostream& operator<<(ostream& out, const PhaseSubject& pS);
	//Virtual methods which are passed down to every player. Methods have a declaration in the PhaseSubject class are not purely virtual
	//Register/Attach: Observers register themselves to the subject because they want to be notified when there is a change.
	virtual void phaseAttach(PhaseObserver* pO);
	virtual void phaseDetach(PhaseObserver* pO);
	//Notify: Depending on the implementation, the subject may “push” information to the observers, or, the observers may “pull” if they need information from the subject.
	virtual void notifyAttack(string country, string countryA, string nameA, int result, int roArmies, string roCountry, int attArmies, string name);
	virtual void notifyDefense(string country, string rCountry, int cArmies, int rArmies, string name);
	virtual void notifyReinforce(int nbArmies, string country, string name);
protected:
	/*
	* The Subject class has a list or a collection of observers.
	* When an event is triggered it calls the notify() operation which loops through all the observers by calling their update function.
	*/
	vector<PhaseObserver*>* _phaseObservers;
};















/*------------------------------
* ---Game Statistics Observer---
* ------------------------------
* StatisticObserver Class (Abstract Class)
* The Observer is the parent class of the concrete observers.
* It contains a subject instance. When an observer is initialized, it registers/attaches itself to the subject
* Equivalent to the class Observer
*/
class StatisticObserver {
protected:
	//Default Constructor
	StatisticObserver();
	//Copy Constructor
	StatisticObserver(const StatisticObserver& sO);
	//Assignment Operator
	StatisticObserver& operator=(const StatisticObserver& sO);
	//Stream Insertion Operator
	friend ostream& operator<<(ostream& out, const StatisticObserver& sO);
public:
	//Destroyer
	~StatisticObserver();
	//Pure Virtual Function
	virtual void update() = 0;
};

//------------------------------------------------------------------------------------------------------------------------------------------------------

/*
* ConcreteStatisticObserver Class, derived from StatisticObserver
* The ConcreteObservers are classes that contain information specific to the current instance.
* The update function is called by the subject’s notify() operation.
* The observers update independently based on their current state.
* Equivalent to the DigitalClock
*/
class ConcreteStatisticObserver : public StatisticObserver {
public:
	//Default Constructor
	ConcreteStatisticObserver();
	//Parameterized Constructor
	ConcreteStatisticObserver(Map* map, GameEngine* g);
	//Destructor
	~ConcreteStatisticObserver();
	//Copy Constructor
	ConcreteStatisticObserver(const ConcreteStatisticObserver& cSO);
	//Assignment Operator
	ConcreteStatisticObserver& operator=(const ConcreteStatisticObserver& cSO);
	//Stream Insertion Operator
	friend ostream& operator<<(ostream& out, const ConcreteStatisticObserver& cSO);
	//Update: Observers update their state independently from other observers however their state might change depending on the triggered event.
	void update();
	void display();
private:
	GameEngine* gameEngine;
	Map* _subject;
};

//------------------------------------------------------------------------------------------------------------------------------------------------------

/*
* StatisticSubject Class
* The Subject class has a list or a collection of observers.
* When an event is triggered it calls the notify() operation which loops through
* all the observers by calling their update function.
* Equivalent to the Subject
*/
class StatisticSubject {
public:
	//Default Constructor
	StatisticSubject();
	//Destructor
	~StatisticSubject();
	//Copy Constructor
	StatisticSubject(const StatisticSubject& sS);
	//Assignment Operator
	StatisticSubject& operator=(const StatisticSubject& sS);
	//Stream Insertion Operator
	friend ostream& operator<<(ostream& out, const StatisticSubject& sS);
	//Register/Attach: Observers register themselves to the subject because they want to be notified when there is a change.
	virtual void attach(StatisticObserver* o);
	virtual void detach(StatisticObserver* o);
	//Notify: Depending on the implementation, the subject may “push” information to the observers, or, the observers may “pull” if they need information from the subject.
	virtual void notify();
protected:
	list<StatisticObserver*>* _observers;
};