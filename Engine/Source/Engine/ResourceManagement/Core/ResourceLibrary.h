#pragma once
#include "ResourceLoader.h"

#include "Engine/ResourceManagement/Shader/ShaderLibrary.h"

// ResourceLibrary::Get<VertexShader>("Shader");

namespace Engine
{
	class ResourceLibrary
	{
	public:
		
	private:
		// TextureLibrary
		ShaderLibrary m_ShaderLibrary;
	};
}

