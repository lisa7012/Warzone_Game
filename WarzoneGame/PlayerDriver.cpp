#include "Player.h"
#include <vector>
#include <string>
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	// Creates Territory pointers and add them to player's list of territories
	Territory* ptrTA = new Territory { "China" };
	Territory* ptrTB = new Territory { "Canada" };
	Territory* ptrTC = new Territory { "Vietnam" };
	Territory* ptrTD = new Territory { "USA" };
	vector<Territory*> countries;
	countries.push_back(ptrTA);
	countries.push_back(ptrTB);

	// Creates Card pointers and add them to player's hand of cards
	Card* ptrCA = new Card { "Bomb" };
	Card* ptrCB = new Card { "Airlift" };
	HandOfCards hand{};
	hand.addCard(ptrCA);
	hand.addCard(ptrCB);
	HandOfCards* playerhand{ &hand };

	// Creates a list of orders for the player
	vector<Order*> orderlist;

	// Creates Player object with previous information
	Player player1{ countries, playerhand, orderlist };

	// Prints player's list of territories, hand of cards, and order list
	cout << "Player's Current Information: " << endl;
	cout << "=============================\n" << endl;
	cout << player1; 

	// Adding territories list to defend and attack
	player1.addTerritoryToDefend(ptrTA);
	player1.addTerritoryToDefend(ptrTB);
	player1.addTerritoryToAttack(ptrTC);
	player1.addTerritoryToAttack(ptrTD);

	// Prints player's list of territories to defend and to attack
	cout << "\ntoDefend() and toAttack Functions: " << endl;
	cout << "==================================\n" << endl;
	player1.toDefend();
	cout << "\n";
	player1.toAttack();
	
	// Testing issueOrder() function and printing player's order list
	player1.issueOrder("Blockade");
	cout << "\nAfter issuing order:" << endl;
	cout << "=====================\n" << endl;
	cout << player1;
} 