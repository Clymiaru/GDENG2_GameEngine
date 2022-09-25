#pragma once
#include <d3d11.h>

namespace Engine
{
	class GraphicsEngine;
	class DeviceContext;

	class VertexShader final
	{
	public:
		VertexShader(const void* shaderByteCode,
					size_t shaderByteCodeSize);

		~VertexShader();

		// auto Init(const void* shaderByteCode,
		//           size_t byteCodeSize) -> bool;
		//
		// auto Release() const -> void;

	private:
		ID3D11VertexShader* m_Data {};
		size_t m_DataSize;
		
		friend class GraphicsEngine;
		friend class DeviceContext;
	};
}
