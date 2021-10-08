#include "Player.h"
#include <iostream>
#include <algorithm>

using std::vector;
using std::ostream;
using std::string;
using std::cout;
using std::endl;

//================ Beginning of Player Methods ==================

bool sortDescendingOrder(Territory* t1, Territory* t2) { return t1->getArmy() > t2->getArmy(); }
bool sortAscendingOrder(Territory* t1, Territory* t2) { return t1->getArmy() < t2->getArmy(); }

// Default Constructor
Player::Player() 
{
	listOfOrders = new OrdersList{};
	position = 0;
	reinforcementPool = 0;
	playerName = "";
	finishedOrders = false;
	listsHaveBeenDecided = false;
	deployCounter = 0;
	defendCounter = 0;
	attackCounter = 0;
	attackAttempts = 0;
	preArmiesPool = 0;
	firstPool = true;
	finishedDeploy = false;
	finishedAdvance = false;
}

// Constructor with playerStrategy
Player::Player(PlayerStrategy* strategy) 
{ 
	this->playerStrategy = strategy;
	playerStrategy->setPlayer(this);
	listOfOrders = new OrdersList{};
	position = 0;
	reinforcementPool = 0;
	playerName = "";
	finishedOrders = false;
	listsHaveBeenDecided = false;
	deployCounter = 0;
	defendCounter = 0;
	attackCounter = 0;
	attackAttempts = 0;
	preArmiesPool = 0;
	firstPool = true;
	finishedDeploy = false;
	finishedAdvance = false;
};

// Destructor 
Player::~Player()
{	
	for (int i = 0; i < listOfOrders->getOrders().size(); i++)
	{
		delete listOfOrders->getOrders().at(i);
		listOfOrders->getOrders().at(i) = nullptr;
	}
	listOfOrders->getOrders().clear();
	listOfOrders = nullptr;

	for (int i = 0; i < listToDefend.size(); i++)
	{
		delete listToDefend.at(i);
		listToDefend[i] = nullptr;
	}
	listToDefend.clear();
	
	for (int i = 0; i < listToAttack.size(); i++)
	{
		delete listToAttack.at(i);
		listToAttack.at(i) = nullptr;
	}
	listToAttack.clear();

	for (int i = 0; i < listOfTerritories.size(); i++)
	{
		listOfTerritories.at(i) = nullptr;
	}
	listOfTerritories.clear();
}

// Parametrisized Constructor 
Player::Player(string name)
{
	playerName = name;
	listOfOrders = new OrdersList{};
}

// Copy Constructor
Player::Player(const Player& p)
{ 
	this->listOfTerritories = p.listOfTerritories;
	this->listOfOrders = p.listOfOrders;
} 

// Assignment Operator
Player& Player::operator=(const Player& p) 
{
	this->listOfTerritories = p.listOfTerritories;
	this->listOfOrders = p.listOfOrders;

	return *this;
}

// Stream Insertion Operator
ostream& operator<<(ostream& out, const Player& p)
{
	out << "Player's List of Territories: " << endl;
	out << "------------------------------" << endl;
	if (!p.listOfTerritories.empty())
	{
		for (Territory* t : p.listOfTerritories)
		{
			out << t->getName() << endl;
		}
	}
	else
	{
		cout << "Player has no territories. \n" << endl; 
	}
	
	out << "\nPlayer's Order List: " << endl;
	out << "-----------------------" << endl;
	if (!p.listOfOrders->getOrders().empty())
	{
		for (Order* o : p.listOfOrders->getOrders())
		{
			out << o->getOrderName() << endl;
		}
	}
	else
	{
		cout << "Player has no orders in their list." << endl;
	}
	
	return out;
}

// Method to add territory pointers to a list of territories to defend
void Player::addTerritoryToDefend(Territory* t)
{
	listToDefend.push_back(t);
}

// Method to add territory pointers to a list of territories to attack
void Player::addTerritoryToAttack(Territory* t)
{
	listToAttack.push_back(t);
}

