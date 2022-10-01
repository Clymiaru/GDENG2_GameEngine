#include "pch.h"
#include "VertexBuffer.h"

#include "RenderSystem.h"

Engine::VertexBuffer::VertexBuffer() :
	m_VertexSize{0},
	m_ListSize{0},
	m_Buffer(nullptr),
	m_Layout(nullptr)
{
}

Engine::VertexBuffer::~VertexBuffer()
{
}

auto Engine::VertexBuffer::GetVertexListSize() const -> UINT
{
	return m_ListSize;
}

auto Engine::VertexBuffer::Load(void* listOfVertices,
                                UINT vertexSize,
                                UINT listSize,
                                void* shaderByteCode,
                                UINT byteShaderSize,
                                D3D11_INPUT_ELEMENT_DESC* indexLayout,
                                size_t indexLayoutSize) -> bool
{
	if (m_Buffer)
		m_Buffer->Release();
	if (m_Layout)
		m_Layout->Release();

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage             = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth         = vertexSize * listSize;
	bufferDesc.BindFlags         = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags    = 0;
	bufferDesc.MiscFlags         = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem                = listOfVertices;
	m_VertexSize                    = vertexSize;
	m_ListSize                      = listSize;
	if (FAILED(RenderSystem::GetInstance().GetDevice()->CreateBuffer(&bufferDesc, &initData, &m_Buffer)))
	{
		return false;
	}

	auto result = RenderSystem::GetInstance().GetDevice()->CreateInputLayout(
		indexLayout, indexLayoutSize, shaderByteCode, byteShaderSize, &m_Layout);

	if (FAILED(result))
	{
		return false;
	}
	return true;
}

auto Engine::VertexBuffer::Release() const -> void
{
	m_Layout->Release();
	m_Buffer->Release();
}
