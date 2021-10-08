#pragma once
#include "GameEngine.h"
#include "MapLoader.h"
#include "Map.h"
#include "Player.h"
#include "GameObservers.h"
#include <math.h>

GameEngine::GameEngine()
{
	_mapName = " ";
	_nbrOfPlayers = 2;
	_observer = 0;
	_allPlayersFinishedOrders = false;
	_isWinner = false;
}

GameEngine::~GameEngine() //Destructor 
{
	for (int i = 0; i < _playersList.size(); i++)
	{
		_playersList[i] = nullptr;
	}
	_playerOrder.clear();

	gameMap = nullptr;
}

GameEngine::GameEngine(const GameEngine& gameEngine) //Copy Constructor
	:_mapName(gameEngine._mapName), _nbrOfPlayers(gameEngine._nbrOfPlayers), _observer(gameEngine._observer), _initialArmy(gameEngine._initialArmy), _playerOrder(gameEngine._playerOrder),
	_playersList(gameEngine._playersList)
{
	cout << "Game engine copied." << endl;
}

GameEngine& GameEngine::operator=(const GameEngine& gameEngine) //Assignment Operator
{
	_mapName = gameEngine._mapName;
	_nbrOfPlayers = gameEngine._nbrOfPlayers;
	_observer = gameEngine._observer;
	_initialArmy = gameEngine._initialArmy;
	_playerOrder = gameEngine._playerOrder;
	_playersList = gameEngine._playersList;
	return *this;
}

ostream& operator<<(ostream& out, const GameEngine& gameEngine) //Stream Insertion Operator
{
	out << gameEngine._mapName;
	out << gameEngine._nbrOfPlayers;
	out << gameEngine._observer;
	out << gameEngine._initialArmy;
	for (int i = 0; i < gameEngine._playerOrder.size(); i++)
	{
		out << gameEngine._playerOrder[i];
	}

	for (int i = 0; i < gameEngine._playersList.size(); i++)
	{
		out << gameEngine._playersList[i];
	}
	
	return out;
}

void GameEngine::mapSelect()
{
	string userMapChoice;
	MapLoader* mapLoad;
	while (true) {
		cout << "Please select a map: ";
		cin >> userMapChoice;
		mapLoad = new MapLoader(userMapChoice);
		gameMap = mapLoad->parseDominationMap();


		if (mapLoad->getValidMap() == true) {
			setMapName(userMapChoice);
			break;
		}

		else {
			cout << "Invalid Map. Try again." << endl;
			continue;
		}
	}

	delete mapLoad;
	mapLoad = nullptr;
	
}

void GameEngine::setMapName(string mapName)
{
	_mapName = mapName;
}

string GameEngine::getMapName()
{
	return _mapName;
}

void GameEngine::setNbrOfPlayers()
{
	int nbrOfplayers;
	while (true)
	{
		cout << "Please enter the number of players: ";
		cin >> nbrOfplayers;
		if (nbrOfplayers < 2 || nbrOfplayers > 5)
		{
			cout << "Invalid number. Please try again." << endl;;
			continue;
		}
		else
		{
			break;
		}
	}
	_nbrOfPlayers = nbrOfplayers;
}

int GameEngine::getNbrOfPlayers()
{
	return _nbrOfPlayers;
}

static int observer;

void GameEngine::setObserver()
{
	while (true)
	{
		cout << "Please press 0 to disable Observers or press 1 to enable Observers: ";
		cin >> observer;  cout << endl;

		if (observer == 0)
		{
			cout << "Observer has been disabled." << endl;
			mapObserver = nullptr;
			break;
		}

		else if (observer == 1)
		{
			cout << "Observer has been enabled." << endl;
			mapObserver = new ConcreteStatisticObserver(gameMap, this);
			break;
		}

		else
		{
			cout << "Invalid choice. Please try again." << endl;;
			continue;
		}
	}
	_observer = observer;
}

