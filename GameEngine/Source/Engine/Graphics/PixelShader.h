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

		explicit PixelShader(ID3DBlob* pixelShaderBlob);

		~PixelShader();

		auto GetData() -> void*;

		auto GetDataSize() -> size_t;

	private:
		ID3D11PixelShader* m_Data{};

		ID3DBlob* m_DataBlob;

		size_t m_DataSize;

		friend class GraphicsEngine;

		friend class DeviceContext;
	};
}
