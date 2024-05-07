#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG //release build
	return "assets/";
#else
	return "C:/Users/siranjiv.s/source/repos/Siranjiv/LightYears/LightYearsGame/assets/";
#endif
}