void Player::sortGreatestToLeastArmies()
{
	std::sort(listToAttack.begin(), listToAttack.end(), sortDescendingOrder);
	return;
};

void Player::sortLeastToGreatestArmies()
{
	std::sort(listToDefend.begin(), listToDefend.end(), sortAscendingOrder);
	return;
};

// Method to print the player's list of territories 
void Player::printListOfTerritories()
{
	cout << "\nPlayer " << getPosition() << "'s List of Territories: " << endl;
	cout << "-------------------------------------" << endl;
	if (!listOfTerritories.empty())
	{
		for (Territory* t : listOfTerritories)
		{
			cout << t->getName() << " - Armies: " << t->getArmy() << endl;
		}
	}
	else
	{
		cout << "Player" << getPosition() << " has no territories. \n" << endl;
	}
}

// Method to print the list of territories to defend
void Player::printToDefend()
{
	cout << "\nPlayer " << getPosition() << "'s List of Territories to Defend: " << endl;
	cout << "----------------------------------------" << endl;
	if (!listToDefend.empty())
	{
		for (Territory* t : listToDefend)
		{
			cout << t->getName() << " - Armies: " << t->getArmy() << endl;
		}
	}
	else
	{
		cout << "Player" << getPosition() << " has no territories to defend. \n" << endl;
	}
}

// Method to print the list of territories to attack
void Player::printToAttack()
{
	cout << "\nPlayer " << getPosition() << "'s List of Territories to Attack: " << endl;
	cout << "----------------------------------------" << endl;
	if (!listToAttack.empty())
	{
		for (Territory* t : listToAttack)
		{
			cout << t->getName() << " - Armies: " << t->getArmy() << endl;
		}
	}
	else
	{
		cout << "Player " << getPosition() << " has no territories to attack. \n" << endl;
	}
}

void Player::printNeighboringEnemyTerritories()
{
	cout << "\nPlayer " << getPosition() << "'s List of Neighboring Enemy Territories: " << endl;
	cout << "-------------------------------------------" << endl;
	if (!neighboringEnemyTerritories.empty())
	{
		for (Territory* t : neighboringEnemyTerritories)
		{
			cout << t->getName() << endl;
		}
	}
	else
	{
		cout << "Player " << getPosition() << " has no neighoring enemy territories. \n" << endl;
	}
};

vector<Territory*> Player::getNeighboringEnemyTerritories(Map* map)
{
	vector<int> sourceIndex{};

	for (int i = 0; i < listOfTerritories.size(); i++)
	{
		sourceIndex.push_back(listOfTerritories[i]->getID());
	}

	// Finds neighboring territory and adds it to the list
	for (int i = 0; i < sourceIndex.size(); i++)
	{
		for (int j = 0; j < map->getMapMatrix().size(); j++)
		{
			if (map->isConnected(sourceIndex[i], j))
			{
				if (neighboringEnemyTerritories.empty())
				{
					neighboringEnemyTerritories.push_back(map->getTerritoryList()[j]);
				}
				else
				{
					neighboringEnemyTerritories.push_back(map->getTerritoryList()[j]);
				}
			}
		}
	}

	std::sort(neighboringEnemyTerritories.begin(), neighboringEnemyTerritories.end());
	auto it = std::unique(neighboringEnemyTerritories.begin(), neighboringEnemyTerritories.end());
	neighboringEnemyTerritories.erase(it, neighboringEnemyTerritories.end());

	// If neighboring territory belongs to player, then it is removed from the list
	for (int i = 0; i < listOfTerritories.size(); i++)
	{
		for (int j = 0; j < neighboringEnemyTerritories.size(); j++)
		{
			if (listOfTerritories[i]->getID() == neighboringEnemyTerritories[j]->getID())
			{
				neighboringEnemyTerritories.erase(neighboringEnemyTerritories.begin() + j);
			}
		}
	}

	return neighboringEnemyTerritories;
}