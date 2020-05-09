#include "CppTesting.h"

bool Make(std::array<int, 32> &inventory, std::string itemName)
{
	//get item id of item to make
	int toMakeID = -1;
	for (int i = 0; i < items.size(); i++)
	{
		if (itemName == items[i]->name)
		{
			toMakeID = i;
		}
	}
	//the item doesn't exist
	if (toMakeID == -1)
	{
		delayedOutput("You cannot make " + itemName + ".\n", textSpeed::veryfast);
		return false;
	}
	Recipe* r = 0;
	//get recipe for making item
	for (int i = 0; i < book.size(); i++)
	{
		std::vector<int> out = book[i].getOut();
		if(out[0] == toMakeID)
			r = &book[i];
	}
	if (r == 0)
	{
		delayedOutput("There is no recipe for " + itemName + ".\n", textSpeed::veryfast);
		return false;
	}
	std::vector<int> required = r->getRequired();
	std::vector<int> out = r->getOut();
	//check inventory for items needed to make new item
	//for (int x : required)
	//	std::cout << items[x]->name << std::endl;
	bool allItems = true;
	std::array<bool, 32> alreadyChecked = {false};
	for (int n : required)
	{
		bool hasItem = false;
		for (int i = 0; i < inventory.size(); i++)
		{
			if (!alreadyChecked[i])//check for multiples of the same item when necessary
			{
				if (n == inventory[i])
				{
					hasItem = true;
					alreadyChecked[i] = true;
					break;
				}
			}
		}
		allItems = hasItem;
		if (allItems == false)
			break;
	}
	//stop if don't have needed items
	if (!allItems)
	{
		delayedOutput("You do not have the required materials for " + itemName + ".\n", textSpeed::veryfast);
		return false;
	}
	//remove used items
	for (int n : required)
	{
		RemoveInventory(n, inventory);
	}
	//add new item(s)
	for (int n : out)
	{
		AddInventory(n, inventory);
	}
	//get article for item to make
	std::string art = defineArticle(items[toMakeID]->name, "some", false, items[toMakeID]->forcePlural);
	//output success
	delayedOutput("You made " + art + " " + itemName + "!\n", textSpeed::veryfast);
	return true;
}