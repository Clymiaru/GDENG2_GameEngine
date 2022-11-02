#include "pch.h"
#include "ConstantBuffer.h"

#include <d3d11.h>

#include "Engine/Core/Debug.h"
#include "Engine/Graphics/DeviceContext.h"
#include "Renderer.h"



namespace Engine
{
	ConstantBuffer::ConstantBuffer(const void* buffer,
	                               const size_t bufferSize) :
		Buffer(1, bufferSize)
	{
		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.ByteWidth           = (UINT)ByteSize();
		bufferDesc.Usage               = D3D11_USAGE_DEFAULT;
		bufferDesc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags      = 0;
		bufferDesc.MiscFlags           = 0;
		bufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem                = buffer;

		auto result = Renderer::CreateBuffer(&bufferDesc,
		                                     &initData,
		                                     &m_Data);

		Debug::Assert(SUCCEEDED(result), "Constant Buffer cannot be created!");
	}

	ConstantBuffer::~ConstantBuffer()
	{
		if (m_Data != nullptr)
			m_Data->Release();
	}

	void ConstantBuffer::Update(const DeviceContext& deviceContext,
	                            const void* updatedBufferData) const
	{
		deviceContext.UpdateBufferResource(m_Data,
		                                   updatedBufferData);
	}
}
