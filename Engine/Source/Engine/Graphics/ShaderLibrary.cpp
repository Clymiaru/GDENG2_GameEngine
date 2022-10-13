﻿#include "pch.h"
#include "ShaderLibrary.h"

namespace Engine
{
	ShaderLibrary ShaderLibrary::s_Instance = ShaderLibrary();

	void ShaderLibrary::Initialize(const size_t expectedShaderCountOfAllShaders)
	{
		s_Instance.m_VertexShaderMap.reserve(expectedShaderCountOfAllShaders);
		s_Instance.m_PixelShaderMap.reserve(expectedShaderCountOfAllShaders);
	}

	void ShaderLibrary::Terminate()
	{
		s_Instance.m_VertexShaderMap.clear();
		s_Instance.m_PixelShaderMap.clear();
	}

	ShaderLibrary::ShaderLibrary() = default;

	ShaderLibrary::~ShaderLibrary() = default;

	std::wstring ShaderLibrary::GetShaderNameFromFilename(const std::wstring& fileName)
	{
		size_t finalBackslashPos   = fileName.find_last_of(L'/');
		if (finalBackslashPos == std::wstring::npos)
		{
			finalBackslashPos = 0ULL;
		}
		const size_t startOfExtensionPos = fileName.find(L'.');
		std::wstring shaderName = fileName.substr(finalBackslashPos, startOfExtensionPos - finalBackslashPos);
		return shaderName;
	}
}
