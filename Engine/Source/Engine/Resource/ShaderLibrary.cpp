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

	std::string ShaderLibrary::GetShaderNameFromFilename(const StringView filename)
	{
		std::string result = filename.data();

		size_t finalBackslashPos = result.find_last_of(L'/');

		if (finalBackslashPos == std::string::npos)
			finalBackslashPos = 0ULL;
		else
			finalBackslashPos += 1;

		const size_t startOfExtensionPos = result.find(L'.');

		std::string shaderName = result.substr(finalBackslashPos,
		                                       startOfExtensionPos - finalBackslashPos);
		return shaderName;
	}
}
