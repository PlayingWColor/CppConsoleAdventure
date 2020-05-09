#include "CppTesting.h"

	Vector2::Vector2()
	{

	}
	Vector2::Vector2(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	std::ostream& operator << (std::ostream& output, const Vector2 vect)
	{
		output << "[" << vect.x << ", " << vect.y << "]";
		return output;
	}
	bool operator == (const Vector2& vect1, const Vector2& vect2)
	{
		return vect1.x == vect2.x && vect1.y == vect2.y;
	}

//player
	player::player()
	{
		this->pos = Vector2();
		this->hunger = 40;
	}

//areas
	Area::Area(std::string name, std::string shorthand, std::vector<int> items, std::vector<int> rarity)
	{
		this->name = name;
		this->shorthand = shorthand;
		this->findableItems = items;
		this->itemRarities = rarity;
	}
//items
	Item::Item()
	{
		name = " ";
		forcePlural = false;
	}
	Item::Item(std::string name)
	{
		this->name = name;
		forcePlural = false;
	}
	Item::Item(std::string name, bool forcePlural)
	{
		this->name = name;
		this->forcePlural = forcePlural;
	}
	Item::~Item() {}

	Edible::Edible(std::string name, int restoreValue)
	{
		this->name = name;
		this->restoreValue = restoreValue;
		forcePlural = false;
	}
	Edible::Edible(std::string name, int restoreValue, bool forcePlural)
	{
		this->name = name;
		this->restoreValue = restoreValue;
		this->forcePlural = forcePlural;
	}

	Weapon::Weapon(std::string name, int damageValue)
	{
		this->name = name;
		this->damageValue = damageValue;
	}
//book
	Recipe::Recipe(int requiredItem, int outItem)
	{
		this->requiredItems = std::vector<int>({ requiredItem });
		this->outItems = std::vector<int>({ outItem });
	}
	Recipe::Recipe(std::vector<int> requiredItems, int outItem)
	{
		this->requiredItems = requiredItems;
		this->outItems = std::vector<int>({ outItem });
	}
	Recipe::Recipe(int requiredItems, std::vector<int> outItems)
	{
		this->requiredItems = std::vector<int>({ requiredItems });
		this->outItems = outItems;
	}
	Recipe::Recipe(std::vector<int> requiredItems, std::vector<int> outItems)
	{
		this->requiredItems = requiredItems;
		this->outItems = outItems;
	}
	std::vector<int> Recipe::getRequired()
	{
		return requiredItems;
	}
	std::vector<int> Recipe::getOut()
	{
		return outItems;
	}

	std::string Recipe::read()
	{
		std::string out = "To make " + items[outItems[0]]->name + " you need: ";

		std::vector<int> neededAmount;
		std::vector<int> itemIDs;

		int last = -1;
		int current = -1;

		//figure out how many of each item is needed
		for (int i = 0; i < requiredItems.size(); i++)
		{
			if (requiredItems[i] == last)
			{
				neededAmount[current]++;
			}
			else
			{
				neededAmount.push_back(1);
				itemIDs.push_back(requiredItems[i]);
				last = requiredItems[i];
				current++;
			}
		}

		bool first = true;
		//display what and amounts
		for (int i = 0; i < neededAmount.size(); i++)
		{
			if (first)
				first = false;
			else
				out += " and ";
			if (neededAmount[i] > 0)
			{
				out += std::to_string(neededAmount[i]) + " ";
			}
			out += items[itemIDs[i]]->name;
		}
		
		out += ".";

		return out;
	}