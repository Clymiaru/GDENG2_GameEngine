#pragma once

#include <iostream>

#define ENGINE_ASSERT(successCondition, errorMsg) {if (!(successCondition)) { std::cout << errorMsg << " Line: " << __FILE__ << " " <<  __LINE__; __debugbreak(); } }