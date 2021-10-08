#include "Order.h"
#include "Map.h"
#include "Player.h"
#include <algorithm>

using std::endl;
using std::to_string;

// Base class
Order::Order() {
}
//Destructor
Order::~Order() {
}
// copy constructor
Order::Order(const Order& order) {
	this->name = order.name;;
	this->isValidate = order.isValidate;
	this->player = order.player;
	this->sourceTerritory = order.sourceTerritory;
	this->targetTerritory = order.targetTerritory;
	this->territoryToDeploy = order.territoryToDeploy;
	this->numOfArmiesToDeploy = order.numOfArmiesToDeploy;
	this->playerName = order.playerName;
	this->orderIndex = order.orderIndex;
}
//Assignment Operator
Order& Order::operator=(const Order& order) {
	name = order.name;;
	isValidate = order.isValidate;
	player = order.player;
	sourceTerritory = order.sourceTerritory;
	targetTerritory = order.targetTerritory;
	territoryToDeploy = order.territoryToDeploy;
	numOfArmiesToDeploy = order.numOfArmiesToDeploy;
	playerName = order.playerName;
	orderIndex = order.orderIndex;
	return *this;
}
//Stream Insertion Operator
ostream& operator<<(ostream& out, const Order& order) {
	out << "Base Order Class" << endl;
	return out;
}

bool Order::validate() { return true; };
void Order::execute()
{
};

// Default constructor
Deploy::Deploy()
{
	name = "";
	isValidate = false;
	player = nullptr;
	sourceTerritory = nullptr;
	targetTerritory = nullptr;
	territoryToDeploy = nullptr;
	numOfArmiesToDeploy = 0;
	playerName = "";
	orderIndex = 0;
};

//Destructor
Deploy::~Deploy() {
}
// copy constructor
Deploy::Deploy(const Deploy& deploy) {
	this->name = deploy.name;;
	this->isValidate = deploy.isValidate;
	this->player = deploy.player;
	this->sourceTerritory = deploy.sourceTerritory;
	this->targetTerritory = deploy.targetTerritory;
	this->territoryToDeploy = deploy.territoryToDeploy;
	this->numOfArmiesToDeploy = deploy.numOfArmiesToDeploy;
	this->playerName = deploy.playerName;
	this->orderIndex = deploy.orderIndex;

}
//Assignment Operator
Deploy& Deploy::operator=(const Deploy& deploy) 
{
	name = deploy.name;;
	isValidate = deploy.isValidate;
	player = deploy.player;
	sourceTerritory = deploy.sourceTerritory;
	targetTerritory = deploy.targetTerritory;
	territoryToDeploy = deploy.territoryToDeploy;
	numOfArmiesToDeploy = deploy.numOfArmiesToDeploy;
	playerName = deploy.playerName;
	orderIndex = deploy.orderIndex;

	return *this;
}
//stream insertion operator
ostream& operator<<(ostream& out, const Deploy& deploy) {
	out << "Deploy Order" << endl;
	return out;
}

// Lisa's modifications
bool Deploy::validate()
{
	//Player* player = this->player;
	vector<Territory*> territoryList = player->getListOfTerritories();

	for (int i = 0; i < territoryList.size(); i++)
	{
		if (territoryToDeploy->getName() == territoryList[i]->getName())
		{
			return isValidate = true;
		}
	}
	cout << "Deploy order is invalid. " << endl;
	return isValidate = false;
}

void Deploy::execute() {

	Player* player = this->player;
	if (isValidate) {
		vector<Territory*> territoryList = player->getListOfTerritories();
		int randomArmy = numOfArmiesToDeploy;

		for (int i = 0; i < territoryList.size(); i++)
		{
			if (territoryToDeploy->getName() == territoryList[i]->getName())
			{
				territoryList[i]->setArmy(territoryList[i]->getArmy() + randomArmy);
			}
		}

		player->setReinforcementPool(player->getReinforcementPool() - randomArmy);

		if (player->getReinforcementPool() < 0)
		{
			player->setReinforcementPool(0);
		}
		
		player->notifyReinforce(numOfArmiesToDeploy, territoryToDeploy->getName(), player->getPlayerName());
		player->getListOfOrders()->remove(this);
	}
}

// Base class
Advance::Advance() {
}
//Destructor
Advance::~Advance() {
	
}
// copy constructor
Advance::Advance(const Advance& advance) {
	this->name = advance.name;;
	this->isValidate = advance.isValidate;
	this->player = advance.player;
	this->sourceTerritory = advance.sourceTerritory;
	this->targetTerritory = advance.targetTerritory;
	this->territoryToDeploy = advance.territoryToDeploy;
	this->numOfArmiesToDeploy = advance.numOfArmiesToDeploy;
	this->playerName = advance.playerName;
	this->orderIndex = advance.orderIndex;
}
//Assignment Operator
Advance& Advance::operator=(const Advance& advance) {
	name = advance.name;;
	isValidate = advance.isValidate;
	player = advance.player;
	sourceTerritory = advance.sourceTerritory;
	targetTerritory = advance.targetTerritory;
	territoryToDeploy = advance.territoryToDeploy;
	numOfArmiesToDeploy = advance.numOfArmiesToDeploy;
	playerName = advance.playerName;
	orderIndex = advance.orderIndex;

	return *this;
}
//Stream Insertion Operator
ostream& operator<<(ostream& out, const Advance& deploy) {
	out << "Advance Order" << endl;
	return out;
}

