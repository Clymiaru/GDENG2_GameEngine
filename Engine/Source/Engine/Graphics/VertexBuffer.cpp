#include "pch.h"
// #include "VertexBuffer.h"
//
// #include "RenderSystem.h"
//
// namespace Engine
// {
// 	VertexBuffer::VertexBuffer(const void* vertexList,
// 	                           size_t vertexDataSize,
// 	                           Uint vertexListCount,
// 	                           const void* shaderByteCode,
// 	                           size_t shaderByteCodeSize,
// 	                           const D3D11_INPUT_ELEMENT_DESC* indexLayout,
// 	                           size_t indexLayoutSize) :
// 		Buffer(vertexListCount, vertexDataSize),
// 		m_DataLayout{nullptr}
// 	{
// 		if (m_Data)
// 			m_Data->Release();
// 		if (m_DataLayout)
// 			m_DataLayout->Release();
//
// 		D3D11_BUFFER_DESC bufferDesc = {};
// 		bufferDesc.Usage             = D3D11_USAGE_DEFAULT;
// 		bufferDesc.ByteWidth         = ByteSize();
// 		bufferDesc.BindFlags         = D3D11_BIND_VERTEX_BUFFER;
// 		bufferDesc.CPUAccessFlags    = 0;
// 		bufferDesc.MiscFlags         = 0;
//
// 		D3D11_SUBRESOURCE_DATA initData = {};
// 		initData.pSysMem                = vertexList;
//
// 		const auto result = RenderSystem::GetDevice().CreateBuffer(&bufferDesc, &initData, &m_Data);
//
// 		ENGINE_ASSERT(SUCCEEDED(result), "Vertex buffer cannot be created!")
//
// 		const auto layoutResult =
// 				RenderSystem::GetDevice().CreateInputLayout(
// 					indexLayout,
// 					indexLayoutSize,
// 					shaderByteCode,
// 					shaderByteCodeSize,
// 					&m_DataLayout);
//
// 		ENGINE_ASSERT(SUCCEEDED(layoutResult), "Vertex layout cannot be created!")
// 	}
//
// 	VertexBuffer::~VertexBuffer()
// 	{
// 	}
//
// 	void VertexBuffer::Release()
// 	{
// 		m_DataLayout->Release();
// 		m_Data->Release();
// 	}
// }
