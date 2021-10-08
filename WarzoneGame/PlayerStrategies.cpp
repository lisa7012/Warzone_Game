#include "PlayerStrategies.h"
#include "Player.h"
#include "Map.h"
#include "Order.h"
#include <iostream>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;

// PlayerStrategy ==================================
// default constructor
PlayerStrategy::PlayerStrategy() 
{
	player = nullptr;
};

// destructor
PlayerStrategy::~PlayerStrategy()
{

}

// copy constructor
PlayerStrategy::PlayerStrategy(const PlayerStrategy& ps)
{
	this->player = ps.player;
};

// assignment operator
PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy& ps)
{
	this->player = ps.player;
	return *this;
}

// stream insertion operator
ostream& operator<<(ostream& out, const PlayerStrategy& ps)
{
	out << "Strategy: PlayerStrategy" << endl;
	return out;
}

// HumanPlayerStrategy Methods ===================
// default constructor
HumanPlayerStrategy::HumanPlayerStrategy()
{
	player = nullptr;
};

// destructor
HumanPlayerStrategy::~HumanPlayerStrategy()
{

}

// copy constructor
HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy& hps)
{
	this->player = hps.player;
};

// assignment operator
HumanPlayerStrategy& HumanPlayerStrategy::operator=(const HumanPlayerStrategy& hps)
{
	this->player = hps.player;
	return *this;
}

// stream insertion operator
ostream& operator<<(ostream& out, const HumanPlayerStrategy& hps)
{
	out << "Strategy: HumanPlayerStrategy" << endl;
	return out;
}

