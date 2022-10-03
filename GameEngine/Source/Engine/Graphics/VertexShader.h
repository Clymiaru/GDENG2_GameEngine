#pragma once
#include <d3d11.h>

namespace Engine
{
	class DeviceContext;

	class VertexShader final
	{
	public:
		VertexShader(const void* shaderByteCode,
		             size_t shaderByteCodeSize);

		explicit VertexShader(ID3DBlob* vertexShaderBlob);

		~VertexShader();

		auto GetData() -> void*;

		auto GetDataSize() -> size_t;

	private:
		ID3D11VertexShader* m_Data;

		ID3DBlob* m_DataBlob;

		size_t m_DataSize;

		friend class DeviceContext;
	};
}
