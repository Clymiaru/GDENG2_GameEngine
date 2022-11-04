#include "pch.h"
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

	std::string ShaderLibrary::GetShaderNameFromFilename(const std::string& fileName)
	{
		size_t finalBackslashPos   = fileName.find_last_of(L'/');
		if (finalBackslashPos == std::string::npos)
		{
			finalBackslashPos = 0ULL;
		}
		else
		{
			finalBackslashPos += 1;
		}
		const size_t startOfExtensionPos = fileName.find(L'.');
		std::string shaderName = fileName.substr(finalBackslashPos, startOfExtensionPos - finalBackslashPos);
		return shaderName;
	}
}
