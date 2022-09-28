#include "Engine/Graphics/Core/ConstantBuffer.h"
#include "Engine/Graphics/Core/DeviceContext.h"
#include "Engine/Graphics/Core/GraphicsEngine.h"

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

	if (FAILED(GraphicsEngine::GetInstance().m_D3DDevice->CreateBuffer(&bufferDesc, &initData, &m_BufferData)))
	{
		return false;
	}
	return true;
}

void Engine::ConstantBuffer::Update(const Scope<DeviceContext>& deviceContext,
                                    void* buffer)
{
	deviceContext->m_DeviceContext->UpdateSubresource(m_BufferData,
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
