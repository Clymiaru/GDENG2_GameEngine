#include "pch.h"
#include "ShaderLibrary.h"

namespace Engine
{
	ShaderLibrary::ShaderLibrary() :
		m_ShaderLoader{ShaderLoader()},
		m_VertexShaderMap{},
		m_PixelShaderMap{}
	{
	}

	ShaderLibrary::~ShaderLibrary()
	{
		// TODO: Actual releasing of resources
		m_VertexShaderMap.clear();
		m_PixelShaderMap.clear();
	}
}
