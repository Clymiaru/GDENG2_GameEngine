#include "pch.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

#include "Engine/ResourceManagement/Core/ResourceSystem.h"

// #include "Engine/Graphics/Renderer.h"
// #include "Engine/Graphics/ShaderLibrary.h"
// #include "Engine/ECS/Entity/Camera.h"

__declspec(align(16))
struct RenderObjectData
{
	Engine::Matrix4 Model;

	Engine::Matrix4 ViewProjection;

	Engine::Color SolidColor;
};

namespace Engine
{
	RenderComponent::RenderComponent(const EntityID& ownerID,
	                                 SharedPtr<TransformComponent> transform) :
		AComponent{ownerID},
		m_Transform{transform},
		m_TextureResource{nullptr},
		m_RenderData{nullptr},
		m_VertexShader{nullptr},
		m_PixelShader{nullptr},
		m_VertexBuffer{nullptr},
		m_IndexBuffer{nullptr},
		m_ConstantBuffer{nullptr} { }

	RenderComponent::RenderComponent(const EntityID& ownerID,
	                                 RenderData* renderData,
	                                 VertexShaderResourceRef vertexShaderResource,
	                                 PixelShaderResourceRef pixelShaderResource,
	                                 SharedPtr<TransformComponent> transform) :
		AComponent{ownerID},
		m_Transform{transform},
		m_TextureResource{nullptr},
		m_RenderData{std::move(renderData)},
		m_VertexShader{vertexShaderResource},
		m_PixelShader{pixelShaderResource},
		m_VertexBuffer{nullptr},
		m_IndexBuffer{nullptr},
		m_ConstantBuffer{nullptr}
	{
		if (renderData == nullptr)
		{
			Debug::Log("Attempting to Attach a RenderComponent to Cube with null RenderData!");
			return;
		}

		const RenderObjectData* constant = new RenderObjectData();

		m_VertexBuffer = Application::GetRenderer().GetDevice().CreateVertexBuffer(*m_RenderData,
		                                                                           m_VertexShader->GetShader());

		m_IndexBuffer = Application::GetRenderer().GetDevice().CreateIndexBuffer(*m_RenderData);

		m_ConstantBuffer = Application::GetRenderer().GetDevice().CreateConstantBuffer(constant,
		                                                                               sizeof(RenderObjectData));
	}

	void RenderComponent::SetTexture(const SharedPtr<TextureResource> texture)
	{
		m_TextureResource = texture;
	}

	void RenderComponent::RemoveTexture()
	{
		m_TextureResource = nullptr;
	}

	void RenderComponent::Draw(CameraComponent& camera)
	{
		RenderObjectData* constant = new RenderObjectData();
		constant->Model            = m_Transform->GetLocalMatrix();
		constant->ViewProjection   = camera.GetViewProjMatrix();
		constant->SolidColor       = AlbedoColor;

		Application::GetRenderer().GetContext().UpdateBufferResource(&m_ConstantBuffer->GetData(), constant);

		Application::GetRenderer().GetContext().Bind<VertexShader>(m_VertexShader->GetShader());
		Application::GetRenderer().GetContext().Bind<PixelShader>(m_PixelShader->GetShader());

		Application::GetRenderer().GetContext().Bind<VertexShader>(0, *m_ConstantBuffer);
		Application::GetRenderer().GetContext().Bind<PixelShader>(0, *m_ConstantBuffer);

		std::vector<ID3D11ShaderResourceView*> textureSRV = {};
		if (m_TextureResource != nullptr)
		{
			textureSRV.push_back(&m_TextureResource->GetTexture().GetView());
		}
		else
		{
			textureSRV.push_back(nullptr);
		}

		Application::GetRenderer().GetContext().Bind<PixelShader>(0,
		                                                          1,
		                                                          textureSRV.data());

		std::vector<ID3D11SamplerState*> textureSampler = {};
		if (m_TextureResource != nullptr)
		{
			textureSampler.push_back(&m_TextureResource->GetTexture().GetSampler());
		}
		else
		{
			textureSampler.push_back(nullptr);
		}
		Application::GetRenderer().GetContext().Bind<PixelShader>(0,
		                                                          1,
		                                                          textureSampler.data());

		Application::GetRenderer().GetContext().Bind<VertexBuffer>(*m_VertexBuffer);
		Application::GetRenderer().GetContext().Bind<IndexBuffer>(*m_IndexBuffer);

		Application::GetRenderer().GetContext().Bind(m_RenderData->Topology);

		Application::GetRenderer().GetContext().DrawIndexed(m_IndexBuffer->ElementCount(), 0);
	}

	void RenderComponent::Draw(EditorCameraComponent& camera)
	{
		RenderObjectData* constant = new RenderObjectData();
		constant->Model            = m_Transform->GetLocalMatrix();
		constant->ViewProjection   = camera.GetViewProjMatrix();
		constant->SolidColor       = AlbedoColor;

		Application::GetRenderer().GetContext().UpdateBufferResource(&m_ConstantBuffer->GetData(), constant);

		Application::GetRenderer().GetContext().Bind<VertexShader>(m_VertexShader->GetShader());
		Application::GetRenderer().GetContext().Bind<PixelShader>(m_PixelShader->GetShader());

		Application::GetRenderer().GetContext().Bind<VertexShader>(0, *m_ConstantBuffer);
		Application::GetRenderer().GetContext().Bind<PixelShader>(0, *m_ConstantBuffer);

		std::vector<ID3D11ShaderResourceView*> textureSRV = {};
		if (m_TextureResource != nullptr)
		{
			textureSRV.push_back(&m_TextureResource->GetTexture().GetView());
		}
		else
		{
			textureSRV.push_back(nullptr);
		}

		Application::GetRenderer().GetContext().Bind<PixelShader>(0,
		                                                          1,
		                                                          textureSRV.data());

		std::vector<ID3D11SamplerState*> textureSampler = {};
		if (m_TextureResource != nullptr)
		{
			textureSampler.push_back(&m_TextureResource->GetTexture().GetSampler());
		}
		else
		{
			textureSampler.push_back(nullptr);
		}
		Application::GetRenderer().GetContext().Bind<PixelShader>(0,
		                                                          1,
		                                                          textureSampler.data());

		Application::GetRenderer().GetContext().Bind<VertexBuffer>(*m_VertexBuffer);
		Application::GetRenderer().GetContext().Bind<IndexBuffer>(*m_IndexBuffer);

		Application::GetRenderer().GetContext().Bind(m_RenderData->Topology);

		Application::GetRenderer().GetContext().DrawIndexed(m_IndexBuffer->ElementCount(), 0);
	}
}
