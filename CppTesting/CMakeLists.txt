# CMakeList.txt : CMake project for CppTesting, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (CppTesting "CppTesting.cpp" "CppTesting.h" "power.cpp" "power.h" "GameClasses.cpp" "GameClasses.h" "Grammar.cpp" "Grammar.h" "Items.cpp" "Items.h" "Inventory.cpp" "Inventory.h" "IFOF.cpp" "IFOF.h")

# TODO: Add tests and install targets if needed.
