#include "CppTesting.h"

bool Save(std::string file_name, std::array<std::array<int, 8>, 8>& world, std::array<bool, 32>& pagesOwned, std::array<int, 32>& inventory, player& p, bool map, bool recipeBook, bool bookComplete, bool readTitle, bool key, std::array<std::array<bool, 8>, 8>& isMapped)
{
	if (file_name.length() < 2)
	{
		return false;//name is too short
	}
	else
	{
		std::ofstream ofs;
		ofs.open(file_name + ".sav", std::ofstream::out);
		if (ofs.is_open())
		{
			//save world
			for (int x = 0; x < world.size(); x++)
			{
				for (int y = 0; y < world[x].size(); y++)
				{
					if (y > 0)//comma after every number except last in row
						ofs << ",";
					ofs << world[x][y];
					if(y == world[x].size()-1 && x != world.size() - 1)//comma after last in row unless its the last collumn
						ofs << ",";
				}
			}
			ofs << std::endl;

			//save owned pages
			for (int i = 0; i < pagesOwned.size(); i++)
			{
				if (i > 0)//comma after every number except last in row
					ofs << ",";
				if(pagesOwned[i])
					ofs << 1;
				else
					ofs << 0;
			}
			ofs << std::endl;

			//save inventory
			for (int i = 0; i < inventory.size(); i++)
			{
				if (i > 0)//comma after every number except last in row
					ofs << ",";
				ofs << inventory[i];
			}
			ofs << std::endl;

			//save player
			ofs << p.pos.x;
			ofs << ",";
			ofs << p.pos.y;
			ofs << ",";
			ofs << p.hunger;
			ofs << std::endl;

			//save bools
			if(map)
				ofs << 1;
			else
				ofs << 0;
			ofs << ",";

			if (recipeBook)
				ofs << 1;
			else
				ofs << 0;
			ofs << ",";

			if (bookComplete)
				ofs << 1;
			else
				ofs << 0;
			ofs << ",";

			if (readTitle)
				ofs << 1;
			else
				ofs << 0;
			ofs << ",";

			if (key)
				ofs << 1;
			else
				ofs << 0;
			ofs << "\n";

			//save mapped area
			for (int x = 0; x < isMapped.size(); x++)
			{
				for (int y = 0; y < isMapped[x].size(); y++)
				{
					if (y > 0)//comma after every number except last in row
						ofs << ",";

					if (isMapped[x][y])
						ofs << 1;
					else
						ofs << 0;

					if (y == isMapped[x].size() - 1 && x != isMapped.size() - 1)//comma after last in row unless its the last column
						ofs << ",";
				}
			}
			ofs << std::endl;

			ofs.close();
		}
		else
		{
			return false;//file could not be openned
		}
		return true;
	}
}
bool Load(std::string file_name, std::array<std::array<int, 8>, 8>& world, std::array<bool, 32>& pagesOwned, std::array<int, 32>& inventory, player& p, bool& map, bool& recipeBook, bool& bookComplete, bool& readTitle, bool& key, std::array<std::array<bool, 8>, 8>& isMapped)
{
	if (file_name.length() < 2)
	{
		return false;//name is too short
	}
	else
	{
		std::ifstream ifs;
		ifs.open(file_name + ".sav", std::ifstream::in);
		if (ifs.is_open())
		{
			char c = ifs.get();
			std::string value = "";
			//load world
			for (int x = 0; x < world.size(); x++)
			{
				for (int y = 0; y < world[x].size(); y++)
				{
					value.clear();
					while (true)
					{
						if (c == ',' || c == '\n')
						{
							try
							{
								world[x][y] = std::stoi(value);
							}
							catch (std::invalid_argument const& e)
							{
								return false;
							}
							catch (std::out_of_range const& e)
							{
								return false;
							}
							value.clear();
							if (ifs.good())
								c = ifs.get();
							else
								return false;
							break;
						}
						else
						{
							value.push_back(c);
							if (ifs.good())
								c = ifs.get();
							else
								return false;
						}
					}
				}
			}/*
			if (ifs.good())
				c = ifs.get();
			else
				return false;*/

			//load owned pages
			for (int i = 0; i < pagesOwned.size(); i++)
			{
				while (true)
				{
					if (c == ',' || c == '\n')
					{
						if(value == "1")
							pagesOwned[i] = true;
						else
							pagesOwned[i] = false;

						value.clear();
						if (ifs.good())
							c = ifs.get();
						else
							return false;
						break;
					}
					else
					{
						value.push_back(c);
						if (ifs.good())
							c = ifs.get();
						else
							return false;
					}
				}
			}/*
			if (ifs.good())
				c = ifs.get();
			else
				return false;*/

			//load inventory
			for (int i = 0; i < inventory.size(); i++)
			{
				while (true)
				{
					if (c == ',' || c == '\n')
					{
						try
						{
							inventory[i] = std::stoi(value);
						}
						catch (std::invalid_argument const& e)
						{
							return false;
						}
						catch (std::out_of_range const& e)
						{
							return false;
						}

						value.clear();
						if (ifs.good())
							c = ifs.get();
						else
							return false;
						break;
					}
					else
					{
						value.push_back(c);
						c = ifs.get();
					}
				}
			}/*
			if (ifs.good())
				c = ifs.get();
			else
				return false;*/

			//load player
			for (int i = 0; i < 3; i++)
			{
				while (true)
				{
					if (c == ',' || c == '\n')
					{
						try
						{
							if(i == 0)
								p.pos.x = std::stoi(value);
							else if(i == 1)
								p.pos.y = std::stoi(value);
							else if (i == 2)
								p.hunger = std::stoi(value);
						}
						catch (std::invalid_argument const& e)
						{
							return false;
						}
						catch (std::out_of_range const& e)
						{
							return false;
						}
						value.clear();
						if (ifs.good())
							c = ifs.get();
						else
							return false;
						break;
					}
					else
					{
						value.push_back(c);
						if (ifs.good())
							c = ifs.get();
						else
							return false;
					}
				}
			}/*
			if (ifs.good())
				c = ifs.get();
			else
				return false;*/


			//load bools
			for (int i = 0; i < 5; i++)
			{
				while (true)
				{
					
					if (c == ',' || c == '\n')
					{
						if (i == 0)
						{
							if (value == "1")
								map = true;
							else
								map = false;
						}
						else if (i == 1)
						{
							if (value == "1")
								recipeBook = true;
							else
								recipeBook = false;
						}
						else if (i == 2)
						{
							if (value == "1")
								bookComplete = true;
							else
								bookComplete = false;
						}
						else if (i == 3)
						{
							if (value == "1")
								readTitle = true;
							else
								readTitle = false;
						}
						else if (i == 4)
						{
							if (value == "1")
								key = true;
							else
								key = false;
						}
						value.clear();
							if (ifs.good())
								c = ifs.get();
							else
								return false;
						break;
					}
					else
					{
						value.push_back(c);
						if (ifs.good())
							c = ifs.get();
						else
							return false;
					}
				}
			}
			//load isMapped
			for (int x = 0; x < isMapped.size(); x++)
			{
				for (int y = 0; y < isMapped[x].size(); y++)
				{
					value.clear();
					while (true)
					{
						if (c == ',' || c == '\n')
						{
							if (value == "1")
								isMapped[x][y] = true;
							else
								isMapped[x][y] = false;

							value.clear();
							//as last variable, it needs to not read anything in at the end
							if (c != '\n')
							{
								if (ifs.good())
									c = ifs.get();
								else
									return false;
							}
							break;
						}
						else
						{
							value.push_back(c);
							if (ifs.good())
								c = ifs.get();
							else
								return false;
						}
					}
				}
			}


			ifs.close();
		}
		else
		{
			return false;//file could not be openned
		}
		return true;
	}
}

void read_directory(const std::string& name, std::vector<std::string>& v)
{
	std::string pattern(name);
	pattern.append("\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			v.push_back(data.cFileName);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
}

std::string workingdir()
{
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf);
}