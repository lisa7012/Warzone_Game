#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

const int CARDS_PER_DECK = 50;

//Card class 
class Card
{
public:
	Card();
	Card(string card);
	Card(const Card& c);
	Card& operator =(const Card& c);
	string print() const;
	string getType();
	void play();

private:
	string type;
};

//Deck class
class deckOfCards
{
public:
	deckOfCards();
	~deckOfCards();
	vector <Card*> vectorCards;
	Card* draw();
	void shuffle();
	void printDeck() const;
	void backToDeck(Card* c);
private:
	Card* deck;
	int currentCard;
};

//Hand class
class Hand
{
public:
	Hand();
	~Hand();
	Hand(Card* c);
	vector <Card*> getCards();
	void pickCard(Card* c);
	Card* removeCard(int index);
	string cardsInHand();
private:
	vector <Card*> vectorCards;
};
