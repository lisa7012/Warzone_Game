#include "Map.h"

int nbrOfCountries = 0;
int nbrOfContinents = 0;

Territory::Territory() {} // Default Constructor

Territory::~Territory()  // Destructor
{

}

Territory::Territory(int id, int army, int continentID, int player, string name) // Constructor
{
	_name = name;
	_continentID = continentID;
	_id = id;
	_player = player;
	_army = army;
	nbrOfCountries++;
}

Territory::Territory(const Territory& territory) // Copy Constructor
	:_name(territory._name), _player(territory._player), _continentID(territory._continentID), _id(territory._id), _army(territory._army)
{
	cout << "Territory copied" << endl;
}

string Territory::getName()
{
	return _name;
}

int Territory::getContinentID()
{
	return _continentID;
}

int Territory::getPlayer()
{
	return _player;
}

int Territory::getArmy()
{
	return _army;
}

int Territory::getID()
{
	return _id;
}

void Territory::setPlayer(int player)
{
	_player = player;
}

void Territory::setArmy(int army)
{
	_army = army;
}

Continent::Continent() {} //Default Constructor

Continent::Continent(string name, vector<Territory*> territoryList, int id)	//Constructor
{
	_name = name;
	_territoryList = territoryList;
	_id = id;
}

Continent::Continent(string name, vector<Territory*> territoryList, int id, int bonusArmies)
{
	_name = name;
	_territoryList = territoryList;
	_id = id;
	_bonusArmies = bonusArmies;
};

Continent::Continent(const Continent& continent) //Copy Constructor
	: _name(continent._name), _territoryList(continent._territoryList)
{
	cout << "Continent copied" << endl;
}

Continent::~Continent()	//Destructor 
{

}

string Continent::getName()
{
	return _name;
}

int Continent::getID()
{
	return _id;
}

vector<Territory*> Continent::getTerritoryList()
{
	return _territoryList;
}

void Continent::addTerritory(Territory* territory)
{
	(_territoryList).push_back(territory);
}

Map::Map() 
{

} //Default Constructor

Map::Map(vector<vector<int>> mapMatrix, vector<Territory*> territoryList, vector<Continent*> continentList) // Constructor
{
	_territoryList = territoryList;
	_continentList = continentList;
	_mapMatrix = mapMatrix;

}

Map::Map(const Map& map) // Copy Constructor
	: _mapMatrix(map._mapMatrix), _territoryList(map._territoryList), _continentList(map._continentList)
{
	cout << "Map copied" << endl;
}

Map::~Map() // Destructor
{
	for (int i = 0; i < _continentList.size(); i++)
	{
		if (_continentList.at(i) != nullptr)
		{
			delete _continentList.at(i);
			_continentList.at(i) = nullptr;
		}
	}

	for (int i = 0; i < _territoryList.size(); i++)
	{
		if (_territoryList.at(i) != nullptr)
		{
			delete _territoryList.at(i);
			_territoryList.at(i) = nullptr;
		}
	}
}

vector<vector<int>> Map::getMapMatrix()
{
	return _mapMatrix;
}

vector<Territory*> Map::getTerritoryList()
{
	return _territoryList;
}

vector<Continent*> Map::getContinentList()
{
	return _continentList;
}

void Map::operator=(const Map& map) // Assignment Operator
{
	_mapMatrix = map._mapMatrix;
	_territoryList = vector<Territory*>(map._territoryList);
	_continentList = vector<Continent*>(map._continentList);
}

bool Map::validate() // Makes sure that the map is connected
{
	int count = 0;
	for (int i = 0; i < _mapMatrix.size(); i++)
	{
		for (int j = 0; j < _mapMatrix.size(); j++)
		{
			if (_mapMatrix[i][j] == 1)
			{
				count++;
			}
		}

		if (count == 0)
		{
			return false;
		}

		else
		{
			count = 0;
		}
	}
	return true;
}

void Map::displayMap() // Displays the matrix
{
	for (int i = 0; i < _mapMatrix.size(); i++)
	{
		for (int j = 0; j < _mapMatrix.size(); j++)
		{
			cout << _mapMatrix[i][j] << " ";
		}
		cout << endl;
	}
}

bool Map::isConnected(int source, int target)
{
	if (_mapMatrix[source][target] == 1)
	{
		return true;
	}

	return false;
}

