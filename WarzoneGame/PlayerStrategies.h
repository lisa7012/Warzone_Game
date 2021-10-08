#pragma once
#include <vector>
#include <iostream>

using std::vector;

class Player;
class Territory;

class PlayerStrategy
{
public:
	// default constructor
	PlayerStrategy();
	// destructor
	~PlayerStrategy();
	// copy constructor
	PlayerStrategy(const PlayerStrategy& ps);
	// assignment operator
	PlayerStrategy& operator=(const PlayerStrategy& p);
	// stream insertion operator
	friend std::ostream& operator<<(std::ostream& out, const PlayerStrategy& ps);

	virtual void issueOrder() = 0;
	virtual vector<Territory*> toDefend() = 0;
	virtual vector<Territory*> toAttack() = 0;
	Player* getPlayer() { return player; }
	void setPlayer(Player* p) { player = p; }
protected:
	Player* player;
};

class HumanPlayerStrategy : public PlayerStrategy
{
public:
	// default constructor
	HumanPlayerStrategy();
	// destructor
	~HumanPlayerStrategy();
	// copy constructor
	HumanPlayerStrategy(const HumanPlayerStrategy& hps);
	// assignment operator
	HumanPlayerStrategy& operator=(const HumanPlayerStrategy& hps);
	// stream insertion operator
	friend std::ostream& operator<<(std::ostream& out, const HumanPlayerStrategy& hps);

	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};

class AggressivePlayerStrategy : public PlayerStrategy
{
public:
	// default constructor
	AggressivePlayerStrategy();
	// destructor
	~AggressivePlayerStrategy();
	// copy constructor
	AggressivePlayerStrategy(const AggressivePlayerStrategy& aps);
	// assignment operator
	AggressivePlayerStrategy& operator=(const AggressivePlayerStrategy& aps);
	// stream insertion operator
	friend std::ostream& operator<<(std::ostream& out, const AggressivePlayerStrategy& aps);

	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};

class BenevolentPlayerStrategy : public PlayerStrategy
{
public:
	// default constructor
	BenevolentPlayerStrategy();
	// destructor
	~BenevolentPlayerStrategy();
	// copy constructor
	BenevolentPlayerStrategy(const BenevolentPlayerStrategy& bps);
	// assignment operator
	BenevolentPlayerStrategy& operator=(const BenevolentPlayerStrategy& bps);
	// stream insertion operator
	friend std::ostream& operator<<(std::ostream& out, const BenevolentPlayerStrategy& bps);

	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};

class NeutralPlayerStrategy : public PlayerStrategy
{
public:
	// default constructor
	NeutralPlayerStrategy();
	// destructor
	~NeutralPlayerStrategy();
	// copy constructor
	NeutralPlayerStrategy(const NeutralPlayerStrategy& nps);
	// assignment operator
	NeutralPlayerStrategy& operator=(const NeutralPlayerStrategy& nps);
	// stream insertion operator
	friend std::ostream& operator<<(std::ostream& out, const NeutralPlayerStrategy& nps);

	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
};