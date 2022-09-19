#include "VertexBuffer.h"
#include "Engine/Graphics/GraphicsEngine.h"

Engine::VertexBuffer::VertexBuffer() :
	m_Buffer(nullptr),
	m_Layout(nullptr)
{
}

Engine::VertexBuffer::~VertexBuffer()
{
}

bool Engine::VertexBuffer::Load(void* listOfVertices, 
	UINT vertexSize, 
	UINT listSize,
	void* shaderByteCode,
	UINT byteShaderSize)
{

	if (m_Buffer)
		m_Buffer->Release();

	if (m_Layout)
		m_Layout->Release();

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = vertexSize * listSize;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = listOfVertices;

	m_VertexSize = vertexSize;
	m_ListSize = listSize;


	if (FAILED(GraphicsEngine::GetInstance().m_D3DDevice->CreateBuffer(&bufferDesc, &initData, &m_Buffer)))
	{
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC indexLayout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	UINT layoutSize = ARRAYSIZE(indexLayout);

	if (FAILED(GraphicsEngine::GetInstance().m_D3DDevice->CreateInputLayout(indexLayout, layoutSize, shaderByteCode, layoutSize, &m_Layout)))
	{
		return false;
	}

	return true;
}

bool Engine::VertexBuffer::Release()
{
	m_Layout->Release();
	m_Buffer->Release();
	delete this;
	return true;
}
