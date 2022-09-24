#pragma once
#include <d3d11.h>

namespace Engine
{
	class GraphicsEngine;

	class DeviceContext;

	class VertexShader final
	{
	public:
		VertexShader();

		~VertexShader() = default;

		auto Init(const void* shaderByteCode,
		          size_t byteCodeSize) -> bool;

		auto Release() const -> void;

	private:
		ID3D11VertexShader* m_Data;

		size_t m_Length;

		friend class DeviceContext;
	};
}
