#pragma once
#include <iostream>
#include "MapLoader.h"

int main() {
	
	ConquestFileReaderAdapter* adapter = new ConquestFileReaderAdapter();
	
	int userGameMode;
	
	//User Input for Map Style: Domination vs Conquest
	while (true)
	{
		cout << "0. Domination \t1. Conquest" << endl;
		cin >> userGameMode;
		if (userGameMode == 0 || userGameMode == 1) { 
			adapter->setConquestMap(userGameMode); //Conquest -> 1; it will be true
			break;
			
		}
		else {
			cout << "Invalid Choice. Please try again." << endl;
			continue;
		}
	}

	string userMapChoice;

	//User Input for Conquest Map
	if (adapter->getConquestMap()) {
		cout << "Conquest Mode has been chosen." << endl;
		Map* map;
		while (true) {
			cout << "Please select a map: ";
			cin >> userMapChoice;
			adapter->setFileName(userMapChoice); 
			map = adapter->parseMap();

			if (adapter->ConquestFileReader::getValidMap() == true) { //bad logic?
				cout << "Valid Map" << endl;
				map->displayMap();
				//setMapeName(userMapChoice);
				break;
			}
			else {
				cout << "Invalid Map. Try again." << endl;
				continue;
			}
		}
	}
	//User Input for Domination Map
	else {
		cout << "Domination Mode has been chosen." << endl;
		//MapLoader* mapLoad;
		Map* map;
		while (true) {
			cout << "Please select a map: ";
			cin >> userMapChoice;
			//mapLoad = new MapLoader(userMapChoice);
			adapter->setFileName(userMapChoice);
			map = adapter->parseMap();

			if (adapter->MapLoader::getValidMap() == true) { //bad logic?
				cout << "Valid Map" << endl;
				map->displayMap();
				//setMapeName(userMapChoice);
				break;
			}
			else {
				cout << "Invalid Map. Try again." << endl;
				continue;
			}
		}
	}
	return 0;
}