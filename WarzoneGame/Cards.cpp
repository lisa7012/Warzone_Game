#include "Cards.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>

//Default constructor
Card::Card() {

}

//Constructor with parameters
Card::Card(string t) {
	this->type = t;
}

//Copy contructor
Card::Card(const Card& obj) {
	this->type = obj.type;
}

//Operator
Card& Card :: operator =(const Card& c)
{
	this->type = c.type;
	return *this;
}

//Method to play a card 
void Card::play()
{
	cout << "I use my " << Card::getType() << " card." << endl;
}

//Method to get the type of the card
string Card::getType()
{
	return type;
}

//Method to print the type of the card
string Card::print()const
{
	return ("This is a " + type + " card." + "\n");
}


//Method to create a deck of cards
deckOfCards::deckOfCards() {
	string type[] = { "Bomb", "Reinforcement", "Blockade",
		"Airlift","Diplomacy" };


	for (int count = 0; count < CARDS_PER_DECK; count++) 
		vectorCards.push_back(new Card(type[count % 5]));

}

//Destructor for the deck of cards
deckOfCards::~deckOfCards()
{
	for (int count = 0; count < CARDS_PER_DECK; count++)
	{
		if (vectorCards.at(count) != nullptr)
		{
			delete vectorCards.at(count);
			vectorCards.at(count) = nullptr;
		}
	}
}

//Method to shuffle the deck at random
void deckOfCards::shuffle() {
	for (int first = 0; first < vectorCards.size(); first++)
	{
		int second = (rand() + time(0)) % vectorCards.size();
		Card* temp = vectorCards[first];
		vectorCards[first] = vectorCards[second];
		vectorCards[second] = temp;
	}
}

//Method to draw card from the deck
Card* deckOfCards::draw()
{
	cout << "The player will draw a card" << endl;

	Card* a = vectorCards.back();
	Card* temp = new Card(*a);
	vectorCards.pop_back();
	cout << "The size of the deck is now " << vectorCards.size() << endl;
	delete a;
	return temp;
}

//Printing all the cards from the deck
void deckOfCards::printDeck() const
{
	cout << left;

	for (int i = 0; i < vectorCards.size(); i++)
	{
		cout << this->vectorCards.at(i)->print();
	}
}

//Method putting card back to deck
void deckOfCards::backToDeck(Card* c)
{
	vectorCards.insert(vectorCards.begin(), c);
	cout << "A card has been put back into the deck " << endl;
}

//Hand object with default constructor
Hand::Hand()
{

};

//Hand object with 1 constructor
Hand::Hand(Card* c)
{
	vectorCards.push_back(c);
}

//Destructor for the hand object
Hand::~Hand()
{

}

//Method to put a card in the hand after drawing
void Hand::pickCard(Card* c)
{
	vectorCards.push_back(c);
}

//Method to get back card in hand
vector<Card*>Hand::getCards()
{
	return vectorCards;
}

//Method to remove a card in the hand
Card* Hand::removeCard(int index)
{
	int i = index;
	Card* b = vectorCards.at(i);
	vectorCards.erase(vectorCards.begin() + i);
	cout << "Card removed from hand !" << endl;
	return b;
}

//Printing all the cards from the deck
string Hand::cardsInHand()
{
	cout << left;

	for (int i = 0; i < vectorCards.size(); i++) {
		return this->vectorCards.at(i)->print();
	}
}




