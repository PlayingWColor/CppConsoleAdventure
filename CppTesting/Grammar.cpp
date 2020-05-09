#include "CppTesting.h"

//grammar
std::string defineArticle(std::string locName, bool capitalize)
{
	char firstLetter = locName.at(0);
	char lastLetter = locName.at(locName.length() - 1);
	if (lastLetter == 's')
		return "";
	else if (capitalize)
	{
		if (firstLetter == 'a' || firstLetter == 'i' || firstLetter == 'u' || firstLetter == 'e' || firstLetter == 'o')
			return "An";
		else
			return "A";
	}
	else
	{
		if (firstLetter == 'a' || firstLetter == 'i' || firstLetter == 'u' || firstLetter == 'e' || firstLetter == 'o')
			return "an";
		else
			return "a";
	}
}
std::string defineArticle(std::string locName, std::string pluralOut, bool capitalize)
{
	char firstLetter = locName.at(0);
	char lastLetter = locName.at(locName.length() - 1);
	if (lastLetter == 's')
		return pluralOut;
	else if (capitalize)
	{
		if (firstLetter == 'a' || firstLetter == 'i' || firstLetter == 'u' || firstLetter == 'e' || firstLetter == 'o')
			return "An";
		else
			return "A";
	}
	else
	{
		if (firstLetter == 'a' || firstLetter == 'i' || firstLetter == 'u' || firstLetter == 'e' || firstLetter == 'o')
			return "an";
		else
			return "a";
	}
}
std::string defineArticle(std::string locName, std::string pluralOut, bool capitalize, bool forcePlural)
{
	char firstLetter = locName.at(0);
	char lastLetter = locName.at(locName.length() - 1);
	if (lastLetter == 's' || forcePlural)
		return pluralOut;
	else if (capitalize)
	{
		if (firstLetter == 'a' || firstLetter == 'i' || firstLetter == 'u' || firstLetter == 'e' || firstLetter == 'o')
			return "An";
		else
			return "A";
	}
	else
	{
		if (firstLetter == 'a' || firstLetter == 'i' || firstLetter == 'u' || firstLetter == 'e' || firstLetter == 'o')
			return "an";
		else
			return "a";
	}
}