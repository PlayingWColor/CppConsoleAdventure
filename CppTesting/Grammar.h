#pragma once

//grammar
std::string defineArticle(std::string locName, bool capitalize = false);
std::string defineArticle(std::string locName, std::string pluralOut, bool capitalize = false);
std::string defineArticle(std::string locName, std::string pluralOut, bool capitalize = false, bool forcePlural = false);