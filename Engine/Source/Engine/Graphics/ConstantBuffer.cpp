#include "pch.h"

#include "Engine/Graphics/ConstantBuffer.h"

#include "RenderSystem.h"
#include "Renderer.h"

#include "Engine/Core/Debug.h"
#include "Engine/Graphics/DeviceContext.h"

Engine::ConstantBuffer::ConstantBuffer(const void* buffer,
                                       const size_t bufferSize,
                                       Renderer* renderer) :
	Buffer(1, bufferSize, renderer)
{
	if (m_Data != nullptr)
		m_Data->Release();

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage             = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth         = (UINT)ByteSize();
	bufferDesc.BindFlags         = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags    = 0;
	bufferDesc.MiscFlags         = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem                = buffer;

	auto result = renderer->CreateBuffer(&bufferDesc,
	                                     &initData,
	                                     &m_Data);

	ENGINE_ASSERT_TRUE(SUCCEEDED(result), "Constant Buffer cannot be created!")
}

Engine::ConstantBuffer::~ConstantBuffer() = default;

void Engine::ConstantBuffer::Release()
{
	if (m_Data != nullptr)
		m_Data->Release();
}
