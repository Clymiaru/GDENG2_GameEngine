#include "pch.h"
#include "IndexBuffer.h"

#include "RenderSystem.h"
#include "Renderer.h"

#include "Engine/Core/Debug.h"

namespace Engine
{
	IndexBuffer::IndexBuffer(const uint32_t* indexList,
	                         const uint32_t indexListCount,
	                         Renderer* renderer):
		Buffer(indexListCount, sizeof(uint32_t), renderer)
	{
		if (m_Data)
			m_Data->Release();

		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.Usage             = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth         = (UINT)ByteSize();
		bufferDesc.BindFlags         = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags    = 0;
		bufferDesc.MiscFlags         = 0;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem                = indexList;

		const HRESULT result = renderer->CreateBuffer(&bufferDesc, &initData, &m_Data);

		ENGINE_ASSERT_TRUE(SUCCEEDED(result), "Index buffer cannot be created!")
	}

	IndexBuffer::~IndexBuffer()
	{
	}

	void IndexBuffer::Release()
	{
		m_Data->Release();
	}
}
