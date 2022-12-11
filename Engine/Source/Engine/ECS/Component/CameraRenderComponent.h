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
	class CameraRenderer;

	class Camera;
	class CameraRenderComponent final : public AComponent
	{
	public:
		explicit CameraRenderComponent(const EntityID& ownerID,
			SharedPtr<TransformComponent> transform);

		explicit CameraRenderComponent(const EntityID& ownerID,
			RenderData* renderData,
			VertexShaderResourceRef vertexShaderResource,
			PixelShaderResourceRef pixelShaderResource,
			SharedPtr<TransformComponent> transform);

		~CameraRenderComponent() override = default;

		void SetTexture(SharedPtr<TextureResource> texture);

		void RemoveTexture();

		void Draw(CameraComponent& camera);

		void Draw(EditorCameraComponent& camera);

		MAKE_COMPONENT(CameraRender)

		CameraRenderComponent(const CameraRenderComponent&) = delete;
		CameraRenderComponent& operator=(const CameraRenderComponent&) = delete;
		CameraRenderComponent(CameraRenderComponent&&) noexcept = delete;
		CameraRenderComponent& operator=(CameraRenderComponent&&) noexcept = delete;

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

