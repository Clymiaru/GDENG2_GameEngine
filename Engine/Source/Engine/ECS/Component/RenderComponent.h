#pragma once
#include "Engine/Core/Core.h"
#include "Engine/ECS/Core/AComponent.h"

#include "Engine/Graphics/RenderData.h"

#include "Engine/Graphics/VertexShader.h"
#include "Engine/Graphics/PixelShader.h"

#include "Engine/Graphics/VertexBuffer.h"
#include "Engine/Graphics/IndexBuffer.h"
#include "Engine/Graphics/ConstantBuffer.h"

namespace Engine
{
	class Renderer;

	class Camera;

	// TODO: Abstract to material later on
	class RenderComponent final : public AComponent
	{
	public:
		RenderComponent(Entity& owner,
		                RenderData* renderData,
		                SharedPtr<VertexShader> vertexShader,
		                SharedPtr<PixelShader> pixelShader);

		~RenderComponent() override;

		void Draw(Camera& camera) const;

		MAKE_COMPONENT(Render)

		RenderComponent(const RenderComponent&) = delete;
	
		RenderComponent& operator=(const RenderComponent&) = delete;
	
		RenderComponent(RenderComponent&&) noexcept = delete;
	
		RenderComponent& operator=(RenderComponent&&) noexcept = delete;

		Color AlbedoColor = Color(1.0f, 1.0f, 1.0f, 1.0f);

	private:
		// Material
		//	Shader
		//		VertexShader
		//		PixelShader
		//	ConstantBuffers
		// Buffers
		//	VertexBuffer
		//	IndexBuffer

		UniquePtr<RenderData> m_RenderData{};

		SharedPtr<VertexShader> m_VertexShader{};

		SharedPtr<PixelShader> m_PixelShader{};

		UniquePtr<VertexBuffer> m_VertexBuffer{};

		UniquePtr<IndexBuffer> m_IndexBuffer{};

		UniquePtr<ConstantBuffer> m_ConstantBuffer{};
	};
}