// HumanPlayerStrategy's version of issueOrder()
void HumanPlayerStrategy::issueOrder()
{
	string territory;
	int armies;
	int preArmiesPool = player->getPreArmiesPool();
	bool finishedDeploy = player->getFinishedDeploy();
	bool finishedAdvance = player->getFinishedAdvance();
	bool listHaveBeenDecided = player->getListsHaveBeenDecided();
	string input;
	int attackCount = 0;

	if (!listHaveBeenDecided)
	{
		toDefend();
		toAttack();
		player->setListsHaveBeenDecided(true);
	}
	
	if (preArmiesPool != 0)
	{
		cout << "\n(Human) Player " << player->getPosition() << "'s Reinforcement Pool: " << player->getPreArmiesPool() << " armies " << endl;
		player->printToDefend();
		cout << endl;

		cout << "(Human) Player " << player->getPosition() << ", which territory would you like to issue a deploy order? ";
		cin >> territory;
		cout << "How many armies would you like to deploy? ";
		cin >> armies;

		int territoryIndex = 0;
		for (int i = 0; i < player->getListToDefend().size(); i++)
		{
			if (territory == player->getListToDefend()[i]->getName())
			{
				territoryIndex = i;
				break;
			}
		}

		player->addOrderToList(new Deploy{});
		int preArmiesPool = player->getPreArmiesPool();
		
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setOrderName("Deploy");
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setTerritoryToDeploy(player->getListToDefend()[territoryIndex]);
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setNumOfArmiesToDeploy(armies);
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setPlayer(player);
		player->setPreArmiesPool(preArmiesPool - armies);

		return;
	}
	else
	if (!finishedDeploy)
	{
		finishedDeploy = true;
		player->setFinishedDeploy(true);
		player->setFinishedAdvance(true);
		cout << "\n==========>(Human) Player " << player->getPosition() << " has no more Deploy orders to issue." << " Reinforcement Pool: " << preArmiesPool << " armies<==========" << endl;
		return;
	}
	
	if (finishedAdvance)
	{
		cout << endl;
		cout << "(Human) Player " << player->getPosition() << ", would you like to issue an avance order? ";
		cin >> input;

		if (input == "yes")
		{
			cout << "(Human) Player " << player->getPosition() << ", is the advance order to defend or to attack? ";
			cin >> input;

			if (input == "defend")
			{
				player->printToDefend();
				cout << endl;
				cout << "(Human) Player " << player->getPosition() << ", which territory would you like to move armies from? ";
				cin >> territory;

				int sourceIndex = 0;
				for (int i = 0; i < player->getListOfTerritories().size(); i++)
				{
					if (territory == player->getListOfTerritories()[i]->getName())
					{
						sourceIndex = i;
						break;
					}
				}

				cout << "(Human) Player " << player->getPosition() << ", which territory would you like to move armies to? ";
				cin >> territory;
				cout << endl;

				int targetIndex = 0;
				for (int i = 0; i < player->getListToDefend().size(); i++)
				{
					if (territory == player->getListToDefend()[i]->getName())
					{
						targetIndex = i;
						break;
					}
				}

				player->addOrderToList(new Advance{});
				player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setOrderName("Advance");
				player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setSourceTerritory(player->getListToDefend()[sourceIndex]);
				player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setTargetTerritory(player->getListToDefend()[targetIndex]);
				player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setPlayer(player);
				cout << "An Advance order on " << player->getListToDefend()[targetIndex]->getName() << " (from toDefend()) is added to (Human) Player " << player->getPosition() << "'s list of orders." << endl;
				return;
			}

			if (input == "attack")
			{
				if (attackCount != 5)
				{
					player->printToAttack();
					cout << endl;
					cout << "(Human) Player " << player->getPosition() << ", which territory would you like to move armies from? ";
					cin >> territory;

					int sourceIndex = 0;
					for (int i = 0; i < player->getListOfTerritories().size(); i++)
					{
						if (territory == player->getListOfTerritories()[i]->getName())
						{
							sourceIndex = i;
							break;
						}
					}

					cout << "(Human) Player " << player->getPosition() << ", which territory would you like to move armies to? ";
					cin >> territory;
					cout << endl;

					int targetIndex = 0;
					for (int i = 0; i < player->getListToAttack().size(); i++)
					{
						if (territory == player->getListToAttack()[i]->getName())
						{
							targetIndex = i;
							break;
						}
					}

					player->addOrderToList(new Advance{});
					int newOrderIndex = player->getListOfOrders()->getLength() - 1;

					player->getListOfOrders()->getOrders()[newOrderIndex]->setOrderName("Advance");
					player->getListOfOrders()->getOrders()[newOrderIndex]->setSourceTerritory(player->getListToDefend()[sourceIndex]);
					player->getListOfOrders()->getOrders()[newOrderIndex]->setTargetTerritory(player->getListToDefend()[targetIndex]);
					player->getListOfOrders()->getOrders()[newOrderIndex]->setPlayer(player);
					cout << "An Advance order on " << player->getListToAttack()[targetIndex]->getName() << " (from toAttack()) is added to (Human) Player " << player->getPosition() << "'s list of orders." << endl;
					attackCount++;
					return;
				}
				else
				{
					cout << "No more attacks can be made. " << endl;
				}
			}
		}
		else
		{
			cout << "\n(Human) Player " << player->getPosition() << " has finished issuing their orders. " << endl;
			finishedAdvance = false;
			player->setListsHaveBeenDecided(false);
			player->setFinishedAdvance(false);
			player->setFinishedOrders(true);
			return;
		}
	}
}

