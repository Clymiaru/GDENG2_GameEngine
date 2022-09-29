#include "pch.h"

#include "Engine/Graphics/Core/ConstantBuffer.h"
#include "Engine/Graphics/Core/DeviceContext.h"
#include "Engine/Graphics/Core/GraphicsEngine.h"

Engine::ConstantBuffer::ConstantBuffer() :
	m_BufferData{nullptr}
{
}

Engine::ConstantBuffer::~ConstantBuffer() = default;

auto Engine::ConstantBuffer::Load(const void* buffer,
                                  const UINT bufferSize) -> bool
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

	if (FAILED(GraphicsEngine::GetInstance().m_D3DDevice->CreateBuffer(&bufferDesc, &initData, &m_BufferData)))
	{
		return false;
	}
	return true;
}

auto Engine::ConstantBuffer::Update(const Scope<DeviceContext>& deviceContext,
                                    void* buffer) -> void
{
	deviceContext->m_DeviceContext->UpdateSubresource(m_BufferData,
	                                                  NULL,
	                                                  nullptr,
	                                                  buffer,
	                                                  NULL,
	                                                  NULL);
}

auto Engine::ConstantBuffer::Release() const -> bool
{
	if (m_BufferData)
		m_BufferData->Release();
	return true;
}
