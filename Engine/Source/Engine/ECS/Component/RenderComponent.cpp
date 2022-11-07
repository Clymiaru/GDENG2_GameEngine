#include "pch.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

#include "Engine/ECS/Core/Entity.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/ShaderLibrary.h"
#include "Engine/ECS/Entity/Camera.h"

__declspec(align(16))
struct RenderObjectData
{
	Engine::Matrix4 Model;

	Engine::Matrix4 ViewProjection;

	Engine::Color SolidColor;
};

namespace Engine
{
	RenderComponent::RenderComponent(Entity& owner,
	                                 RenderData* renderData,
	                                 SharedPtr<VertexShader> vertexShader,
	                                 SharedPtr<PixelShader> pixelShader) :
		AComponent{owner},
		m_RenderData{std::move(renderData)},
		m_VertexShader{vertexShader},
		m_PixelShader{pixelShader},
		m_VertexBuffer{nullptr},
		m_IndexBuffer{nullptr},
		m_ConstantBuffer{nullptr}
	{
		if (renderData == nullptr)
		{
			Debug::Log("Attempting to Attach a RenderComponent to {0} with null RenderData!",
			           owner.Name.c_str());
			return;
		}

		RenderObjectData* constant = new RenderObjectData();

		m_VertexBuffer = CreateUniquePtr<VertexBuffer>(*m_RenderData,
		                                               *m_VertexShader);

		m_IndexBuffer = CreateUniquePtr<IndexBuffer>(*m_RenderData);

		m_ConstantBuffer = CreateUniquePtr<ConstantBuffer>(constant,
		                                                   sizeof(RenderObjectData));
	}

	RenderComponent::~RenderComponent() = default;

	void RenderComponent::Draw(Camera& camera) const
	{
		RenderObjectData* constant = new RenderObjectData();
		constant->Model            = m_EntityRef.Transform().LocalMatrix();
		constant->ViewProjection   = camera.ViewProjMatrix();
		constant->SolidColor       = AlbedoColor;

		Renderer::UpdateConstantBuffer(*m_ConstantBuffer, constant);

		Renderer::GetDeviceContext().SetRenderData<VertexShader>(*m_VertexShader);
		Renderer::GetDeviceContext().SetRenderData<PixelShader>(*m_PixelShader);


		Renderer::GetDeviceContext().UploadShaderData<VertexShader>(*m_ConstantBuffer);
		Renderer::GetDeviceContext().UploadShaderData<PixelShader>(*m_ConstantBuffer);

		/* Textures
		Renderer::GetDeviceContext().GetContext().PSSetShaderResources(0,
																	   1,
																	   frameReferenceViews.data());
		Renderer::GetDeviceContext().GetContext().PSSetSamplers(0,
																1,
																&m_TextureSampler);
		*/

		Renderer::GetDeviceContext().SetRenderData<VertexBuffer>(*m_VertexBuffer);
		Renderer::GetDeviceContext().SetRenderData<IndexBuffer>(*m_IndexBuffer);

		Renderer::GetDeviceContext().SetTopology(m_RenderData->Topology);

		Renderer::GetDeviceContext().DrawIndexed(m_IndexBuffer->ElementCount(), 0);
	}
}
