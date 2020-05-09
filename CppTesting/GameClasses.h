#pragma once

struct Vector2
{
	int x = 0;
	int y = 0;
	Vector2();
	Vector2(int x, int y);
	friend std::ostream& operator << (std::ostream& output, const Vector2 vect);
	friend bool operator == (const Vector2& vect1, const Vector2& vect2);
};

//player
class player
{
public:
	Vector2 pos;
	int hunger;
	player();
};

//areas
class Area
{
public:
	std::string name;

	std::vector<int> findableItems;

	std::string shorthand;

	std::vector<int> itemRarities;//out of 512 smaller is more rare
	Area(std::string name, std::string shorthand, std::vector<int> items, std::vector<int> rarity);

};

//items
class Item
{
public:
	std::string name;
	bool forcePlural;
	Item();
	Item(std::string name);
	Item(std::string name, bool forcePlural);
	virtual ~Item();
};

class Edible : public Item
{
public:
	int restoreValue;
	Edible(std::string name, int restoreValue);
	Edible(std::string name, int restoreValue, bool forcePlural);
};

class Weapon : public Item
{
public:
	int damageValue;
	Weapon(std::string name, int damageValue);
};

//book
class Recipe
{
	std::vector<int> requiredItems;
	std::vector<int> outItems;
public:
	Recipe(int requiredItem, int outItem);
	Recipe(std::vector<int> requiredItems, int outItem);
	Recipe(int requiredItems, std::vector<int> outItems);
	Recipe(std::vector<int> requiredItems, std::vector<int> outItems);
	std::vector<int> getRequired();
	std::vector<int> getOut();
	std::string read();
};