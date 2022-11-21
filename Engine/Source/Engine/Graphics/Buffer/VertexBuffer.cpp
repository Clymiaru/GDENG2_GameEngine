#include "pch.h"
#include "VertexBuffer.h"

#include "Engine/Graphics/RenderDevice.h"

namespace Engine
{
	VertexBuffer::VertexBuffer(ID3D11Device& deviceRef,
	                           const RenderData& renderDataRef,
	                           const Shader& shaderRef) :
		Buffer(renderDataRef.VertexCount, renderDataRef.VertexSize),
		m_DataLayout{nullptr}
	{
		D3D11_BUFFER_DESC vertexBufferDesc = {};
		vertexBufferDesc.ByteWidth         = (UINT)ByteSize();
		vertexBufferDesc.Usage             = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.BindFlags         = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags    = 0;
		vertexBufferDesc.MiscFlags         = 0;
		// bufferDesc.StructureByteStride = 0; // Might be needed for StructuredBuffers  

		D3D11_SUBRESOURCE_DATA vertexBufferInitData = {};
		vertexBufferInitData.pSysMem                = renderDataRef.Vertices;

		HRESULT result = deviceRef.CreateBuffer(&vertexBufferDesc,
		                                        &vertexBufferInitData,
		                                        &m_Data);

		Debug::Assert(SUCCEEDED(result),
		              "Vertex buffer cannot be created!");

		result = deviceRef.CreateInputLayout(renderDataRef.VertexLayout,
		                                     renderDataRef.VertexLayoutElementCount,
		                                     shaderRef.ByteCodeData(),
		                                     shaderRef.ByteCodeSizeData(),
		                                     &m_DataLayout);

		Debug::Assert(SUCCEEDED(result),
		              "Vertex layout cannot be created!");
	}

	VertexBuffer::~VertexBuffer()
	{
		m_DataLayout->Release();
		m_Data->Release();
	}
	
	ID3D11InputLayout& VertexBuffer::GetInputLayout() const
	{
		return *m_DataLayout;
	}
}
