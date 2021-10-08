#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <iterator>

using std::vector;
using std::string;
using std::cout;

class Territory;
class Player;

// Order class for Part 3 (Order) ===========
class Order {
public:
    
    // default constructor
    Order();

    // destructor
    ~Order();

    // copy constructor
    Order(const Order& order);

    // assignment operator
    Order& operator=(const Order& order);

    //Stream Insertion Operator
    friend std::ostream& operator<<(std::ostream& out, const Order& order);

    // Validates the order.
    virtual bool validate() = 0;

    // Validate then executes orders according to player's state and order definition.
    virtual void execute() = 0;

    void setOrderName(string _name);
    string getOrderName();

    Territory* getSourceTerritory() { return sourceTerritory; };
    void setSourceTerritory(Territory* t) { sourceTerritory = t; };
    Territory* getTargetTerritory() { return targetTerritory; };
    void setTargetTerritory(Territory* t) { targetTerritory = t; };
    Territory* getTerritoryToDeploy() { return territoryToDeploy; };
    void setTerritoryToDeploy(Territory* t) { territoryToDeploy = t; };
    int getNumOfArmiesToDeploy() { return numOfArmiesToDeploy; };
    void setNumOfArmiesToDeploy(int a) { numOfArmiesToDeploy = a; };
    Player* getPlayer() { return player; }
    void setPlayer(Player* p) { player = p; }
    string getPlayerName() { return playerName; }
    void setPlayerName(string n) { playerName = n; };
    int getOrderIndex() { return orderIndex; };
    void setOrderIndex(int o) { orderIndex = o; };

protected:
    string name;
    bool isValidate;
    Player* player;
    Territory* sourceTerritory;
    Territory* targetTerritory;
    Territory* territoryToDeploy;
    int numOfArmiesToDeploy;
    string playerName;
    int orderIndex;
};

class Deploy : public Order {
public:
    //Default constructor
    Deploy();
    //Destructor
    ~Deploy();
    //Copy Constructor
    Deploy(const Deploy& deploy);
    //Assignment Operator
    Deploy& operator=(const Deploy& deploy);
    //Stream Insertion Operator
    friend std::ostream& operator<<(std::ostream& out, const Deploy& deploy);
    bool validate();
    void execute();
};

class Advance : public Order {
public:
    // Default constructor
    Advance();
    //Destructor
    ~Advance();
    //Copy Constructor
    Advance(const Advance& advance);
    //Assignment Operator
    Advance& operator=(const Advance& advance);
    //Stream Insertion Operator
    friend std::ostream& operator<<(std::ostream& out, const Advance& advance);
    bool validate();
    void execute();
};

// Structure to hold orders and apply operations over.
class OrdersList {
private:
    // Set of Order pointers.
    vector<Order*> orders;

    // Finds an order in orders.
    vector<Order*>::iterator findOrder(Order* order);

public:

    //Default constructor
    OrdersList();
    //Destructor
    ~OrdersList();
    //Copy Constructor
    OrdersList(const OrdersList& OrderList);
    //Assignment Operator
    OrdersList& operator=(const OrdersList& ordersList);
    //Stream Insertion Operator
    friend std::ostream& operator<<(std::ostream& out, const OrdersList& ordersList);
    vector<Order*> getOrders();
    
    // Adds an order to orders.
    void addOrder(Order* order);
	bool isEmpty() { return orders.empty(); }
	
    // Gets the number of elements in orders.
    int getLength() const;

    // Deletes an order from the list
    void remove(Order* removeOrder);

    // Gets an Order pointer at a specific index.
    Order* getAtIndex(const unsigned int index) const;

    // Swaps two orders' position in the list.
    void move(Order* first, Order* second);
    void PrintOrders();
};