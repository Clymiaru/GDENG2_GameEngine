#include "pch.h"
#include "VertexBuffer.h"
#include "RenderSystem.h"

namespace Engine
{
	VertexBuffer::VertexBuffer() :
		m_Data(nullptr),
		m_DataLayout(nullptr),
		m_DataSize{0},
		m_DataCount{0}
	{
	}

	VertexBuffer::~VertexBuffer()
	{
		m_DataLayout->Release();
		m_Data->Release();
	}

	auto VertexBuffer::GetCount() const -> Uint
	{
		return m_DataCount;
	}

	auto VertexBuffer::GetSize() const -> Uint
	{
		return m_DataSize * m_DataCount;
	}

	auto VertexBuffer::Load(const void* vertexList,
	                        const Uint vertexDataSize,
	                        const Uint vertexListCount,
	                        const void* shaderByteCode,
	                        const Uint shaderByteCodeSize,
	                        const D3D11_INPUT_ELEMENT_DESC* indexLayout,
	                        const Uint indexLayoutSize) -> bool
	{
		if (m_Data)
			m_Data->Release();
		if (m_DataLayout)
			m_DataLayout->Release();

		m_DataCount = vertexListCount;
		m_DataSize  = vertexDataSize;

		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.Usage             = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth         = GetSize();
		bufferDesc.BindFlags         = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags    = 0;
		bufferDesc.MiscFlags         = 0;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem                = vertexList;

		const auto result = RenderSystem::GetInstance().GetDevice().CreateBuffer(&bufferDesc, &initData, &m_Data);
		if (FAILED(result))
		{
			return false;
		}

		const auto layoutResult =
				RenderSystem::GetInstance().GetDevice().CreateInputLayout(
					indexLayout,
					indexLayoutSize,
					shaderByteCode,
					shaderByteCodeSize,
					&m_DataLayout);

		if (FAILED(layoutResult))
		{
			return false;
		}
		return true;
	}
}
