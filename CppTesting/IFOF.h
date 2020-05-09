#pragma once

bool Save(std::string file_name, std::array<std::array<int, 8>, 8> &world, std::array<bool, 32> &pagesOwned, std::array<int, 32> &inventory, player& p,bool map, bool recipeBook, bool bookComplete, bool readTitle, bool key, std::array<std::array<bool, 8>, 8>& isMapped);
bool Load(std::string file_name, std::array<std::array<int, 8>, 8>& world, std::array<bool, 32>& pagesOwned, std::array<int, 32>& inventory, player& p, bool& map, bool& recipeBook, bool& bookComplete, bool& readTitle, bool& key, std::array<std::array<bool, 8>, 8>& isMapped);
void read_directory(const std::string& name, std::vector<std::string>& v);
std::string workingdir();