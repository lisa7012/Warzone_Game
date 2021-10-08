#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "Map.h"
#include "Order.h"
#include "MapLoader.h"
#include "GameObservers.h"

#include "PlayerStrategies.h"

using std::vector;
using std::string;

class Order;
class Map;
class Territory;

// Player class for Part 4 (Player) ===========
class Player : public PhaseSubject
{
public:
	// default constructor
	Player();
	// parametrisized constructor
	Player(string playerName);

	// A constructor for a player using a certain strategy
	Player(PlayerStrategy* strategy);
	// A getter to get the player's current strategy
	PlayerStrategy* getPlayerStrategy() { return playerStrategy; };
	// A setter to change the player's strategy during play
	void setPlayerStrategy(PlayerStrategy* strategy) { this->playerStrategy = strategy; };

	// destructor
	~Player();
	// copy constructor
	Player(const Player& p);
	// assignment operator
	Player& operator=(const Player& p); 
	// stream insertion operator
	friend ostream& operator<<(ostream& out, const Player& p);

	// methods to add Territory pointers to attack list and defend list
	void addTerritoryToDefend(Territory* t);
	void addTerritoryToAttack(Territory* t);

	// methods to clear lists to defend, to attack, and neighboring enemy territories
	void clearToDefend() { listToDefend.clear(); }
	void clearToAttack() { listToAttack.clear(); }
	void clearNeighboringEnemies() { neighboringEnemyTerritories.clear(); };

	// prints the list of territories the player will defend and attack
	void printListOfTerritories();
	void printToDefend();
	void printToAttack(); 
	void printNeighboringEnemyTerritories();

	// a method that creates an order object and adds it to the list of orders A2 ======
	void issueOrder() {return this->playerStrategy->issueOrder();};

	// Getter and setter for reinforcementPool
	int getReinforcementPool() { return reinforcementPool; };
	void setReinforcementPool(int a) { reinforcementPool = a; };

	// Getter and setter for preArmiesPool
	int getPreArmiesPool() { return preArmiesPool; };
	void setPreArmiesPool(int a) { preArmiesPool = a; };

	// Getter and setter for playerName
	string getPlayerName() { return playerName; };
	void setPlayerName(string n) { playerName = n; };
	
	// Methods to return, add and remove from the listOfTerritories
	void addTerritory(Territory* t) { listOfTerritories.push_back(t); };
	void removeTerritory(int tPos) { listOfTerritories.erase(listOfTerritories.begin() + tPos); }
	vector<Territory*> getListOfTerritories() { return listOfTerritories; };
	void sortGreatestToLeastArmies();
	void sortLeastToGreatestArmies();


	// Getter and setter for the position of the player in the player order list
	int getPosition() { return position; };
	void setPosition(int p) { position = p; }

	// Method to get neighboring enemy territories and a method to add those territories
	vector<Territory*> getNeighboringEnemyTerritories(Map* map);
	vector<Territory*> getListOfNeighboringEnemies() { return neighboringEnemyTerritories; }
	void addNeighboringTerritory(Territory* t) { neighboringEnemyTerritories.push_back(t); }
	
	// Methods thats returns a listToDefend and a listToAttack
	vector<Territory*> toDefend() { return this->playerStrategy->toDefend(); };
	vector<Territory*> toAttack() { return this->playerStrategy->toAttack(); };
	vector<Territory*> getListToDefend() { return listToDefend; };
	vector<Territory*> getListToAttack() { return listToAttack; };

	// Method to add order from player's class
	void addOrderToList(Order* o) { listOfOrders->addOrder(o); }

	// Getter and setter for finishedOrders (when the player finished their orders)
	bool getFinishedOrders() { return finishedOrders; };
	void setFinishedOrders(bool f) { finishedOrders = f; };

	// Getter and setter for listHaveBeenDecided (when their lists to attack and defend have been decided during their turn)
	bool getListsHaveBeenDecided() { return listsHaveBeenDecided; };
	void setListsHaveBeenDecided(bool f) { listsHaveBeenDecided = f; };

	// Getter for the player's listOfOrders
	OrdersList* getListOfOrders() { return listOfOrders; };
	
	// Getter and setter for their 
	Map* getMap() { return map; };
	void setMap(Map* m) { map = m; }

	// Getters and setters for counters used in the issuOrder method
	int getDeployCounter() { return deployCounter; }
	void setDeployCounter(int c) { deployCounter = c; }
	int getDefendCounter() { return defendCounter; }
	void setDefendCounter(int c) { defendCounter = c; }
	int getAttackCounter() { return attackCounter; }
	void setAttackCounter(int c) { attackCounter = c; }
	int getAttackAttempts() { return attackAttempts; }
	void setAttackAttempts(int c) { attackAttempts = c; }

	// Getter and setter for firstPool (their initial army pool included)
	bool getFirstPool() { return firstPool; };
	void setFirstPool(bool f) { firstPool = f; };

	// Getter and setter for the list of players
	vector<Player*> getPlayersList() { return playersList; }
	void setPlayersList(vector<Player*> p) { playersList = p; }

	// Getter and setters for when the players finish their deploy and advance orders
	bool getFinishedDeploy() { return finishedDeploy; };
	void setFinishedDeploy(bool f) { finishedDeploy = f; };
	bool getFinishedAdvance() { return finishedAdvance; };
	void setFinishedAdvance(bool f) { finishedAdvance = f; };

	Territory* getStrongestTerritory() { return strongestTerritory; };
	void setStrongestTerritory(Territory* t) { strongestTerritory = t; };

private:
	// vectors of pointers to Territory objects
	vector<Territory*> listOfTerritories;
	vector<Territory*> listToDefend;
	vector<Territory*> listToAttack;
	
	int reinforcementPool;
	int preArmiesPool;
	string playerName;
	int position;
	vector<Territory*> neighboringEnemyTerritories;
	Map* map;
	int deployCounter;
	int defendCounter;
	int attackCounter;
	int attackAttempts;
	bool finishedOrders;
	bool listsHaveBeenDecided;
	bool firstPool;
	bool finishedDeploy;
	bool finishedAdvance;
	vector<Player*> playersList;

	// player's strategy
	PlayerStrategy* playerStrategy;
	Territory* strongestTerritory;

	// vector of pointers to Order objects
	OrdersList* listOfOrders;
};

