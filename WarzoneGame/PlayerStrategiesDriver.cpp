#define _DEBUG
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif
#include "PlayerStrategies.h"
#include "Player.h"
#include "GameEngine.h"

int main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	cout << "-------------------------------------------------\n" <<
			"                     Game Start                \n" <<
			"-------------------------------------------------\n\n";
	GameEngine gameEngine;
	
	//Testing Map Select."
	gameEngine.mapSelect();
		
	//Testing number of player set.
	gameEngine.setNbrOfPlayers();
		
	//Testing observer on/off
	gameEngine.setObserver();
	
	gameEngine.startupPhase();

	//Asking the user for which type of strategy
	cout << "\nTypes of strategy: " << endl;
	cout << "1. Human Player Strategy" << endl;
	cout << "2. Aggressive Player Strategy" << endl;
	cout << "3. Benevolent Player Strategy" << endl;
	cout << "4. Neutral Player Strategy" << endl;

	int choice;
	for (int i = 0; i < gameEngine.getPlayerList().size(); i++) {
		cout << "\nWhich strategy would you like for Player " << gameEngine.getPlayerList()[i]->getPosition() << ": ";
		cin >> choice;
		switch (choice) {
		case 1:
			gameEngine.getPlayerList()[i]->setPlayerStrategy(new HumanPlayerStrategy);
			gameEngine.getPlayerList()[i]->getPlayerStrategy()->setPlayer(gameEngine.getPlayerList()[i]);
			break;
		case 2: 
			gameEngine.getPlayerList()[i]->setPlayerStrategy(new AggressivePlayerStrategy);
			gameEngine.getPlayerList()[i]->getPlayerStrategy()->setPlayer(gameEngine.getPlayerList()[i]);
			break;
		case 3:
			gameEngine.getPlayerList()[i]->setPlayerStrategy(new BenevolentPlayerStrategy);
			gameEngine.getPlayerList()[i]->getPlayerStrategy()->setPlayer(gameEngine.getPlayerList()[i]);
			break;
		case 4:
			gameEngine.getPlayerList()[i]->setPlayerStrategy(new NeutralPlayerStrategy);
			gameEngine.getPlayerList()[i]->getPlayerStrategy()->setPlayer(gameEngine.getPlayerList()[i]);
			break;
		default:
			cout << "Invalid choice";
		}
	}

	cout << "\n====================================== MAIN GAME LOOP =========================================" << endl;
	gameEngine.mainGameLoop();

	return 0;
}