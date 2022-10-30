#pragma once
#include <d3d11.h>

#include "Buffer.h"

namespace Engine
{
	class DeviceContext;
	class Renderer;

	class VertexBuffer final : public Buffer
	{
	public:
		VertexBuffer(const void* vertexList,
		             size_t vertexSize,
		             uint32_t vertexListCount,
		             const void* shaderByteCode,
		             size_t shaderByteCodeSize,
		             const D3D11_INPUT_ELEMENT_DESC* indexLayout,
		             size_t indexLayoutSize);

		~VertexBuffer() override;

	private:
		ID3D11InputLayout* m_DataLayout;
		friend class DeviceContext;
	};
}
