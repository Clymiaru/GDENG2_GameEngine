#include "pch.h"
#include "IndexBuffer.h"

#include "Renderer.h"

#include "Engine/Core/Debug.h"

namespace Engine
{
	IndexBuffer::IndexBuffer(const uint32_t* indexList,
	                         const uint32_t indexListCount):
		Buffer(indexListCount, sizeof(uint32_t))
	{
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.Usage             = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth         = ByteSize();
		bufferDesc.BindFlags         = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags    = 0;
		bufferDesc.MiscFlags         = 0;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem                = indexList;

		const HRESULT result = Renderer::CreateBuffer(&bufferDesc, &initData, &m_Data);

		Debug::Assert(SUCCEEDED(result), "Index buffer cannot be created!");
	}

	IndexBuffer::~IndexBuffer()
	{
		m_Data->Release();
	}
}
