// CppTesting.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <array>
#include <vector>
#include <cstdlib>
#include <limits>
#include <chrono>
#include <thread>
#include <typeinfo>
#include <fstream> 
#include <windows.h>
#undef max

#include "power.h"
#include "GameClasses.h"
#include "Grammar.h"
#include "Items.h"
#include "Inventory.h"
#include "IFOF.h"

static enum textSpeed { slow, medium, fast, veryfast };
void delayedOutput(std::string out, textSpeed speed);
std::string getInput();