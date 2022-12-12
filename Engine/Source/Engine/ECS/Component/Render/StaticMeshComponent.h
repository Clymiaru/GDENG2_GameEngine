#pragma once
#include "Engine/Core/Core.h"
#include "Engine/Math/Math.h"

#include "Engine/Graphics/RenderData.h"
#include "Engine/ResourceManagement/Core/Resource.h"

#include "Engine/ECS/Core/AComponent.h"
#include "Engine/ECS/Component/CameraComponent.h"
#include "Engine/ECS/Component/EditorCameraComponent.h"
#include "Engine/ECS/Component/TransformComponent.h"

namespace Engine
{
	class StaticMeshComponent final : public AComponent
	{
	public:
		explicit StaticMeshComponent(const EntityID& ownerID,
								 SharedPtr<TransformComponent> transform);

		explicit StaticMeshComponent(const EntityID& ownerID,
								 RenderData* renderData,
								 VertexShaderResourceRef vertexShaderResource,
								 PixelShaderResourceRef pixelShaderResource,
								 SharedPtr<TransformComponent> transform);

		~StaticMeshComponent() override = default;

		void SetTexture(SharedPtr<TextureResource> texture);

		void RemoveTexture();

		void Draw(CameraComponent& camera);

		void Draw(EditorCameraComponent& camera);
		
		MAKE_COMPONENT(Render)

		StaticMeshComponent(const StaticMeshComponent&)                = delete;
		StaticMeshComponent& operator=(const StaticMeshComponent&)     = delete;
		StaticMeshComponent(StaticMeshComponent&&) noexcept            = delete;
		StaticMeshComponent& operator=(StaticMeshComponent&&) noexcept = delete;

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
	};
}
