#pragma once

#define INVSIZE 32

void OutInventory(std::array<int, INVSIZE>& inventory);
void AddInventory(int toAdd, std::array<int, INVSIZE>& inventory);
void RemoveInventory(int toRem, std::array<int, INVSIZE>& inventory);
bool InventoryFull(std::array<int, INVSIZE>& inventory, int& space);
void MakeSpace(std::array<int, INVSIZE>& inventory, std::vector<int>& found, int& space);
bool CheckFor(std::array<int, INVSIZE>& inventory, std::string name, int& pos);