//HumanPlayerStrategy's version of toDefend()
vector<Territory*> HumanPlayerStrategy::toDefend()
{
	// If listToDefend is not empty, clear the list to start a new list
	if (!player->getListToDefend().empty())
	{
		player->clearToDefend();
	}

	// Prints player's list of territories for them to choose
	player->printListOfTerritories();
	cout << endl;
	string input;
	bool isValid = false;
	bool found = false;
	
	while (true)
	{
		cout << "(Human) Player " << player->getPosition() << ", which territory/territories would you like to defend? ";
		cin >> input;

		// If player writes "all", all of their territories are added to the player's listToDefend
		if (input == "all")
		{
			for (int i = 0; i < player->getListOfTerritories().size(); i++)
			{
				player->addTerritoryToDefend(player->getListOfTerritories()[i]);
			}

			cout << "\nAll territories you own have been added to your list to defend. " << endl;
			break;
		}
		else
		{
			// Check if the input is a valid territory in the map
			for (int i = 0; i < player->getMap()->getTerritoryList().size(); i++)
			{
				if (input == player->getMap()->getTerritoryList()[i]->getName())
				{
					isValid = true;
					break;
				}
			}

			// If it is invalid, a message is displayed and the player is asked again
			if (!isValid) { cout << "Invalid territory. " << endl; continue; }
			else 
			{
				// If the valid territory does not belong to the current player, a message is displayed and the player is asked again
				for (int i = 0; i < player->getListOfTerritories().size(); i++)
				{
					if (input == player->getListOfTerritories()[i]->getName())
					{
						player->addTerritoryToDefend(player->getListOfTerritories()[i]);
						cout << player->getListOfTerritories()[i]->getName() << " has been added to your list to defend. " << endl;
						found = true;
						break;
					}
				}

				if (!found) { cout << "Territory does not belong to you. " << endl; continue; }
			}

			// Player is asked if they would like to add another terrtitory to their listToDefend
			cout << "Would you like to add another territory? ";
			cin >> input;

			if (input == "yes")
			{ continue; }
			else
			{
				break;
			}
		}
	}

	player->printToDefend();
	return player->getListToDefend();
}

// HumanPlayerStrategy's version of toAttack()
vector<Territory*> HumanPlayerStrategy::toAttack()
{
	// If listToAttack and list of neigboring enemies is not empty, clear the lists to start new lists
	if (!player->getListToAttack().empty() || !player->getListOfNeighboringEnemies().empty())
	{
		player->clearNeighboringEnemies();
		player->clearToAttack();
	}

	// Prints player's list of enemy neighboring territories for them to choose
	player->getNeighboringEnemyTerritories(player->getMap());
	player->printNeighboringEnemyTerritories();
	cout << endl;
	string input;
	bool isValid = false;
	bool found = false;

	while (true)
	{
		cout << "(Human) Player " << player->getPosition() << ", which territory/territories would you like to attack? ";
		cin >> input;

		// If player writes "all", all of their territories are added to the player's listToAttack
		if (input == "all")
		{
			for (int i = 0; i < player->getListOfNeighboringEnemies().size(); i++)
			{
				player->addTerritoryToAttack(player->getListOfNeighboringEnemies()[i]);
			}

			cout << "\nAll territories you own have been added to your list to attack. " << endl;
			break;
		}
		else
		{
			// Check if the input is a valid territory in the map
			for (int i = 0; i < player->getMap()->getTerritoryList().size(); i++)
			{
				if (input == player->getMap()->getTerritoryList()[i]->getName())
				{
					isValid = true;
					break;
				}
			}

			// If it is invalid, a message is displayed and the player is asked again
			if (!isValid) { cout << "Invalid territory. " << endl; continue; }
			else
			{
				for (int i = 0; i < player->getListOfNeighboringEnemies().size(); i++)
				{
					// If the valid territory is not a neighboring enemy territory, a message is displayed and the player is asked again
					if (input == player->getListOfNeighboringEnemies()[i]->getName())
					{
						player->addTerritoryToAttack(player->getListOfNeighboringEnemies()[i]);
						cout << player->getListOfNeighboringEnemies()[i]->getName() << " has been added to your list to attack. " << endl;
						found = true;
						break;
					}
				}

				if (!found) { cout << "Territory is not an enemy neighboring territory. " << endl; continue; }
			}

			// Player is asked if they would like to add another terrtitory to their listToAttack
			cout << "Would you like to add another territory? ";
			cin >> input;

			if (input == "yes")
			{ continue; }
			else
			{ break; }
		}
	}
	player->printToAttack();
	return player->getListToAttack();
}


