#pragma once
#include "Engine/Core/Core.h"
#include "Engine/Math/Math.h"

#include "Engine/Graphics/RenderData.h"
#include "Engine/ResourceManagement/Core/Resource.h"

#include "Engine/ECS/Core/AComponent.h"
#include "CameraComponent.h"
#include "EditorCameraComponent.h"
#include "TransformComponent.h"

namespace Engine
{
	class Renderer;

	class Camera;

	class RenderComponent final : public AComponent
	{
	public:
		explicit RenderComponent(const EntityID& ownerID,
		                         SharedPtr<TransformComponent> transform);

		explicit RenderComponent(const EntityID& ownerID,
		                         RenderData* renderData,
		                         VertexShaderResourceRef vertexShaderResource,
		                         PixelShaderResourceRef pixelShaderResource,
		                         SharedPtr<TransformComponent> transform);

		~RenderComponent() override = default;

		void SetTexture(SharedPtr<TextureResource> texture);

		void RemoveTexture();

		void Draw(CameraComponent& camera);

		void Draw(EditorCameraComponent& camera);
		
		MAKE_COMPONENT(Render)

		RenderComponent(const RenderComponent&)                = delete;
		RenderComponent& operator=(const RenderComponent&)     = delete;
		RenderComponent(RenderComponent&&) noexcept            = delete;
		RenderComponent& operator=(RenderComponent&&) noexcept = delete;

		Color AlbedoColor = Color(1.0f, 1.0f, 1.0f, 1.0f);

	private:
		// Material
		//	Shader
		//		VertexShader
		//		PixelShader
		//	ShaderData
		SharedPtr<TransformComponent> m_Transform;
		SharedPtr<TextureResource> m_TextureResource;
		
		UniquePtr<RenderData> m_RenderData{};
		
		VertexShaderResourceRef m_VertexShader{};
		PixelShaderResourceRef m_PixelShader{};
		
		UniquePtr<VertexBuffer> m_VertexBuffer{};
		UniquePtr<IndexBuffer> m_IndexBuffer{};
		
		UniquePtr<ConstantBuffer> m_ConstantBuffer{};

		// bool m_HasTexture = false;
		//
		// ID3D11ShaderResourceView* m_TextureView = nullptr;
		//
		// int m_TextureWidth;
		//
		// int m_TextureHeight;
		//
		// ID3D11SamplerState* m_TextureSampler = nullptr;
	};
}
