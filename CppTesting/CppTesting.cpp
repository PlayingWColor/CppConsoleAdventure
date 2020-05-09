// CppTesting.cpp : Defines the entry point for the application.
//

#include "CppTesting.h"

void DisplayMap(std::array<std::array<int, 8>, 8>& world, std::array<Area, 8>& areaTypes, player& player, std::array<std::array<bool, 8>, 8>& isMapped, Vector2& monumentLoc)
{
	int knockback = 0;
	for (int y = world.size() - 1; y >= 0; y--)
	{
		for(int x = 0; x < world[y].size(); x++)
		{
			std::string name = areaTypes[world[x][y]].shorthand;
			
			if (!isMapped[x][y])
				name = "??????";

			int spaceAmount = 10 - name.length();
			long long int spaceFront = spaceAmount / 2;
			int spaceBack = spaceAmount - spaceFront;
			std::string centered = name;
			//center word
			centered.insert(0, spaceFront, ' ');
			centered.insert(centered.length(), spaceBack, ' ');


			//add player position
			if(x == player.pos.x && y == player.pos.y)
				centered.replace(9, 1, "P");
			//add monument location
			if(isMapped[x][y] && monumentLoc.x == x && monumentLoc.y == y)
				centered.replace(0, 1, "M");

			std::cout << " [" << centered << "] ";
		}
		std::cout << std::endl << std::endl;
	}
}
std::string addPage(std::array<bool, 32>& pagesOwned)
{
	while (true)
	{
		int newNum = std::rand() % 32;
		if (!pagesOwned[newNum])
		{
			pagesOwned[newNum] = true;
			return std::to_string(newNum);
		}
	}
}
std::string addPage(std::array<bool, 32>& pagesOwned, bool& bookComplete)
{
	int pageCount = 0;
	while (pageCount < 32)
	{
		int newNum = std::rand() % 32;
		if (!pagesOwned[newNum])
		{
			pagesOwned[newNum] = true;
			return std::to_string(newNum);
		}
		pageCount++;
	}
	bookComplete = true;
	return "";
}
void initWorld(std::array<std::array<int, 8>, 8> &world, Vector2 &monumentLoc, std::array<bool, 32>& pagesOwned)
{
	for (int x = 0; x < world.size(); x++)
	{
		for (int y = 0; y < world[0].size(); y++)
		{
			world.at(x).at(y) = std::rand() % 8;
		}
	}
	monumentLoc = Vector2(std::rand() % 8, std::rand() % 8);
	for (int i = 0; i < 5; i++)
	{
		std::string n = addPage(pagesOwned);
	}
}

bool checkHunger(int hunger)
{
	if (hunger <= 20)
	{
		if (hunger == 20)
			delayedOutput("You are starting to feel hungry.\n", textSpeed::fast);
		if (hunger == 10)
			delayedOutput("You are very hungry. It's time to eat.\n", textSpeed::fast);
		if (hunger == 8)
			delayedOutput("You find it difficult to keep moving due to the hunger pangs.\n", textSpeed::fast);
		if (hunger <= 4)
			delayedOutput("You collapse on the ground, knowing full well that if you push yourself much further without eating, you will die.\n", textSpeed::fast);
		if (hunger == 0)
		{
			delayedOutput("You collapse on the ground. Your vision fades, as your dulling thoughts are carried into oblivion.\n", textSpeed::fast);
			delayedOutput("You have died.\n", textSpeed::medium);
			delayedOutput("Game Over\n", textSpeed::medium);
			return true;
		}
	}
	return false;
}
void afterEat(int hunger)
{
	if(hunger <= 12)
		delayedOutput("You are still very hungry.\n", textSpeed::fast);
	else if (hunger <= 20)
		delayedOutput("You are still hungry.\n", textSpeed::fast);
	else if (hunger <= 25)
		delayedOutput("You are still a little hungry.\n", textSpeed::fast);
	else if (hunger <= 30)
		delayedOutput("You could probably eat more, but your hunger is satisfied for now.\n", textSpeed::fast);
	else if (hunger < 40)
		delayedOutput("You are feeling full.\n", textSpeed::fast);
	else if (hunger == 40)
		delayedOutput("You couldn't possibly eat another bite!\n", textSpeed::fast);
}
std::string getInput()
{
	std::string str;

	std::cin >> str;
	while (std::cin.rdbuf()->in_avail() > 1)
	{
		std::string add;
		std::cin >> add;
		str += " " + add;
	}
	return str;
}