int GameEngine::getObserver()
{
	return _observer; // 0 -> disabled, 1 -> enabled
}

void GameEngine::startupPhase()
{
	//Randomizing player order
	srand(unsigned(time(0)));
	vector<int> playerOrder;
	for (int i = 1; i <= getNbrOfPlayers(); i++)
	{
		playerOrder.push_back(i);
	}
	random_shuffle(playerOrder.begin(), playerOrder.end());
	_playerOrder = playerOrder;

	//Assigning Territories to players

	createPlayers(_nbrOfPlayers);

	vector<Territory*> territoryList = gameMap->getTerritoryList();

	int j = 0;
	for (int i = 0; i < territoryList.size(); i++)
	{
		territoryList[i]->setPlayer(playerOrder[j]); 
		
		for (int k = 0; k < _playersList.size(); k++)
		{
			if (_playersList[k]->getPosition() == playerOrder[j]) {
				_playersList[k]->addTerritory(territoryList[i]);
			}
		}

		j++;
		if (j == playerOrder.size())
		{
			j = 0;
		}
	}

	//Initial Armies   
	if (getNbrOfPlayers() == 2)
	{
		//_initialArmy = 40;
		_initialArmy = 10;
		
		for (int i = 0; i < _playersList.size(); i++) {
			_playersList[i]->setReinforcementPool(_initialArmy);
		}
		
	}

	else if (getNbrOfPlayers() == 3)
	{
		_initialArmy = 35;
		for (int i = 0; i < _playersList.size(); i++) {
			_playersList[i]->setReinforcementPool(_initialArmy);
		}
	}

	else if (getNbrOfPlayers() == 4)
	{
		_initialArmy = 30;
		for (int i = 0; i < _playersList.size(); i++) {
			_playersList[i]->setReinforcementPool(_initialArmy);
		}
	}

	else if (getNbrOfPlayers() == 5)
	{
		_initialArmy = 25;
		for (int i = 0; i < _playersList.size(); i++) {
			_playersList[i]->setReinforcementPool(_initialArmy);
		}
	}
}

vector<int> GameEngine::getPlayerOrder()
{
	return _playerOrder;
}

int GameEngine::getInitialArmy()
{
	return _initialArmy;
}

Map* GameEngine::getMap()
{
	return gameMap;
}

vector<Player*> GameEngine::getPlayerList()
{
	return _playersList;
}

void GameEngine::mainGameLoop()
{
	int counter = 0;
	while (!_isWinner)
	{
		// Hardcoded to show winner
		counter++;
		if (counter == 5)
		{
			int size0 = _playersList[0]->getListOfTerritories().size();
			int size1 = _playersList[1]->getListOfTerritories().size();
			int position = 0;
			for (int i = 0; i < size0; i++)
			{
				_playersList[0]->removeTerritory(position);
			}
			for (int i = 0; i < size1; i++)
			{
				_playersList[1]->removeTerritory(position);
			}

			for (int i = 0; i < gameMap->getTerritoryList().size(); i++)
			{
				_playersList[1]->addTerritory(gameMap->getTerritoryList()[i]);
			}
			
			if (_playersList[0]->getListOfTerritories().empty())
			{
				_playersList.erase(_playersList.begin());
			}

			mapObserver->display();
			break;
		}

		for (int i = 0; i < _playersList.size(); i++)
		{
			if (_playersList[i]->getListOfTerritories().empty())
			{
				_playersList.erase(_playersList.begin() + i);
			}
		}

		reinforcementPhase();
		issueOrdersPhase();
		executeOrdersPhase();

		cout << "\n=========================================================================================\n" << endl;
		if (mapObserver != nullptr) mapObserver->display();
		cout << "=========================================================================================\n" << endl;

		for (int i = 0; i < _playersList.size(); i++)
		{
			if (_playersList[i]->getListOfTerritories().size() == gameMap->getTerritoryList().size())
			{
				cout << "Winner found!" << endl;
				_isWinner = true;
			}
		}
	}	
};