// AggressivePlayerStrategy Methods ===================
// default constructor
AggressivePlayerStrategy::AggressivePlayerStrategy()
{
	player = nullptr;
};

// destructor
AggressivePlayerStrategy::~AggressivePlayerStrategy()
{

}

// copy constructor
AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy& aps)
{
	this->player = aps.player;
};

// assignment operator
AggressivePlayerStrategy& AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy& aps)
{
	this->player = aps.player;
	return *this;
}

// stream insertion operator
ostream& operator<<(ostream& out, const AggressivePlayerStrategy& aps)
{
	out << "Strategy: AggressivePlayerStrategy" << endl;
	return out;
}

// AggressivePlayerStrategy's version of issueOrder()
void AggressivePlayerStrategy::issueOrder()
{
	int preArmiesPool = player->getPreArmiesPool();
	bool finishedDeploy = player->getFinishedDeploy();
	bool finishedAdvance = player->getFinishedAdvance();
	int deployCounter = player->getDeployCounter();
	int defendCounter = player->getDefendCounter();
	int attackCounter = player->getAttackCounter();
	bool listHaveBeenDecided = player->getListsHaveBeenDecided();

	if (!listHaveBeenDecided)
	{
		toDefend();
		toAttack();
		player->setListsHaveBeenDecided(true);
	}
	
	//Issues deploy orders as long as there is still armies in the reinforcementPool 
	if (preArmiesPool != 0)
	{
		player->addOrderToList(new Deploy{});
		int preArmiesPool = player->getPreArmiesPool();
		int sourceID = player->getListToDefend()[deployCounter]->getID();
		bool connect = false;

		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setOrderName("Deploy");
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setTerritoryToDeploy(player->getListToDefend()[deployCounter]);
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setNumOfArmiesToDeploy(preArmiesPool);
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setPlayer(player);
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setPlayerName("Player " + player->getPosition());
		cout << "A Deploy order on " << player->getListToDefend()[deployCounter]->getName() << " has been added to (Aggressive) Player " << player->getPosition() << "'s list of orders." << endl;
		player->setStrongestTerritory(player->getListToDefend()[deployCounter]);
		player->setPreArmiesPool(preArmiesPool - preArmiesPool);

		player->setDeployCounter(player->getDeployCounter() + 1);
		if (player->getDeployCounter() >= player->getListToDefend().size() - 1)
		{
			player->setDeployCounter(0);
		}
		return;
	}
	else if (!finishedDeploy)
	{
		player->setDeployCounter(0);
		finishedDeploy = true;
		player->setFinishedDeploy(true);
		cout << "==========>(Aggressive) Player " << player->getPosition() << " has no more Deploy orders to issue." << " Reinforcement Pool: " << player->getPreArmiesPool() << " armies<==========" << endl;
		return;
	}
	else
	// ISSUE ADVANCE ORDER =====================================================================
	if (attackCounter < player->getListToAttack().size())
	{
		player->addOrderToList(new Advance{});

		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setOrderName("Advance");
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setSourceTerritory(player->getStrongestTerritory());
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setTargetTerritory(player->getListToAttack()[attackCounter]);
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setPlayer(player);
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setPlayerName("Player " + player->getPosition());
		cout << "An Advance order on " << player->getListToAttack()[attackCounter]->getName() << " is added to (Aggressive) Player " << player->getPosition() << "'s list of orders." << endl;
		player->setAttackCounter(player->getAttackCounter() + 1);
	
		return;
	}
	else if (!finishedAdvance)
	{
		cout << "(Aggressive) Player " << player->getPosition() << " has finished issuing their orders. " << endl;
		player->setDefendCounter(0);
		player->setAttackCounter(0);
		player->setListsHaveBeenDecided(false);
		player->setFinishedAdvance(true);
		player->setFinishedOrders(true);
		return;
	}
};

