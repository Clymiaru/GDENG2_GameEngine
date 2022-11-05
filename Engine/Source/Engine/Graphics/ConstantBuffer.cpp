#include "pch.h"
#include "ConstantBuffer.h"

#include "Renderer.h"

namespace Engine
{
	ConstantBuffer::ConstantBuffer(const void* buffer,
	                               const size_t bufferSize) :
		Buffer(1, bufferSize)
	{
		D3D11_BUFFER_DESC constantBufferDesc;
		constantBufferDesc.ByteWidth           = (UINT)ByteSize();
		constantBufferDesc.Usage               = D3D11_USAGE_DEFAULT;
		constantBufferDesc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.CPUAccessFlags      = 0;
		constantBufferDesc.MiscFlags           = 0;
		constantBufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA constantBufferInitData = {};
		constantBufferInitData.pSysMem                = buffer;

		const HRESULT result = Renderer::CreateBuffer(&constantBufferDesc,
		                                              &constantBufferInitData,
		                                              &m_Data);

		Debug::Assert(SUCCEEDED(result),
		              "Constant Buffer cannot be created!");
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
