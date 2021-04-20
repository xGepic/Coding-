#pragma once
#include <iostream>

using namespace std;

class Fighter {

private:
	int LifePoints;
	int Speed;
	string name;

protected:
	void setLifepoints(int lp);
	void setSpeed(int s);
	void setName(string n);

public:
	Fighter();
	virtual ~Fighter();

	int getLifepoints();
	int getSpeed();
	string getName();

	void damage(int i);
	void heal(int i);

	bool isOnline;
	void setOnline();
	void setOffline();

	void incSpeed();
	void decSpeed();

	bool nullify;
	void setNullify();
	void unNullify();

	bool dodge;
	void setDodge();
	void unDodge();

	virtual void useAbility(int n, Fighter* enemy, int p) = 0;
	virtual void printAbilities() = 0;
};

class Warrior : public Fighter {

private:
	int counter;

public:
	Warrior();
	virtual ~Warrior();

	void setCounter(int i);
	int getCounter();
	void incCounter();

	void useAbility(int n, Fighter* enemy, int p);
	void printAbilities();
};

class Hunter : public Fighter {

private:

public:
	Hunter();
	virtual ~Hunter();

	void useAbility(int n, Fighter* enemy, int p);
	void printAbilities();
};

class Mage : public Fighter {

private:
	bool counterSpell;

public:
	Mage();
	virtual ~Mage();

	void setCounterSpellF();
	void setCounterSpellT();

	void useAbility(int n, Fighter* enemy, int p);
	void printAbilities();
};

class Rogue : public Fighter {

private:
	bool ambush;
	bool assassinate;
	bool cd;

public:
	Rogue();
	virtual ~Rogue();

	void setAmbushF();
	void setAmbushT();

	void setCdF();
	void setCdT();

	void setAssassinateF();
	void setAssassinateT();

	void useAbility(int n, Fighter* enemy, int p);
	void printAbilities();
};

class Custom : public Fighter {

private:
	int counter;
	bool counterSpell;
	bool ambush;
	bool assassinate;
	bool cd;

public:
	Custom();
	virtual ~Custom();

	void setCounter(int i);
	int getCounter();
	void incCounter();

	void setCounterSpellF();
	void setCounterSpellT();

	void setAmbushF();
	void setAmbushT();

	void setCdF();
	void setCdT();

	void setAssassinateF();
	void setAssassinateT();

	void useAbility(int n, Fighter* enemy, int p);
	void printAbilities();
};
