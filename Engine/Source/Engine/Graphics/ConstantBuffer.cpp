#include "pch.h"

#include "Engine/Graphics/ConstantBuffer.h"

#include "RenderSystem.h"

#include "Engine/Graphics/DeviceContext.h"

Engine::ConstantBuffer::ConstantBuffer() :
	m_BufferData{nullptr}
{
}

Engine::ConstantBuffer::~ConstantBuffer() = default;

bool Engine::ConstantBuffer::Load(const void* buffer,
                                  const UINT bufferSize)
{
	if (m_BufferData != nullptr)
		m_BufferData->Release();

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage             = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth         = bufferSize;
	bufferDesc.BindFlags         = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags    = 0;
	bufferDesc.MiscFlags         = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem                = buffer;

	if (FAILED(RenderSystem::GetDevice().CreateBuffer(&bufferDesc,
		&initData,
		&m_BufferData)))
	{
		return false;
	}
	return true;
}

void Engine::ConstantBuffer::Update(DeviceContext& deviceContext,
                                    void* buffer) const
{
	deviceContext.m_DeviceContext->UpdateSubresource(m_BufferData,
	                                                 NULL,
	                                                 nullptr,
	                                                 buffer,
	                                                 NULL,
	                                                 NULL);
}

bool Engine::ConstantBuffer::Release() const
{
	if (m_BufferData)
		m_BufferData->Release();
	return true;
}
