#pragma once
#include <iostream>
#if DEBUG
	#define ENGINE_ASSERT(successCondition, errorMsg) {if (!(successCondition)) { std::cout << errorMsg << " Line: " << __FILE__ << " " <<  __LINE__; __debugbreak(); } }
#else 
	#define ENGINE_ASSERT(successCondition, errorMsg) { if (!(successCondition)) { } }
#endif