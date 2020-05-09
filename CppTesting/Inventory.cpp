#include "CppTesting.h"

void OutInventory(std::array<int, INVSIZE>& inventory)
{
	int knockback = 0;
	for (int x : inventory)
	{
		int spaceAmount = 18 - items[x]->name.length();
		int spaceFront = spaceAmount / 2;
		int spaceBack = spaceAmount - spaceFront;
		std::string centered = items[x]->name;
		//center word
		centered.insert(0, spaceFront, ' ');
		centered.insert(centered.length(), spaceBack, ' ');
		std::cout << " [" << centered << "] ";

		knockback++;
		if (knockback == 4)
		{
			std::cout << std::endl << std::endl;
			knockback = 0;
		}
	}
}
void OutFound(std::vector<int>& found)
{
	int knockback = 0;
	for (int x : found)
	{
		int spaceAmount = 16 - items[x]->name.length();
		int spaceFront = spaceAmount / 2;
		int spaceBack = spaceAmount - spaceFront;
		std::string centered = items[x]->name;
		//center word
		centered.insert(0, spaceFront, ' ');
		centered.insert(centered.length(), spaceBack, ' ');
		std::cout << " [" << centered << "] ";

		knockback++;
		if (knockback == 4)
		{
			std::cout << std::endl << std::endl;
			knockback = 0;
		}
	}
}
void AddInventory(int toAdd, std::array<int, INVSIZE>& inventory)
{
	int i = 0;
	for (int x : inventory)
	{
		if (x == 0)
			break;
		else
			i++;
	}
	inventory[i] = toAdd;
}
void RemoveInventory(int toRem, std::array<int, INVSIZE>& inventory)
{
	int i = 0;
	for (int x : inventory)
	{
		if (x == toRem)
			break;
		else
			i++;
	}
	inventory[i] = 0;
}
bool InventoryFull(std::array<int, INVSIZE>& inventory, int& space)
{
	space = 0;
	for (int x : inventory)
	{
		if (x == 0)
			space++;
	}
	if (space > 0)
		return false;
	else
		return true;
}
void MakeSpace(std::array<int, INVSIZE>& inventory, std::vector<int>& found, int& space)
{
	delayedOutput("However, there isn't enough room.\n", textSpeed::fast);
	while (found.size() > space)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		OutInventory(inventory);
		OutFound(found);
		delayedOutput("\nPick an item to discard.\n>", textSpeed::fast);
		std::string toRemove = getInput();//ask for item
		bool removed = false;
		for (int i = 0; i < found.size(); i++)//check found items for item to remove first
		{
			if (toRemove == items[found[i]]->name)
			{
				delayedOutput(items[found[i]]->name + " was discarded.\n", textSpeed::fast);

				found.erase(found.begin()+i);
				removed = true;
			}
		}
		if (!removed)//check inventory for item to remove
		{
			for (int i = 0; i < inventory.size(); i++)
			{
				if (toRemove == items[inventory[i]]->name)
				{
					delayedOutput(items[inventory[i]]->name + " was discarded.\n", textSpeed::fast);

					inventory[i] = 0;
					removed = true;
					break;
				}
			}

			InventoryFull(inventory, space);
		}
		if (!removed)//tell player the item he chose doesn't exist
		{
			delayedOutput("No item was found by the name of " + toRemove + ".\n", textSpeed::fast);
		}
		else if (found.size() > space)
		{
			delayedOutput("There still isn't enough room.\n", textSpeed::fast);
		}
		else
		{
			delayedOutput("There is now enough room, and the items have been added to your inventory.\n", textSpeed::fast);
		}
	}
}
bool CheckFor(std::array<int, INVSIZE>& inventory, std::string name, int& pos)
{
	for (int i = 0; i < inventory.size(); i++)
	{
		if (name == items[inventory[i]]->name)
		{
			pos = i;
			return true;
		}
	}
	return false;
}