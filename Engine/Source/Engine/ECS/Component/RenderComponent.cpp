#include "pch.h"
#include "RenderComponent.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/ShaderLibrary.h"
#include "Engine/Math/Color.h"
#include "Engine/Math/Vector3.h"

struct Vertex
{
	Engine::Vector3Float Position;

	Engine::Color Color;
};

__declspec(align(16))
struct Constant
{
	DirectX::XMMATRIX View;

	DirectX::XMMATRIX Projection;

	DirectX::XMMATRIX Model;

	float Time;
};

namespace Engine
{
	RenderComponent::RenderComponent(Entity* owner) :
		AComponent{owner},
		m_VertexData{nullptr},
		m_VertexLayoutData{nullptr},
		m_IndexData{nullptr},
		m_VertexShader{nullptr},
		m_PixelShader{nullptr},
		m_VertexBuffer{nullptr},
		m_IndexBuffer{nullptr},
		m_ConstantBuffer{nullptr},
		m_Constant{nullptr}
	{
	}

	RenderComponent::~RenderComponent()
	{
	}

	void RenderComponent::Initialize(VertexData vertexData,
	                                 VertexLayoutData vertexLayoutData,
	                                 IndexData indexLayoutData,
	                                 const String shaderName,
	                                 void* constantBufferData,
	                                 size_t constantBufferDataSize)
	{
		m_VertexData       = std::move(&vertexData);
		m_VertexLayoutData = std::move(&vertexLayoutData);
		m_IndexData        = std::move(&indexLayoutData);
		m_VertexShader     = ShaderLibrary::GetShaderRef<VertexShader>(shaderName);
		m_PixelShader      = ShaderLibrary::GetShaderRef<PixelShader>(shaderName);
		
		m_Constant = new Constant{};

		// Do we have to create vertex, index buffers, and constant buffers here?
		m_VertexBuffer = CreateUniquePtr<VertexBuffer>(m_VertexData->VertexList,
		                                               sizeof(Vertex),
		                                               m_VertexData->VertexListCount,
		                                               m_VertexShader->GetByteCodeData(),
		                                               static_cast<uint32_t>(m_VertexShader->GetByteCodeSizeData()),
		                                               m_VertexLayoutData->VertexLayout,
		                                               m_VertexLayoutData->VertexLayoutCount);
		
		// m_IndexBuffer = CreateUniquePtr<IndexBuffer>(m_IndexData->IndexList,
		//                                              m_IndexData->IndexListCount);
		//
		// m_ConstantBuffer = CreateUniquePtr<ConstantBuffer>(constantBufferData, constantBufferDataSize);
	}

	void RenderComponent::Terminate()
	{
		// m_VertexBuffer->Release();
		// m_IndexBuffer->Release();
	}

	void RenderComponent::Draw(Renderer* rendererRef)
	{
		//rendererRef->UpdateConstantBuffer(*m_ConstantBuffer, newConstantData);

		// rendererRef->Draw(*m_VertexShader, *m_PixelShader,
		//                   *m_VertexBuffer, *m_IndexBuffer,
		//                   *m_ConstantBuffer, nullptr,
		//                   D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}
