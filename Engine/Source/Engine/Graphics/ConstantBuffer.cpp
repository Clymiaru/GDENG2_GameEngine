#include "pch.h"

#include "Engine/Graphics/ConstantBuffer.h"

#include "RenderSystem.h"

#include "Engine/Graphics/DeviceContext.h"

Engine::ConstantBuffer::ConstantBuffer(const void* buffer,
                                       const size_t bufferSize) :
	Buffer(1, bufferSize)
{
	if (m_Data != nullptr)
		m_Data->Release();

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage             = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth         = bufferSize;
	bufferDesc.BindFlags         = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags    = 0;
	bufferDesc.MiscFlags         = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem                = buffer;

	auto result = RenderSystem::GetDevice().CreateBuffer(&bufferDesc,
	                                                     &initData,
	                                                     &m_Data);

	ENGINE_ASSERT(SUCCEEDED(result), "Constant Buffer cannot be created!")
}

Engine::ConstantBuffer::~ConstantBuffer() = default;

void Engine::ConstantBuffer::Release()
{
	if (m_Data != nullptr)
		m_Data->Release();
}
