#include "pch.h"
#include "IndexBuffer.h"

#include "RenderSystem.h"

Engine::IndexBuffer::IndexBuffer(const Uint* indexList,
                                 const Uint indexListCount):
	Buffer(indexListCount, sizeof(Uint))
{
	if (m_Data)
		m_Data->Release();

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage             = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth         = ByteSize();
	bufferDesc.BindFlags         = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags    = 0;
	bufferDesc.MiscFlags         = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem                = indexList;

	const HRESULT result = RenderSystem::GetDevice().CreateBuffer(&bufferDesc, &initData, &m_Data);

	ENGINE_ASSERT(SUCCEEDED(result), "Index buffer cannot be created!")
}

Engine::IndexBuffer::~IndexBuffer()
{
}

void Engine::IndexBuffer::Release()
{
	m_Data->Release();
}
