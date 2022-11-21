#pragma once
#include "Engine/Core/Core.h"
#include "Engine/Graphics/Shader/VertexShader.h"
#include "Engine/Graphics/Shader/PixelShader.h"

namespace Engine
{
	struct Material
	{
		String Name;
		VertexShader* VertexShader;
		PixelShader* PixelShader;
	};
}