//AggressivePlayerStrategy's version of toDefend()
vector<Territory*> AggressivePlayerStrategy::toDefend()
{
	//Clearing the list every turn 
	if (!player->getListToDefend().empty())
	{
		player->clearToDefend();
	}

	player->sortGreatestToLeastArmies();

	//Add all the territory which need to be defend
	for (int i = 0; i < player->getListOfTerritories().size(); i++)
	{
		player->addTerritoryToDefend((player->getListOfTerritories()[i]));
	}

	player->printToDefend();

	return player->getListToDefend();
}

// AggressivePlayerStrategy's version of toAttack()
vector<Territory*> AggressivePlayerStrategy::toAttack()
{
	// If listToAttack and list of neigboring enemies is not empty, clear the lists to start new lists
	if (!player->getListToAttack().empty() || !player->getListOfNeighboringEnemies().empty())
	{
		player->clearNeighboringEnemies();
		player->clearToAttack();
	}

	player->getNeighboringEnemyTerritories(player->getMap());

	// If there are neighboring enemy territories
	if (player->getListOfNeighboringEnemies().size() != 0)
	{
		for (int i = 0; i < player->getListOfNeighboringEnemies().size(); i++)
		{
			player->addTerritoryToAttack(player->getListOfNeighboringEnemies()[i]);
		}
	}

	player->printToAttack();
	cout << endl;

	return player->getListToAttack();
}


// BenevolentPlayerStrategy Methods ===================
// default constructor
BenevolentPlayerStrategy::BenevolentPlayerStrategy()
{
	player = nullptr;
};

// destructor
BenevolentPlayerStrategy::~BenevolentPlayerStrategy()
{

}

// copy constructor
BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy& bps)
{
	this->player = bps.player;
};

// assignment operator
BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy& bps)
{
	this->player = bps.player;
	return *this;
}

// stream insertion operator
ostream& operator<<(ostream& out, const BenevolentPlayerStrategy& bps)
{
	out << "Strategy: BenevolentPlayerStrategy" << endl;
	return out;
}

// BenevolentPlayerStrategy's version of issueOrder()
void BenevolentPlayerStrategy::issueOrder()
{
	int preArmiesPool = player->getPreArmiesPool();
	bool finishedDeploy = player->getFinishedDeploy();
	bool finishedAdvance = player->getFinishedAdvance();
	int deployCounter = player->getDeployCounter();
	int defendCounter = player->getDefendCounter();
	bool listHaveBeenDecided = player->getListsHaveBeenDecided();

	if (!listHaveBeenDecided)
	{
		toDefend();
		toAttack();
		player->setListsHaveBeenDecided(true);
	}

	//Issues deploy orders as long as there is still armies in the reinforcementPool 
	if (preArmiesPool != 0)
	{
		int randomArmy = 1;
		int preArmiesPool = player->getPreArmiesPool();
		player->addOrderToList(new Deploy{});
		
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setOrderName("Deploy");
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setTerritoryToDeploy(player->getListToDefend()[deployCounter]);
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setNumOfArmiesToDeploy(randomArmy);
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setPlayer(player);
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setPlayerName("Player " + player->getPosition());
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setOrderIndex(deployCounter);
		cout << "A Deploy order on " << player->getListToDefend()[deployCounter]->getName() << " has been added to (Benevolent) Player " << player->getPosition() << "'s list of orders." << endl;
		player->setPreArmiesPool(preArmiesPool - randomArmy);

		player->setDeployCounter(player->getDeployCounter()+1);
		if (player->getDeployCounter() >= player->getListToDefend().size() - 1)
		{
			player->setDeployCounter(0);
		}
		return;
	}
	else if (!finishedDeploy)
	{
		player->setDeployCounter(0);
		finishedDeploy = true;
		player->setFinishedDeploy(true);		
		cout << "==========>(Benevolent) Player " << player->getPosition() << " has no more Deploy orders to issue." << " Reinforcement Pool: " << player->getPreArmiesPool() << " armies<==========" << endl;
		return;
	}
	else
	// ISSUE ADVANCE ORDER =====================================================================
	if (defendCounter < player->getListToDefend().size())
	{	
		//Getting a random source territory
		int randomSource = rand() % player->getListOfTerritories().size();

		player->addOrderToList(new Advance{});
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setOrderName("Advance");
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setSourceTerritory(player->getListOfTerritories()[randomSource]);
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setTargetTerritory(player->getListToDefend()[defendCounter]);
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setPlayer(player);
		player->getListOfOrders()->getOrders()[player->getListOfOrders()->getLength() - 1]->setPlayerName("Player " + player->getPosition());
		cout << "An Advance order on " << player->getListToDefend()[defendCounter]->getName() << " is added to (Benevolent) Player " << player->getPosition() << "'s list of orders." << endl;
		player->setDefendCounter(player->getDefendCounter()+1);
		return;
	}
	else
	if (!finishedAdvance)
	{
		cout << "(Benevolent) Player " << player->getPosition() << " has finished issuing their orders. " << endl;
		player->setDefendCounter(0);
		player->setListsHaveBeenDecided(false);
		player->setFinishedAdvance(true);
		player->setFinishedOrders(true);
		return;
	}
}

