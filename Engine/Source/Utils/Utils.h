#pragma once
#include <string>

#include <Windows.h>

namespace Engine::Utils
{
	inline std::wstring CStringToWString(const std::string& cString)
	{
		const int count = MultiByteToWideChar(CP_UTF8,
		                                      0,
		                                      cString.c_str(),
		                                      (int)cString.size(),
		                                      nullptr,
		                                      0);
		std::wstring wstr(count, 0);
		MultiByteToWideChar(CP_UTF8,
		                    0,
		                    cString.c_str(),
		                    (int)cString.size(),
		                    &wstr[0],
		                    count);
		return wstr;
	}
}
