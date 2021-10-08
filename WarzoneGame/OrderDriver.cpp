#include "Order.h"

void testFunction();

int main()
{
	testFunction();
	return 0;
}

void testFunction() // To avoid memory leak 
{
	cout << "Creating all 6 different Orders\n";
	// Created an object of each type of order
	Deploy* deploy = new Deploy{};
	cout << "Deploy Created" << endl;
	Advance* advance = new Advance{};
	cout << "Advance Created" << endl;
	Bomb* bomb = new Bomb{};
	cout << "Bomb Created" << endl;
	Blockade* blockade = new Blockade{};
	cout << "Blockade Created" << endl;
	Airlift* airlift = new Airlift{};
	cout << "Airlift Created" << endl;
	Negotiate* negotiate = new Negotiate{};
	cout << "Negotiate Created" << endl;

	// Validate orders
	cout << "\nValidating each type of order: " << endl;
	cout << deploy->validate();
	deploy->SetName("Deploy");
	cout << advance->validate();
	advance->SetName("Advance");
	cout << bomb->validate();
	bomb->SetName("Bomb");
	cout << blockade->validate();
	blockade->SetName("Blockade");
	cout << airlift->validate();
	airlift->SetName("Airlift");
	cout << negotiate->validate();
	negotiate->SetName("Negotiate");

	cout << "\n\n";

	// Created an orderlist order
	OrdersList* orderlist = new OrdersList();

	// Adding order pointers to orderlist
	orderlist->addOrder(deploy);
	orderlist->addOrder(advance);
	orderlist->addOrder(bomb);
	orderlist->addOrder(blockade);
	orderlist->addOrder(airlift);
	orderlist->addOrder(negotiate);

	// Displaying current order list
	orderlist->PrintOrders();

	Player* player = new Player();

	// Testing execute function
	cout << "\nExecute function: " << endl;
	deploy->execute(player);
	advance->execute(player);
	bomb->execute(player);
	blockade->execute(player);
	airlift->execute(player);
	negotiate->execute(player);
	 
	// Displaying the length of the orders list
	cout << "\nLength of Orders List: " << endl;
	cout << orderlist->getLength() << endl;

	// Testing the remove function
	cout << "\nRemoving an order from the list: " << endl;
	orderlist->remove(bomb);
	cout << "Bomb removed." << endl;
	cout << "\nLength of Orders List: " << endl;
	cout << orderlist->getLength() << "\n" << endl;
	orderlist->PrintOrders();

	// Testing the move function
	cout << "\nMoving two orders: " << endl;
	orderlist->move(blockade, negotiate);
	cout << "Switching Blockade and Negotiate\n" << endl;
	orderlist->PrintOrders();

	// delete empty objects because still uses memory
	delete orderlist;
	delete player;
}
