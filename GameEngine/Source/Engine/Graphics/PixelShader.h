#pragma once
#include <d3d11.h>

namespace Engine
{
	class GraphicsEngine;

	class DeviceContext;

	class PixelShader final
	{
	public:
		PixelShader(const void* shaderByteCode,
		            size_t shaderByteCodeSize);

		~PixelShader();

	private:
		ID3D11PixelShader* m_Data{};

		size_t m_DataSize;

		friend class GraphicsEngine;

		friend class DeviceContext;
	};
}
