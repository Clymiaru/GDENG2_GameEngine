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

		~VertexShader();

	private:
		ID3D11VertexShader* m_Data{};

		size_t m_DataSize;

		friend class DeviceContext;
	};
}
