﻿#include "pch.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

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
	RenderComponent::RenderComponent(const EntityID& ownerID) :
		AComponent{ownerID},
		m_RenderData{nullptr},
		m_VertexShader{nullptr},
		m_PixelShader{nullptr} { }

	RenderComponent::RenderComponent(const EntityID& ownerID,
	                                 RenderData* renderData,
	                                 VertexShaderResourceRef vertexShaderResource,
	                                 PixelShaderResourceRef pixelShaderResource) :
		AComponent{ownerID},
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
	
	void RenderComponent::Draw(TransformComponent* transform, CameraComponent& camera)
	{
		if (transform == nullptr)
			return;
		
		RenderObjectData* constant = new RenderObjectData();
		constant->Model            = transform->GetLocalMatrix();
		constant->ViewProjection   = camera.GetViewProjMatrix();
		constant->SolidColor       = AlbedoColor;

		Application::GetRenderer().GetContext().UpdateBufferResource(&m_ConstantBuffer->GetData(), constant);
	
		Application::GetRenderer().GetContext().SetRenderData<VertexShader>(m_VertexShader->GetShader());
		Application::GetRenderer().GetContext().SetRenderData<PixelShader>(m_PixelShader->GetShader());
	
		Application::GetRenderer().GetContext().UploadShaderData<VertexShader>(*m_ConstantBuffer);
		Application::GetRenderer().GetContext().UploadShaderData<PixelShader>(*m_ConstantBuffer);
	
		Application::GetRenderer().GetContext().SetRenderData<VertexBuffer>(*m_VertexBuffer);
		Application::GetRenderer().GetContext().SetRenderData<IndexBuffer>(*m_IndexBuffer);
	
		Application::GetRenderer().GetContext().SetTopology(m_RenderData->Topology);
	
		Application::GetRenderer().GetContext().DrawIndexed(m_IndexBuffer->ElementCount(), 0);
	}

	// RenderComponent::RenderComponent(Entity& owner,
	//                                  RenderData* renderData,
	//                                  SharedPtr<VertexShader> vertexShader,
	//                                  SharedPtr<PixelShader> pixelShader) :
	// 	AComponent{owner},
	// 	m_RenderData{std::move(renderData)},
	// 	m_VertexShader{vertexShader},
	// 	m_PixelShader{pixelShader},
	// 	m_VertexBuffer{nullptr},
	// 	m_IndexBuffer{nullptr},
	// 	m_ConstantBuffer{nullptr}
	// {
	// 	if (renderData == nullptr)
	// 	{
	// 		Debug::Log("Attempting to Attach a RenderComponent to {0} with null RenderData!",
	// 		           owner.Name.c_str());
	// 		return;
	// 	}
	//
	// 	RenderObjectData* constant = new RenderObjectData();
	//
	// 	m_VertexBuffer = CreateUniquePtr<VertexBuffer>(*m_RenderData,
	// 	                                               *m_VertexShader);
	//
	// 	m_IndexBuffer = CreateUniquePtr<IndexBuffer>(*m_RenderData);
	//
	// 	m_ConstantBuffer = CreateUniquePtr<ConstantBuffer>(constant,
	// 	                                                   sizeof(RenderObjectData));
	// }
	//
	// RenderComponent::RenderComponent(Entity& owner,
	//                                  RenderData* renderData,
	//                                  SharedPtr<VertexShader> vertexShader,
	//                                  SharedPtr<PixelShader> pixelShader,
	//                                  StringView textureFilepath) :
	// 	AComponent{owner},
	// 	m_RenderData{std::move(renderData)},
	// 	m_VertexShader{vertexShader},
	// 	m_PixelShader{pixelShader},
	// 	m_VertexBuffer{nullptr},
	// 	m_IndexBuffer{nullptr},
	// 	m_ConstantBuffer{nullptr},
	// 	m_HasTexture{true}
	// {
	// 	if (renderData == nullptr)
	// 	{
	// 		Debug::Log("Attempting to Attach a RenderComponent to {0} with null RenderData!",
	// 		           owner.Name.c_str());
	// 		return;
	// 	}
	//
	// 	RenderObjectData* constant = new RenderObjectData();
	//
	// 	m_VertexBuffer = CreateUniquePtr<VertexBuffer>(*m_RenderData,
	// 	                                               *m_VertexShader);
	//
	// 	m_IndexBuffer = CreateUniquePtr<IndexBuffer>(*m_RenderData);
	//
	// 	m_ConstantBuffer = CreateUniquePtr<ConstantBuffer>(constant,
	// 	                                                   sizeof(RenderObjectData));
	//
	// 	// LoadTextureFromFile(textureFilepath.data(),
	// 	//                     &m_TextureView,
	// 	//                     &m_TextureWidth,
	// 	//                     &m_TextureHeight);
	// 	//
	// 	// D3D11_SAMPLER_DESC frameTextureSampler = {};
	// 	// frameTextureSampler.Filter             = D3D11_FILTER_MIN_MAG_MIP_POINT;
	// 	// frameTextureSampler.AddressU           = D3D11_TEXTURE_ADDRESS_CLAMP;
	// 	// frameTextureSampler.AddressV           = D3D11_TEXTURE_ADDRESS_CLAMP;
	// 	// frameTextureSampler.AddressW           = D3D11_TEXTURE_ADDRESS_CLAMP;
	// 	//
	// 	// Renderer::GetDevice().CreateSamplerState(&frameTextureSampler,
	// 	//                                          &m_TextureSampler);
	// }
	//
	// RenderComponent::~RenderComponent() = default;
	//
	// void RenderComponent::Draw(Camera& camera) const
	// {
	// 	RenderObjectData* constant = new RenderObjectData();
	// 	constant->Model            = m_EntityRef.Transform().GetLocalMatrix();
	// 	constant->ViewProjection   = camera.ViewProjMatrix();
	// 	constant->SolidColor       = AlbedoColor;
	//
	// 	Renderer::UpdateConstantBuffer(*m_ConstantBuffer, constant);
	//
	// 	Renderer::GetDeviceContext().SetRenderData<VertexShader>(*m_VertexShader);
	// 	Renderer::GetDeviceContext().SetRenderData<PixelShader>(*m_PixelShader);
	//
	// 	Renderer::GetDeviceContext().UploadShaderData<VertexShader>(*m_ConstantBuffer);
	// 	Renderer::GetDeviceContext().UploadShaderData<PixelShader>(*m_ConstantBuffer);
	//
	// 	// if (m_HasTexture)
	// 	// {
	// 	// 	Renderer::GetDeviceContext().GetContext().PSSetShaderResources(0,
	// 	// 																   1,
	// 	// 																   &m_TextureView);
	// 	// 	Renderer::GetDeviceContext().GetContext().PSSetSamplers(0,
	// 	// 															1,
	// 	// 															&m_TextureSampler);
	// 	// }
	//
	// 	Renderer::GetDeviceContext().SetRenderData<VertexBuffer>(*m_VertexBuffer);
	// 	Renderer::GetDeviceContext().SetRenderData<IndexBuffer>(*m_IndexBuffer);
	//
	// 	Renderer::GetDeviceContext().SetTopology(m_RenderData->Topology);
	//
	// 	Renderer::GetDeviceContext().DrawIndexed(m_IndexBuffer->ElementCount(), 0);
	// }
}
