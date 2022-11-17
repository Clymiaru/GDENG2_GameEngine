#include "pch.h"
#include "ConstantBuffer.h"

#include "Engine/Graphics/RenderDevice.h"

namespace Engine
{
	ConstantBuffer::ConstantBuffer(ID3D11Device& deviceRef,
	                               const void* bufferData,
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
		constantBufferInitData.pSysMem                = bufferData;

		const HRESULT result = deviceRef.CreateBuffer(&constantBufferDesc,
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

	void ConstantBuffer::Update(ID3D11DeviceContext& deviceContext,
	                            const void* updatedBufferData) const
	{
		deviceContext.UpdateSubresource(m_Data, NULL, nullptr,
		                                updatedBufferData, NULL, NULL);
	}
}
