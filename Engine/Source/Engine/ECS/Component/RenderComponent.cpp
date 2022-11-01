#include "pch.h"
#include "RenderComponent.h"

#include "TransformComponent.h"

#include "Engine/ECS/Entity/Entity.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/ShaderLibrary.h"
#include "Engine/Math/Color.h"
#include "Engine/Math/Vector3.h"

#include "Engine/ECS/Entity/Camera.h"

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

	void RenderComponent::Initialize(VertexData* vertexData,
									VertexLayoutData* vertexLayoutData,
									IndexData* indexData,
									size_t vertexDataSize,
									String shaderName)
	{
		m_VertexData       = vertexData;
		m_VertexLayoutData = vertexLayoutData;
		m_IndexData        = indexData;
		m_VertexShader     = ShaderLibrary::GetShaderRef<VertexShader>(shaderName);
		m_PixelShader      = ShaderLibrary::GetShaderRef<PixelShader>(shaderName);

		m_Constant = new Constant{};

		// Do we have to create vertex, index buffers, and constant buffers here?
		m_VertexBuffer = CreateUniquePtr<VertexBuffer>(m_VertexData->VertexList,
		                                               vertexDataSize,
		                                               m_VertexData->VertexListCount,
		                                               m_VertexShader->GetByteCodeData(),
		                                               static_cast<uint32_t>(m_VertexShader->GetByteCodeSizeData()),
		                                               m_VertexLayoutData->VertexLayout,
		                                               m_VertexLayoutData->VertexLayoutCount);

		m_IndexBuffer = CreateUniquePtr<IndexBuffer>(m_IndexData->IndexList,
		                                             m_IndexData->IndexListCount);

		m_ConstantBuffer = CreateUniquePtr<ConstantBuffer>(m_Constant, sizeof(Constant));
	}

	void RenderComponent::Terminate()
	{
		m_VertexBuffer.release();
		m_IndexBuffer.release();
		m_ConstantBuffer.release();
	}

	void RenderComponent::Update()
	{
		m_Constant->Time       = 0;
		m_Constant->Model      = m_EntityRef->Transform().LocalMatrix();
		m_Constant->Projection = Matrix4();
		m_Constant->View       = Matrix4();
	}

	void RenderComponent::Draw(Camera& camera)
	{
		m_Constant->Time       = 0;
		m_Constant->Model      = m_EntityRef->Transform().LocalMatrix();
		m_Constant->Projection = camera.ViewProjMatrix();
		m_Constant->View       = Matrix4();

		Renderer::UpdateConstantBuffer(*m_ConstantBuffer, m_Constant);

		Renderer::Draw(*m_VertexShader, *m_PixelShader,
		               *m_VertexBuffer, *m_IndexBuffer,
		               *m_ConstantBuffer, m_Constant,
		               D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	// void RenderComponent::Draw()
	// {
	// 	Update();
	// 	
	// 	Renderer::UpdateConstantBuffer(*m_ConstantBuffer, m_Constant);
	//
	// 	Renderer::Draw(*m_VertexShader, *m_PixelShader,
	// 	                  *m_VertexBuffer, *m_IndexBuffer,
	// 	                  *m_ConstantBuffer, m_Constant,
	// 	                  D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// }
}
