#include "pch.h"
#include "IndexBuffer.h"

#include "RenderSystem.h"

Engine::IndexBuffer::IndexBuffer():
	m_Data{nullptr},
	m_DataCount{0}
{
}

Engine::IndexBuffer::~IndexBuffer()
{
	m_Data->Release();
}

auto Engine::IndexBuffer::GetCount() const -> Uint
{
	return m_DataCount;
}

auto Engine::IndexBuffer::GetSize() const -> Uint
{
	return sizeof(Uint) * m_DataCount;
}

auto Engine::IndexBuffer::Load(const Uint* indexList,
                               const Uint indexListCount) -> bool
{
	if (m_Data)
		m_Data->Release();

	m_DataCount = indexListCount;

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage             = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth         = GetSize();
	bufferDesc.BindFlags         = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags    = 0;
	bufferDesc.MiscFlags         = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem                = indexList;

	if (FAILED(RenderSystem::GetInstance().GetDevice().CreateBuffer(&bufferDesc, &initData, &m_Data)))
	{
		return false;
	}

	return true;
}
