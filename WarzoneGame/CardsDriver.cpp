#include "Cards.h"

int main()
{
	//Creating the deck of card object
	deckOfCards* deck = new deckOfCards();

	//Printing the deck in order
	deck->printDeck();
	//Shuffling the deck at random
	deck->shuffle();

	cout << endl << endl;
	std::cout << "The deck has been shuffled.\n";
	cout << endl << endl;

	//Printing the new shuffled deck
	deck->printDeck();

	cout << endl << endl;

	//User draws 3 cards.
	//Puts cards in hand object
	Card* a = deck->draw();
	Hand* hand = new Hand();
	hand->pickCard(a);

	Card* b = deck->draw();
	hand->pickCard(b);

	Card* c = deck->draw();
	hand->pickCard(c);

	cout << endl;
	cout << "These are the cards in the hand:" << endl;

	//Displaying all the cards in the hand
	for (int i = 0; i < hand->getCards().size(); i++) 
	{
		Card* cardy = hand->getCards().at(i);

		if (cardy) 
		{
			cout << cardy->print();
		}
		else 
		{
			cout << "This is a null pointer";
		}

	}

	cout << endl;

	//Playing the 1st card in the card and removing it from the hand obj
	a->play();
	Card* f = hand->removeCard(0);

	cout << endl;
	cout << "These are the cards in the hand:" << endl;

	//Displaying the cards left in hand
	for (int i = 0; i < hand->getCards().size(); i++)
	{
		Card* cardInHand = hand->getCards().at(i);
		if (cardInHand)
		{
			cout << cardInHand->print();
		}
		else
		{
			cout << "Null pointer or invalid pointer occuring" << endl;
		}
	}

	cout << endl;

	//Putting the card back in the deck
	deck->backToDeck(f);

	cout << endl;
	cout << "The deck will now be printed" << endl;
	cout << endl;

	//Printing the deck with the additional card 
	deck->printDeck();

	//Shuffling back the deck with the additional card
	deck->shuffle();

	//Printing the deck that has been shuffled 
	deck->printDeck();

	cout << endl;

	//Playing every cards in the hand and putting it back to the deck
	b->play();
	Card* g = hand->removeCard(0);
	deck->backToDeck(g);
	c->play();
	Card* h = hand->removeCard(0);
	deck->backToDeck(h);

	cout << endl;

	cout << endl;
	cout << "These are the cards in the hand:" << endl;

	//Displaying the cards left in hand
	for (int i = 0; i < hand->getCards().size(); i++)
	{
		Card* cardy = hand->getCards().at(i);
		if (cardy)
		{
			cout << cardy->print();
		}
		else
		{
			cout << "Null pointer or invalid pointer occuring" << endl;
		}
	}

	//Deleting all the pointers for objects
	delete deck;
	deck = nullptr;
	delete hand;
	hand = nullptr;
	return 0;
}