#pragma once
#include <iostream>
#include <vector>

class Player;
class Map;
class ConcreteStatisticObserver;

using namespace std;

class GameEngine 
{
private:
	
	int _nbrOfPlayers;
	int _observer;
	int _initialArmy;
	string _mapName;
	vector<int> _playerOrder;

	vector<Player*> _playersList;
	bool _allPlayersFinishedOrders;
	bool _isWinner;
	ConcreteStatisticObserver* mapObserver;

	int _playWStrategy;

public:
	
	GameEngine();
	~GameEngine();
	GameEngine(const GameEngine& gameEngine);
	GameEngine& operator=(const GameEngine& gameEngine);
	friend ostream& operator<<(ostream& out, const GameEngine& gameEngine);

	//Getters
	int getNbrOfPlayers();
	int getObserver();
	int getInitialArmy();
	string getMapName();
	vector<int> getPlayerOrder();
	Map* getMap();

	//Setters
	void setNbrOfPlayers();
	void setMapName(string mapName);
	void setObserver();

	void mapSelect();
	void startupPhase();

	void mainGameLoop();
	void reinforcementPhase();
	void issueOrdersPhase();
	void executeOrdersPhase();
	vector<Player*> getPlayerList();

	void createPlayers(int _nbrOfPlayers);
	vector<int> territoriesInContinent();
	int getBonusArmiesFromContinent(int continentID);

	bool getAllPlayersFinishedOrders() { return _allPlayersFinishedOrders; };
	void setAllPlayersFinishedOrders(bool f) { _allPlayersFinishedOrders = f; };

protected:
	Map* gameMap;
};