// A method that creates players for the game and stores them in a list
void GameEngine::createPlayers(int _nbrOfPlayers)
{
	for (int i = 1; i <= _nbrOfPlayers; i++)
	{
		_playersList.push_back(new Player{ "Player " + std::to_string(_playerOrder[i-1]) });
	}

	for (int i = 0; i < _playersList.size(); i++)
	{
		_playersList[i]->setPosition(_playerOrder[i]);
		_playersList[i]->setMap(gameMap);
		_playersList[i]->setPlayersList(_playersList);
		if (observer == 1)
		{
			ConcretePhaseObserver* playerObserver = new ConcretePhaseObserver(_playersList[i]);
		}
	}
};

// A method that returns a list that indicates the number of territories for each continent 
vector<int> GameEngine::territoriesInContinent()
{
	MapLoader* mapLoad = new MapLoader(_mapName);
	gameMap = mapLoad->parseDominationMap();
	vector<int> territoryForContinent;
	int territoryIDCounter = 0;
	int continentID = 0;
	
	for (int i = 0; i < gameMap->getContinentList().size(); i++)
	{
		territoryIDCounter = 0;
		
		for (int j = 0; j < gameMap->getTerritoryList().size(); j++)
		{
			if(gameMap->getContinentList()[i]->getID() == gameMap->getTerritoryList()[j]->getID())
			{
				territoryIDCounter++;
			}
		}

		territoryForContinent.push_back(territoryIDCounter);
	}

	// Delete pointers to avoid memory leak here
	delete mapLoad;
	mapLoad = nullptr;

	return territoryForContinent;
}

// A method to retrieve the bonus armies from a specific continent
int GameEngine::getBonusArmiesFromContinent(int continentID)
{
	MapLoader* mapLoad = new MapLoader(_mapName);
	gameMap = mapLoad->parseDominationMap();
	
	vector<Continent*> continentList = gameMap->getContinentList();
	int bonusArmies = 0;

	for (int i = 0; i < continentList.size(); i++)
	{
		if (continentList[i]->getID() == continentID)
		{
			bonusArmies = continentList[i]->getBonusArmies();
			return bonusArmies;
		}
	}

	// Delete pointers to avoid memory leak here
	delete mapLoad;
	mapLoad = nullptr;

	return bonusArmies;
}

void GameEngine::reinforcementPhase()
{
	int numOfArmies = 0;
	const int MINIMUM_NUM_ARMIES = 3;
	int numOfTerritories = 0;
	int territoryCounter = 0;
	bool ownsContinent = false;
	int bonusArmies = 0;

	cout << "\nReinforcement Phase" << endl;
	cout << "======================" << endl;

	// Going through the list of players to assign armies to reinforcement pool for each player
	for (int i = 0; i < _playersList.size(); i++)
	{
		numOfArmies = 0;
		// Gets the number of territories from the player's list of territories
		numOfTerritories = _playersList[i]->getListOfTerritories().size();
		// Calls a method to get a list that indicates the number of territories for each continent 
		vector<int> territoryContinentIDs = territoriesInContinent();
		
		// Going through the given list to check if player owns a continent
		for (int j = 0; j < territoryContinentIDs.size(); j++)
		{
			// Going through the player's list of territories
			for (int k = 0; k < numOfTerritories; k++)
			{
				// Everytime a territory's continentID matches a continentID, a counter is incremented
				if (_playersList[i]->getListOfTerritories()[k]->getContinentID() == j+1)
				{
					territoryCounter++;
				}
			}

			/* If the counter is equal to the number of territories that the current continentID has, then the player owns the continent 
			 and they gain the continent's bonus armies */
			if (territoryCounter == territoryContinentIDs[j])
			{
				bool ownsContinent = true;
				bonusArmies = getBonusArmiesFromContinent(j+1);
				numOfArmies += bonusArmies;
			}
		}

		// The number of armies is then calculated with the number of territories they own
		numOfArmies += floor(numOfTerritories / 3);

		if (numOfArmies < 3)
		{
			numOfArmies = MINIMUM_NUM_ARMIES;
		}
		
		if (_playersList[i]->getFirstPool() == 0)
		{
			_playersList[i]->setReinforcementPool(_playersList[i]->getReinforcementPool() + numOfArmies);
			_playersList[i]->setPreArmiesPool(_playersList[i]->getReinforcementPool());
			_playersList[i]->setFirstPool(false);
		}
		else
		{
			_playersList[i]->setReinforcementPool(numOfArmies);
			_playersList[i]->setPreArmiesPool(_playersList[i]->getReinforcementPool());
		}
		
		cout << "\nPlayer " << _playersList[i]->getPosition() << " has " << _playersList[i]->getReinforcementPool() << " armies in their reinforcement pool." << endl;
		cout << "Player has " << numOfTerritories << " territories. \n" << endl;
	}
};