void delayedOutput(std::string out, textSpeed speed)
{
	for (char c : out)
	{
		switch(speed)
		{
		case textSpeed::slow:
			Sleep(120);
			break;
		case textSpeed::medium:
			Sleep(50);
			break;
		case textSpeed::fast:
			Sleep(20);
			break;
		case textSpeed::veryfast:
			Sleep(5);
			break;
		}
		std::cout << c;
	}
}
int main()
{
	static std::array<Area, 8> areaTypes =
	{
		Area("grassy hills", "hills", std::vector<int>({2,5,12,14,19,20,23,26,36}), std::vector<int>({42,64,32,26,128,16,42,96})),
		Area("arid desert", "desert", std::vector<int>({2,8,9,10,20,24,26,27,28}), std::vector<int>({64,16,12,24,48,32,128,64,32})),
		Area("murky swamp", "swamp", std::vector<int>({1,2,7,11,12,13,21,27,28,41}), std::vector<int>({200,128,96,64,64,48,128,36,24,4})),
		Area("snowswept tundra", "tundra", std::vector<int>({4,13,16,17,26,40}), std::vector<int>({128,16,96,24,36,8})),
		Area("breezy forest", "forest", std::vector<int>({2,5,7,10,11,12,13,14,18,19,20,22,23,24,36}), std::vector<int>({48,32,64,16,32,48,64,36,64,64,32,100,24,24,128})),
		Area("sun scortched crag", "crag", std::vector<int>({2,8,9,10,20,24,26,27}), std::vector<int>({128,48,24,96,48,64,24,12})),
		Area("refreshing lakeside", "lake", std::vector<int>({1,2,7,11,12,13,15,27,28}), std::vector<int>({128,64,128,48,32,64,64,48,24})),
		Area("volcanic ridge", "volcano", std::vector<int>({2,3,6,9,10,20,24,25,26}), std::vector<int>({128,128,96,48,96,128,40,16,32}))
	};

	std::array<std::array<int,8>,8> world;

	std::array<bool, 32> pagesOwned = {false};

	pagesOwned[0] = true;
	
	Vector2 monumentLoc;

	player p;

	std::array<int, 32> inventory = {0};//zero fills inventory with nothing

	bool map = false;
	bool recipeBook = false;
	bool bookComplete = false;
	bool readTitle = false;
	bool key = false;

	std::array<std::array<bool, 8>, 8> isMapped = {false};

	delayedOutput("Load or Start?\n", textSpeed::medium);

	//std::cout << "Load or Start?" << std::endl;
	//std::cout << monumentLoc << std::endl;

	//get file names in case of load
	std::vector<std::string> allFiles;
	//only works in windows
	read_directory(workingdir(), allFiles);
	std::vector<std::string> savesOnly;
	for (std::string s : allFiles)
	{
		if (s.length() > 4)
		{
			if (s.substr(s.length() - 4, 4) == ".sav")
			{
				savesOnly.push_back(s.substr(0, s.length() - 4));
			}
		}
	}



	std::string input;
	do
	{
		std::cout << ">";std::cin >> input;
		if (input == "l" || input == "load")
		{
			if (savesOnly.size() > 0)
			{
				if (std::cin.rdbuf()->in_avail() <= 1)
				{
					std::cout << "List of Saves" << std::endl << "------------------" << std::endl;
					for (std::string s : savesOnly)
						std::cout << s << std::endl;
					
					input = getInput();
				}
				else
				{
					input = getInput();
				}
			
				bool loadInfo = Load(input, world, pagesOwned, inventory, p, map, recipeBook, bookComplete, readTitle, key, isMapped);

				if (loadInfo)
				{
					delayedOutput("Loaded game successfully!\n", textSpeed::fast);
				}
				else
				{
					delayedOutput("Loading game failed!\n", textSpeed::fast);
					delayedOutput("Quiting Game\n", textSpeed::fast);
					return 0;
				}
			}
			else
			{
				delayedOutput("No save files exist. Starting from scratch.\n", textSpeed::fast);
			}

			break;
		}
		else if (input == "s" || input == "start")
		{
			delayedOutput("Input something to be used as a seed.\n", textSpeed::fast);
			std::string seed;
			seed = getInput();
			
			int intseed = 0;
			try
			{
				intseed = std::stoi(seed);
			}
			catch (std::invalid_argument const& e)
			{
				for (char c : seed)
					intseed += c;
			}

			std::srand(intseed);
			
			initWorld(world, monumentLoc, pagesOwned);
		}
		else
			delayedOutput("expecting \"load\" or \"start\" as a response.\n", textSpeed::veryfast);
	} while (input != "s" && input != "start");

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	bool gameover = false;
	
	//declare location
	std::string locName = areaTypes.at(world.at(p.pos.x).at(p.pos.y)).name;

	//a or an
	std::string art = defineArticle(locName, true);

	std::string sentenceEnd = " encompases you.";

	if(art.length() == 0)
		sentenceEnd = " encomapase you.";

	delayedOutput("You find yourself stranded in an unfamiliar land. " + art + " " + locName + sentenceEnd + "\n", textSpeed::fast);


	std::string ACT;
	while (!gameover)
	{
		
		delayedOutput("What will you do?\n", textSpeed::veryfast);

		std::cout << ">";std::cin >> ACT;
		if (ACT == "go" || ACT == "walk" || ACT == "run" || ACT == "head")
		{
			if (std::cin.rdbuf()->in_avail() <= 1)
				delayedOutput("which direction?\n", textSpeed::veryfast);

			std::cout << ">";std::cin >> ACT;

			bool success = false;

			if (ACT == "north" || ACT == "up" || ACT == "n")
			{
				p.pos.y++;
				if (p.pos.y > world[0].size()-1)
				{
					p.pos.y -= world[0].size();
				}
				success = true;
			}
			else if (ACT == "south" || ACT == "down" || ACT == "s")
			{
				p.pos.y--;
				if (p.pos.y < 0)
				{
					p.pos.y += world[0].size();
				}
				success = true;
			}
			else if (ACT == "east" || ACT == "right" || ACT == "e")
			{
				p.pos.x++;
				if (p.pos.x > world.size() - 1)
				{
					p.pos.x -= world.size();
				}
				success = true;
			}
			else if (ACT == "west" || ACT == "left" || ACT == "w")
			{
				p.pos.x--;
				if (p.pos.x < 0)
				{
					p.pos.x += world.size();
				}
				success = true;
			}
			else if (ACT == "help")
			{
				delayedOutput("directions include: north, south, east, & west\n", textSpeed::veryfast);
			}
			else
			{
				delayedOutput(ACT + " is not a direction. Try typing \"go help\" for a list of possible commands\n", textSpeed::veryfast);
			}
			if (success)
			{
				//remove hunger point
				p.hunger -= 2;
				
				//map area if map is owned
				if(map)
					isMapped[p.pos.x][p.pos.y] = true;
				//declare location
				std::string locName = areaTypes.at(world.at(p.pos.x).at(p.pos.y)).name;

				//a or an
				std::string art = defineArticle(locName);

				delayedOutput("You travel until you find yourself in " + art + " " + locName + "." + "\n", textSpeed::fast);

				if (p.pos == monumentLoc)
				{
					delayedOutput("A large stone monument, aged by time, sits solemnly on a small ridge, raised higher than all else visible.\n", textSpeed::fast);
				}

				if(map)
					std::cout << p.pos << std::endl;

				//display hunger warnings
				gameover = checkHunger(p.hunger);
			}
		}
		else if (ACT == "forage"  || ACT == "f" || ACT == "search" || ACT == "find")
		{
			bool specific = false;
			//check for searching for something specific
			if (std::cin.rdbuf()->in_avail() > 1)
			{
				ACT = getInput();
				specific = true;
			}
			
			
			int space = INVSIZE;
			//check to see if you found a page
			if (recipeBook && !bookComplete && std::rand() % 256 < 64 && !specific)
			{
				std::string add = addPage(pagesOwned, bookComplete);
				if(!bookComplete)
					delayedOutput("You found a missing page! It's page number " + add + "\n", textSpeed::fast);
				else
					delayedOutput("You found nothing.\n", textSpeed::fast);
			}//check to see if you found items
			else if (!InventoryFull(inventory, space))//make sure inventory isn't full first
			{
				std::vector<int> findableItems = areaTypes.at(world.at(p.pos.x).at(p.pos.y)).findableItems;
				std::vector<int> itemRarities = areaTypes.at(world.at(p.pos.x).at(p.pos.y)).itemRarities;

				std::vector<int> found;

				for (int i = 0; i < findableItems.size(); i++)
				{
					int randVal = std::rand() % 256;

					if (specific)
					{
						if (items[findableItems[i]]->name == ACT)
						{
							if (randVal <= itemRarities[i])
								found.push_back(findableItems[i]);
						}
					}
					else
					{
						if (randVal <= itemRarities[i])
							found.push_back(findableItems[i]);
					}
				}

				if (found.size() > 0)
				{
					delayedOutput("You found ", textSpeed::fast);
					for (int i = 0; i < found.size(); i++)
					{
						if (i > 0)
							delayedOutput(" and ", textSpeed::fast);

						//a, an, or some
						std::string art = defineArticle(items[found[i]]->name, "some", false, items[found[i]]->forcePlural);

						//output name of item
						delayedOutput(art + " " + items[found[i]]->name, textSpeed::fast);
					}
					std::cout << "." << std::endl;

					//get rid of items until you have space
					if (found.size() > space)
					{
						MakeSpace(inventory, found, space);
					}

					//add to inventory
					for (int x : found)
					{
						AddInventory(x, inventory);
					}

				}
				else
				{
					delayedOutput("You found nothing.\n", textSpeed::veryfast);
				}

				//remove hunger point
				p.hunger--;
				p.hunger = std::fmax(p.hunger, 0);
				//display hunger warnings
				gameover = checkHunger(p.hunger);
			}
			else
			{
				delayedOutput("You can't forage right now, because your inventory is full. Try using the \"discard\" command to remove items from your bag.\n", textSpeed::veryfast);
				delayedOutput("WARNING: This is permanent!\n", textSpeed::veryfast);
			}
		}
		else if (ACT == "inventory" || ACT == "i")
		{
			OutInventory(inventory);
		}
		else if (ACT == "discard" || ACT == "remove" || ACT == "drop" || ACT == "d" || ACT == "toss")
		{
			bool all = false;
			bool yesAll = false;

			if (std::cin.rdbuf()->in_avail() <= 1)
			{
				delayedOutput("discard what?\n", textSpeed::fast);
				ACT = getInput();
			}
			else
			{
				ACT = getInput();
				if (ACT.substr(0, 3) == "all")
				{
					all = true;
					if (ACT.length() <= 4)
					{
						delayedOutput("discard all of what?\n", textSpeed::fast);
						ACT = getInput();
					}
					else
					{
						ACT = ACT.substr(4, ACT.length() - 4);
					}
					delayedOutput("Are you sure you want to discard all " + ACT + " from your inventory?\n", textSpeed::fast);
					std::string ANS;
					std::cout << ">";std::cin >> ANS;
					if (ANS == "y" || ANS == "yes")
					{
						yesAll = true;
					}
				}
			}
			int pos;
			if (all && yesAll)
			{
				while (CheckFor(inventory, ACT, pos))
				{
					inventory[pos] = 0;
				}
				delayedOutput("You have discarded all items called " + ACT + ".\n", textSpeed::fast);
			}
			else if(!all)
			{
				if (CheckFor(inventory, ACT, pos))
				{
					delayedOutput("Are you sure you want to discard " + ACT + " from your inventory?\n", textSpeed::fast);
					std::string ANS;
					std::cout << ">";std::cin >> ANS;
					if (ANS == "y" || ANS == "yes")
					{
						inventory[pos] = 0;
						delayedOutput("You have discarded " + ACT + ".\n", textSpeed::fast);
					}
				}
				else
				{
					delayedOutput("No " + ACT + " could be found in your inventory.", textSpeed::veryfast);
				}
			}
		}
		else if (ACT == "eat" || ACT == "consume" || ACT == "devour" || ACT == "e")
		{
			if (p.hunger < 40)
			{
				if (std::cin.rdbuf()->in_avail() <= 1)
				{
					delayedOutput("eat what?", textSpeed::fast);
					ACT = getInput();
				}
				else
				{
					ACT = getInput();
				}

				int pos;

				if (CheckFor(inventory, ACT, pos))
				{
					Item* t = items[inventory[pos]];
					try
					{
						Edible* e = dynamic_cast<Edible*>(t);
						p.hunger += e != nullptr ? e->restoreValue : throw std::exception("bad cast");
						p.hunger = std::fmin(p.hunger, 40);
						inventory[pos] = 0;
						delayedOutput("You ate " + ACT + ".\n", textSpeed::fast);
						afterEat(p.hunger);
					}
					catch (const std::bad_cast & e)
					{
						delayedOutput("You can't eat that!\n", textSpeed::veryfast);
					}
					catch (const std::exception & e)
					{
						delayedOutput("You can't eat that!\n", textSpeed::veryfast);
					}
				}
				else
				{
					delayedOutput("No " + ACT + " could be found in your inventory.\n", textSpeed::veryfast);
				}
			}
			else
			{
				delayedOutput("You're too stuffed to eat right now.\n", textSpeed::veryfast);
			}
		}
		else if (ACT == "examine" || ACT == "look" || ACT == "l")
		{
			if (std::cin.rdbuf()->in_avail() <= 1)
			{
				delayedOutput("examine what?\n", textSpeed::veryfast);
				ACT = getInput();
			}
			else
			{
				ACT = getInput();
			}
			if (ACT == "monument" || ACT == "stone monument" || ACT == "aged monument")
			{
				if (recipeBook)
				{
					if (key)
					{
						delayedOutput("You find a small embossed keyhole sticking out one of the sides of the monument.\n", textSpeed::medium);
						Sleep(200);
						delayedOutput("Tentatively,", textSpeed::medium);
						Sleep(400);
						delayedOutput(" you place the monument key inside the keyhole and turn.\n", textSpeed::medium);
						Sleep(200);
						delayedOutput("After a half turn the key refuses to budge, and a ticking noise begins to come from within the monument.\n", textSpeed::medium);
						Sleep(200);
						delayedOutput("The ticking stops suddenly, and just then large cracks crawl out from the keyhole covering the whole monument.\n", textSpeed::medium);
						Sleep(200);
						delayedOutput("As they spread, an immensely bright light emanates from within.\n", textSpeed::medium);
						Sleep(200);
						delayedOutput("Eventually the glow becomes so strong that it engulfs you in its light.\n", textSpeed::medium);
						delayedOutput("The light is warm, and you feel as if it is carrying you somewhere...\n", textSpeed::slow);
						Sleep(1300);
						delayedOutput("...somewhere more familiar.\n", textSpeed::slow);
						Sleep(2000);
						delayedOutput("\n\nYou Win!\nThank you for playing!\n", textSpeed::medium);
						Sleep(5000);
						delayedOutput("\n\nPress Enter To Quit the Game.\n", textSpeed::veryfast);
						std::string end;
						std::cin >> end;
						return 0;
					}
					else
						delayedOutput("You find a small embossed keyhole sticking out one of the sides of the monument.\n", textSpeed::fast);
				}
				else
				{
					delayedOutput("You notice a large book sitting at the foot of the monument.\n", textSpeed::fast);
					delayedOutput("It has been weathered by time, and looks as if many of its pages have been torn out.\n", textSpeed::fast);
					delayedOutput("You take it.\n", textSpeed::fast);
					delayedOutput("Access the book by using the \"check book\" command.\n", textSpeed::fast);
					recipeBook = true;
				}
			}
		}
		else if (ACT == "check" || ACT == "c" || ACT == "book" || ACT == "b" || ACT == "map")
		{
			if (ACT == "check" || ACT == "c")
			{
				if (std::cin.rdbuf()->in_avail() <= 1)
					delayedOutput("check what?\n", textSpeed::fast);

				std::cout << ">";std::cin >> ACT;
			}
			if (ACT == "book" || ACT == "b")
			{
				if (recipeBook)
				{
					if (std::cin.rdbuf()->in_avail() <= 1)
					{
						delayedOutput("The book contains the following pages:\n", textSpeed::fast);
						delayedOutput("title page, ", textSpeed::fast);
						bool first = true;
						for (int i = 0; i < pagesOwned.size(); i++)
						{
							if (pagesOwned[i])
							{
								if (first)
									first = false;
								else
									std::cout << ", ";

								delayedOutput("page " + (i + 1), textSpeed::fast);
							}
						}
						delayedOutput(".\n", textSpeed::fast);
						delayedOutput("To read a page, type the number of the page after the command \"check book\" or \"book\".\n", textSpeed::fast);
						delayedOutput("The title page can be refered to as \"0\" or \"title\".\n", textSpeed::fast);
					}
					else
					{
						std::cout << ">";std::cin >> ACT;
						if (ACT == "title" || ACT == "0")
						{
							delayedOutput("Guide to Unlocking the Monument: Building the Key and Much More!\n", textSpeed::fast);
							if (!readTitle)
							{
								delayedOutput("Use the command \"make\" to construct something new.\n", textSpeed::veryfast);
								readTitle = true;
							}
						}
						else
						{
							try
							{
								long long int pageNum = std::stoi(ACT);

								if (pageNum <= pagesOwned.size() && pageNum >= 1)
								{
									if (pagesOwned[pageNum - 1])
									{
										delayedOutput(book[pageNum - 1].read()+"\n", textSpeed::fast);
									}
									else
									{
										delayedOutput("You don't have page " + ACT + " yet.\n", textSpeed::veryfast);
									}
								}
								else
								{
									delayedOutput("Page " + ACT + " does not exist.\n", textSpeed::veryfast);
								}
							}
							catch (std::invalid_argument const& e)
							{
								delayedOutput(ACT + " is not a page number!\n", textSpeed::veryfast);
							}
						}
					}
				}
				else
				{
					delayedOutput("You do not have a book.\n", textSpeed::veryfast);
				}
			}
			else if (ACT == "map")
			{
				if (map)
				{
					isMapped[p.pos.x][p.pos.y] = true;
					DisplayMap(world, areaTypes, p, isMapped, monumentLoc);
				}
				else
				{
					delayedOutput("You do not have a map.\n", textSpeed::veryfast);
				}
			}
			else
			{
				delayedOutput("That's not something that can be checked!\n", textSpeed::veryfast);
			}
		}
		else if (ACT == "make" || ACT == "m")
		{
			if (std::cin.rdbuf()->in_avail() <= 1)
			{
				delayedOutput("make what?\n", textSpeed::fast);
				ACT = getInput();
			}
			else
			{
				ACT = getInput();
			}
			bool success = Make(inventory, ACT);
			if (success)
			{
				//remove hunger point
				p.hunger--;
				
				if (ACT == "map")
				{
					isMapped[p.pos.x][p.pos.y] = true;
					delayedOutput("Now you can check the map using \"check map\" or \"map\".\n", textSpeed::fast);
					map = true;
				}
				if (ACT == "monument key")
				{
					key = true;
				}
			}


		}
		else if (ACT == "save")
		{
			if (std::cin.rdbuf()->in_avail() <= 1)
			{
				delayedOutput("type a file name\n", textSpeed::fast);
				ACT = getInput();
			}
			else
			{
				ACT = getInput();
			}
			bool saveInfo = Save(ACT, world, pagesOwned, inventory, p, map, recipeBook, bookComplete, readTitle, key, isMapped);
			if (saveInfo)
				delayedOutput("Game Saved!\n", textSpeed::veryfast);
			else
				delayedOutput("Game Save Failed!\nFile name was invalid!\n", textSpeed::veryfast);
		}
		else if (ACT == "quit")
		{
			gameover = true;
		}
		else if (ACT == "help")
		{
			if (std::cin.rdbuf()->in_avail() <= 1)
			{
				delayedOutput("Command list: go, forage, examine, inventory, eat, discard, ", textSpeed::veryfast);
				if (recipeBook || map)
					delayedOutput("check, ", textSpeed::veryfast);
				if (readTitle)
					delayedOutput("make, ", textSpeed::veryfast);
				delayedOutput("quit, help\n", textSpeed::veryfast);
				delayedOutput("Type \"help\" and the name of a command for more details, and shortcut commands.\n", textSpeed::veryfast);
			}
			else
			{
				std::cin >> ACT;
				if (ACT == "go")
				{
					delayedOutput("Use \"go\" to move to a new area.\nThe shortcut command is \"g\".\nOther acceptable commands are \"walk\", \"run\", and \"head\".\n", textSpeed::veryfast);
				}
				else if (ACT == "forage")
				{
					delayedOutput("Use \"forage\" to search the environment for items.\nThe shortcut command is \"f\".\nOther acceptable commands are \"search\" and \"find\".\n", textSpeed::veryfast);
				}
				else if (ACT == "examine")
				{
					delayedOutput("Use \"examine\" to examine something in your vicinity.\nThe shortcut command is \"l\".\n\"look\" is also acceptable.\n", textSpeed::veryfast);
				}
				else if (ACT == "inventory")
				{
					delayedOutput("Use \"inventory\" to look at your inventory.\nThe shortcut command is \"e\".\nOther acceptable commands are \"consume\" and \"devour\".\n", textSpeed::veryfast);
				}
				else if (ACT == "eat")
				{
					delayedOutput("Use \"eat\" to eat something in your inventory.\nThe shortcut command is \"e\".\nOther acceptable commands are \"consume\" and \"devour\".\n", textSpeed::veryfast);
				}
				else if (ACT == "discard")
				{
					delayedOutput("Use \"discard\" to remove something from your inventory.\nThe shortcut command is \"d\".\nOther acceptable commands are \"remove\", \"drop\", and \"toss\".\n", textSpeed::veryfast);
				}
				else if (ACT == "check" && (recipeBook || map))
				{
					delayedOutput("Use \"check\" to look at the recipe book or map.\nThe shortcut command is \"c\".\n", textSpeed::veryfast);
					delayedOutput("In most cases this command is unnecesary and \"book\" or \"map\" can be used as commands themselves.\n", textSpeed::veryfast);
				}
				else if (ACT == "make" && readTitle)
				{
					delayedOutput("Use \"make\" to make items from other items.\nThe shortcut command is \"m\"\n", textSpeed::veryfast);
				}
				else if (ACT == "quit")
				{
					delayedOutput("This will quit the game.\nMake sure to save first!\n", textSpeed::veryfast);
				}
				else if (ACT == "help")
				{
					delayedOutput("How clever of you.\n", textSpeed::veryfast);
				}
				else
				{
					delayedOutput(ACT + "is not a command with help instructions.\n", textSpeed::veryfast);
				}
			}
		}
		else
		{
			delayedOutput(ACT + " is not a command. Try typing \"help\" for a list of possible commands.\n", textSpeed::veryfast);
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

		if(gameover)
			delayedOutput("Thank you for playing!\n", textSpeed::fast);
	}

	return 0;
}
