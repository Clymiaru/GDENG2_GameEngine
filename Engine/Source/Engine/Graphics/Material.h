#pragma once
#include "Engine/Core/Core.h"

namespace Engine
{
	class VertexShader;
	class PixelShader;
	class Material
	{
	public:
		Material(const String& shader);
		virtual ~Material();

	private:
		// Shader
		
		// ConstantData Required by the Shader (Except TransformMatrices)
	};
}