//BenevolentPlayerStrategy's version of toDefend()
vector<Territory*> BenevolentPlayerStrategy::toDefend()
{
	// If listToDefend is not empty, clear the list to start a new list
	if (!player->getListToDefend().empty())
	{
		player->clearToDefend();
	}
	
	//Adding territory to defend if army is less than 5
	for (int i = 0; i < player->getListOfTerritories().size(); i++)
	{
		if (player->getListOfTerritories()[i]->getArmy() <= 5) {
			player->addTerritoryToDefend((player->getListOfTerritories()[i]));
		}
	}

	int counter = 0;
	//Adding territory to defend by least army
	if (player->getListToDefend().size() == 0) {
		player->sortLeastToGreatestArmies();
		for (int i = 0; i < player->getListOfTerritories().size(); i++)
		{
			player->addTerritoryToDefend((player->getListOfTerritories()[i]));
			counter++;
			if (counter <= 3) {
				break;
			}
		}
	}

	player->sortLeastToGreatestArmies();
	player->printToDefend();

	return player->getListToDefend();
}

// BenevolentPlayerStrategy's version of toAttack()
vector<Territory*> BenevolentPlayerStrategy::toAttack()
{
	cout << "\n(Benevolent) Player " << player->getPosition() << " is a benevolent player, which does not attack any territories.\n" << endl;
	return player->getListToAttack();
}


// NeutralPlayerStrategy Methods ===================
// default constructor
NeutralPlayerStrategy::NeutralPlayerStrategy()
{
	player = nullptr;
};

// destructor
NeutralPlayerStrategy::~NeutralPlayerStrategy()
{

}

// copy constructor
NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& nps)
{
	this->player = nps.player;
};

// assignment operator
NeutralPlayerStrategy& NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy& nps)
{
	this->player = nps.player;
	return *this;
}

// stream insertion operator
ostream& operator<<(ostream& out, const NeutralPlayerStrategy& bps)
{
	out << "Strategy: NeutralPlayerStrategy" << endl;
	return out;
}

// NeutralPlayerStrategy's version of issueOrder()
void NeutralPlayerStrategy::issueOrder()
{
	cout << "(Neutral) Player " << player->getPosition() << " is a neutral player, which does not issue any order." << endl;
	player->setFinishedOrders(true);
	return;
}

// NeutralPlayerStrategy's version of toDefend()
vector<Territory*> NeutralPlayerStrategy::toDefend()
{
	cout << "(Neutral) Player " << player->getPosition() << " is a neutral player, which does not defend any territory." << endl;
	return player->getListToDefend();
}

// NeutralPlayerStrategy's version of toAttack()
vector<Territory*> NeutralPlayerStrategy::toAttack()
{
	cout << "(Neutral) Player " << player->getPosition() << " is a neutral player, which does not attack any territories." << endl;
	return player->getListToAttack();
}

