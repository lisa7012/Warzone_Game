#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "GameObservers.h"
using namespace std;

class Territory
{
private:
	string _name;
	int _player;
	int _continentID;
	int _id;
	int _army;

public:
	Territory();
	Territory(int id, int army, int continentID, int player, string name);
	Territory(const Territory& territory);
	~Territory();

	//Getters
	string getName();
	int getPlayer();
	int getArmy();
	int getID();
	int getContinentID();

	//Setters
	void setPlayer(int player);
	void setArmy(int army);
};

class Continent
{
private:
	string _name;
	vector<Territory*> _territoryList;
	int _id;
	int _bonusArmies;

public:
	Continent();
	~Continent();
	Continent(string name, vector<Territory*> territoryList, int id);
	Continent(string name, vector<Territory*> territoryList, int id, int bonusArmies);
	Continent(const Continent& continent);

	//Getters
	string getName();
	int getID();
	
	int getBonusArmies() { return _bonusArmies; };
	vector<Territory*> getTerritoryList();

	void addTerritory(Territory* territory);
};

class Map : public StatisticSubject
{
private:
	vector<vector<int>> _mapMatrix;
	vector<Territory*> _territoryList;
	vector<Continent*> _continentList;

public:
	Map();
	Map(vector<vector<int>> mapMatrix, vector<Territory*> territoryList, vector<Continent*> continentList);
	Map(const Map& map);
	~Map();

	// Getters
	vector<vector<int>> getMapMatrix();
	vector<Territory*> getTerritoryList();
	vector<Continent*> getContinentList();

	void operator = (const Map& map);
	void displayMap();
	bool validate();

	bool isConnected(int source, int target);
};