void GameEngine::issueOrdersPhase()
{
	cout << "\nOrders Issuing Phase" << endl;
	cout << "=======================" << endl;
	// Implement round-robin fashion

	int _finishedCounter = 0;
	bool _playersFinished = false;
	while (!_allPlayersFinishedOrders)
	{
		_finishedCounter = 0;
		for (int i = 0; i < _playersList.size(); i++)
		{
			if (!_playersList[i]->getFinishedOrders())
			{
				_playersList[i]->issueOrder();
			}
		}

		for (int i = 0; i < _playersList.size(); i++)
		{
			if (_playersList[i]->getFinishedOrders())
			{
				_finishedCounter++;
			}
		}

		if (_finishedCounter == _nbrOfPlayers)
		{
			for (int i = 0; i < _playersList.size(); i++)
			{
				_playersList[i]->setFinishedDeploy(false);
				_playersList[i]->setFinishedAdvance(false);
				_playersList[i]->setFinishedOrders(false);
			}
			_allPlayersFinishedOrders = true;
		}
	}	
	_allPlayersFinishedOrders = false;
	cout << "\nEnd of Orders Issuing Phase" << endl;
};

void GameEngine::executeOrdersPhase()
{
	cout << "\nExecute Orders Phase" << endl;
	cout << "=======================" << endl;

	OrdersList* masterOrderList = new OrdersList();
	vector<OrdersList*> playerOrdersList;

	for (int x = 0; x < _nbrOfPlayers; x++)
	{
		playerOrdersList.push_back(_playersList.at(x)->getListOfOrders());
	}
	
	vector<Player*> finishedPlayers;
	while (finishedPlayers.size() < _nbrOfPlayers)
	{
		int counter = 0;
		for (int x = 0; x < _nbrOfPlayers; x++)
		{
			int currentPlayerID = _playersList.at(x)->getPosition();
			if (playerOrdersList.at(x)->isEmpty())
			{
				bool exists = false;
				for (int f = 0; f < finishedPlayers.size(); f++)
				{
					if (finishedPlayers[f]->getPosition() == currentPlayerID) exists = true;
					break;
				}
				if (!exists) finishedPlayers.push_back(_playersList.at(x));
				continue;
			}

			masterOrderList->addOrder(playerOrdersList.at(x)->getAtIndex(counter));
			playerOrdersList.at(x)->remove(playerOrdersList.at(x)->getAtIndex(counter));

		}
	}

	for (int o = 0; o < masterOrderList->getLength(); o++)
	{
		masterOrderList->getOrders()[o]->validate();
		masterOrderList->getOrders()[o]->execute();
	}

	for (int p = 0; p < _nbrOfPlayers; p++)
	{
		cout << _playersList[p]->getPlayerName() << " has " << _playersList[p]->getListOfOrders()->getLength() << " orders left.\n";
	}
};