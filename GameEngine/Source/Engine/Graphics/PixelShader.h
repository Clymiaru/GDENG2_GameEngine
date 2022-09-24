#pragma once
#include <d3d11.h>

namespace Engine
{
	class GraphicsEngine;
	class DeviceContext;
	
	class PixelShader
	{
	public:
		PixelShader();
		virtual ~PixelShader() = default;

		auto Release() -> void;

		[[nodiscard]]
		auto Init(const void* shaderByteCode, size_t byteCodeSize) -> bool;

	private:
		ID3D11PixelShader* m_Data;

		friend class GraphicsEngine;
		friend class DeviceContext;
		
	};
}
