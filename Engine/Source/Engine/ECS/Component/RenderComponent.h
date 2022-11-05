#pragma once

#include "AComponent.h"

#include "Engine/Core/Core.h"
#include "Engine/Graphics/RenderData.h"

struct SimpleChromaticAberrationConstantData;

namespace Engine
{
	class ConstantBuffer;

	class IndexBuffer;

	class PixelShader;

	class VertexShader;

	class VertexBuffer;

	class Renderer;

	class Camera;

	class RenderComponent final : public AComponent
	{
	public:
		RenderComponent(Entity& owner);

		~RenderComponent() override;

		void Initialize(VertexData* vertexData,
		                VertexLayoutData* vertexLayoutData,
		                IndexData* indexData,
		                size_t vertexDataSize,
		                String shaderName);

		void Terminate();

		void Update();

		void Draw(Camera& camera);

		MAKE_COMPONENT(Render)

	private:
		// Material
		//	Shader
		//		VertexShader
		//		PixelShader
		//	ConstantBuffers
		// Buffers
		//	VertexBuffer
		//	IndexBuffer
		
		VertexData* m_VertexData;

		VertexLayoutData* m_VertexLayoutData;

		IndexData* m_IndexData;

		SharedPtr<VertexShader> m_VertexShader;

		SharedPtr<PixelShader> m_PixelShader;

		UniquePtr<VertexBuffer> m_VertexBuffer;

		UniquePtr<IndexBuffer> m_IndexBuffer;

		UniquePtr<ConstantBuffer> m_ConstantBuffer;
	};
}
