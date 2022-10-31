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

		VertexShader& GetVertexShader();
		PixelShader& GetPixelShader();

	private:
		// Shader
		SharedPtr<VertexShader> m_VertexShader;
		SharedPtr<PixelShader> m_PixelShader;
		
		// ConstantData
	};
}
