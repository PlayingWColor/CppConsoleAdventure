#include "CppTesting.h"

using namespace std;

void print_pow()
{
	float base;
	cout << "what's the base?" << endl << ">";
	cin >> base;
	int exp;
	cout << "what's the exponent?" << endl << ">";
	cin >> exp;

	string suffix = "th";

	unsigned int x = exp;

	if (exp > 20)
	{
		while (x > 10)
		{
			x -= 10;
		}
	}

	switch (x)
	{
	case 1:
		suffix = "st";
		break;
	case 2:
		suffix = "nd";
		break;
	case 3:
		suffix = "rd";
		break;
	}

	cout << base << " to the " << exp << suffix << " power is " << pow(base, exp) << ".\n";
}