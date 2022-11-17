#include "pch.h"
#include "IndexBuffer.h"

#include "Engine/Graphics/RenderDevice.h"

namespace Engine
{
	IndexBuffer::IndexBuffer(ID3D11Device& deviceRef,
	                         const RenderData& renderDataRef):
		Buffer(renderDataRef.IndexCount, sizeof(uint32_t))
	{
		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.ByteWidth         = (UINT)ByteSize();
		indexBufferDesc.Usage             = D3D11_USAGE_DEFAULT;
		indexBufferDesc.BindFlags         = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags    = 0;
		indexBufferDesc.MiscFlags         = 0;
		// bufferDesc.StructureByteStride = 0; // Might be needed for StructuredBuffers

		D3D11_SUBRESOURCE_DATA indexBufferData = {};
		indexBufferData.pSysMem                = renderDataRef.Indices;

		const HRESULT result = deviceRef.CreateBuffer(&indexBufferDesc,
		                                              &indexBufferData,
		                                              &m_Data);

		Debug::Assert(SUCCEEDED(result),
		              "Index buffer cannot be created!");
	}

	IndexBuffer::~IndexBuffer()
	{
		m_Data->Release();
	}
}
