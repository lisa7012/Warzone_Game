//
//#include <iostream>
//#include <string>
//#include "Map.h"
//#include "Player.h"
//#include "GameEngine.h"
//
//int main()
//{
//	cout << "-------------------------------------------------\n" <<
//	    "                     Game Start                \n" <<
//	    "-------------------------------------------------\n\n";
//	GameEngine gameEngine;
//	//Testing Map Select."
//	gameEngine.mapSelect();
//
//	//Testing number of player set.
//	gameEngine.setNbrOfPlayers();
//
//	//Testing observer on/off
//	gameEngine.setObserver();
//
//	cout << "\nHere are the settings of the Game Engine.\nNumber of Players: " << gameEngine.getNbrOfPlayers() << endl;
//	cout << "Map name: ";
//	cout<< gameEngine.getMapName() << endl;
//
//	if (gameEngine.getObserver() == 0) {
//		cout << "Observer is disabled." << endl;
//	}
//	else {
//		cout << "Observer is enabled." << endl;
//	}
//
//	//Testing startup phase
//	cout << "\nTesting startup Phase." << endl;
//	gameEngine.startupPhase();
//
//	//Territory Assignment
//	Map* map = gameEngine.getMap();
//	vector<Territory*> territoryList = map->getTerritoryList();
//	for (int i = 0; i < territoryList.size(); i++)
//	{
//		cout << territoryList[i]->getName() + " belongs to Player " << territoryList[i]->getPlayer() << endl;
//	}
//	
//	vector<Player*> playerList = gameEngine.getPlayerList();
//	cout << "\nEvery player will start with " << gameEngine.getInitialArmy() << " armies." << endl;
//
//	cout << "Player " << playerList[0]->getPosition() << " has " << playerList[0]->getReinforcementPool() << " armies in their reinforcement pool." << endl;
//	
//	cout << "\n====================================== MAIN GAME LOOP =========================================" << endl;
//	gameEngine.mainGameLoop();
//
//	delete map;
//	map = nullptr;
//
//	return 0;
//}