bool Advance::validate() {

	vector<Territory*> territoryList = player->getListOfTerritories();

	//Get the id of the territories
	int source = sourceTerritory->getID();
	int target = targetTerritory->getID();

	for (int i = 0; i < territoryList.size(); i++)
	{
		if (sourceTerritory->getName() == territoryList[i]->getName()) {
			if (player->getMap()->isConnected(source, target)) {
				cout << "Player " << player->getPosition() << "'s Advance Order on " << targetTerritory->getName() << " is valid. " << endl;
				return isValidate = true;
			}
		}
	}		
	return isValidate = false;
}

void Advance::execute()
{
	vector<Territory*> territoryList = player->getListOfTerritories();
	int defenderID = targetTerritory->getPlayer();
	//Player* defender = player->getPlayersList()[defenderID];
	Player* defender{};
	for (int i = 0; i < player->getPlayersList().size(); i++)
	{
		if (defenderID == player->getPlayersList()[i]->getPosition())
		{
			defender = player->getPlayersList()[i];
		}
	}
	//Player* defender = player->getPlayersList()[defenderID-1];

	if (isValidate) {
		if (player->getPosition() == defender->getPosition())
		{
			//Check if target territory is owned
			int transfer = sourceTerritory->getArmy() / 2;
			sourceTerritory->setArmy(sourceTerritory->getArmy() - transfer);
			targetTerritory->setArmy(targetTerritory->getArmy() + transfer);
			player->notifyDefense(sourceTerritory->getName(), targetTerritory->getName(), sourceTerritory->getArmy(), targetTerritory->getArmy(), "Player " + to_string(player->getPosition()));
		}
		else
		{
			int attack = sourceTerritory->getArmy();
			int defence = targetTerritory->getArmy();

			//if(defence)
			for (int z = 0; z < targetTerritory->getArmy(); z++) {
				//Creating random numbers
				int randomAttack = rand() % 100;
				int randomDefence = rand() % 100;

				if (randomAttack < 70) {
					defence--;
				}

				if (randomDefence < 60) {
					attack--;
				}
			}

			sourceTerritory->setArmy(attack);
			targetTerritory->setArmy(defence);

			//What happens when the target territory has 0 army 
			if (targetTerritory->getArmy() <= 0) 
			{
				for (int y = 0; y < defender->getListOfTerritories().size(); y++) 
				{
					if (defender->getListOfTerritories()[y]->getName() == targetTerritory->getName()) 
					{
						player->addTerritory(targetTerritory);
						defender->removeTerritory(y);
						targetTerritory->setPlayer(player->getPosition());
						targetTerritory->setArmy(0);
					}
				}
			}
			player->notifyAttack(sourceTerritory->getName(), targetTerritory->getName(), "Player " + to_string(defender->getPosition()), targetTerritory->getArmy(), sourceTerritory->getArmy(), sourceTerritory->getName(), targetTerritory->getArmy(), "Player " + to_string(player->getPosition()));
		}
	}
	else
	{
		cout << "Player " << player->getPosition() << "'s Advance Order on " << targetTerritory->getName() << " is not valid. " << endl;
	}
	
	player->getListOfOrders()->remove(this);
}

// OrdersList
// Base class
OrdersList::OrdersList() {
}
//Destructor
OrdersList::~OrdersList() {
}
// copy constructor
OrdersList::OrdersList(const OrdersList& ordersList) {
	this->orders = ordersList.orders;
}
//Assignment Operator
OrdersList& OrdersList::operator=(const OrdersList& ordersList) {
	orders = ordersList.orders;
	return *this;
}
//Stream Insertion Operator
ostream& operator<<(ostream& out, const OrdersList& ordersList) {
	out << "Player's OrderList" << endl;
	return out;
}

vector<Order*> OrdersList::getOrders()
{
	return orders;
};

void OrdersList::PrintOrders()
{
	cout << "Current orders:\n";
	for (int x = 0; x < orders.size(); x++)
	{
		cout << orders.at(x)->getOrderName() << "\n";;
	}
}

void OrdersList::addOrder(Order* o) {
	orders.push_back(o);
}

void OrdersList::remove(Order* removeOrder) {
	orders.erase(std::remove(orders.begin(), orders.end(), removeOrder), orders.end());
	orders.shrink_to_fit();
}

vector<Order*>::iterator OrdersList::findOrder(Order* order) {
	return find(orders.begin(), orders.end(), order);
}

Order* OrdersList::getAtIndex(const unsigned int index) const {
	return orders.at(index);
}

int OrdersList::getLength() const {
	return orders.size();
}

void OrdersList::move(Order* first, Order* second) {
	auto firstit = findOrder(first);
	auto secondit = findOrder(second);
	iter_swap(firstit, secondit);
}

void Order::setOrderName(string _name)
{
	name = _name;
}

string Order::getOrderName()
{
	return name;
}