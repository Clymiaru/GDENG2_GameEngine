#include "pch.h"
#include "VertexBuffer.h"

#include "Renderer.h"

#include "Engine/Core/Debug.h"

namespace Engine
{
	VertexBuffer::VertexBuffer(const void* vertexList,
	                           size_t vertexSize,
	                           uint32_t vertexListCount,
	                           const void* shaderByteCode,
	                           size_t shaderByteCodeSize,
	                           const D3D11_INPUT_ELEMENT_DESC* indexLayout,
	                           size_t indexLayoutSize) :
		Buffer(vertexListCount, vertexSize),
		m_DataLayout{nullptr}
	{
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.Usage             = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth         = ByteSize();
		bufferDesc.BindFlags         = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags    = 0;
		bufferDesc.MiscFlags         = 0;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem                = vertexList;

		const auto result = Renderer::CreateBuffer(&bufferDesc, &initData, &m_Data);

		Debug::Assert(SUCCEEDED(result), "Vertex buffer cannot be created!");

		const auto layoutResult =
				Renderer::CreateLayout(indexLayout,
				                       indexLayoutSize,
				                       shaderByteCode,
				                       shaderByteCodeSize,
				                       &m_DataLayout);

		Debug::Assert(SUCCEEDED(layoutResult), "Vertex layout cannot be created!");
	}

	VertexBuffer::~VertexBuffer()
	{
		m_DataLayout->Release();
		m_Data->Release();
	}
}
