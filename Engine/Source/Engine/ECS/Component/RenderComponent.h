#pragma once

#include <d3d11.h>

#include "AComponent.h"

#include "Engine/Core/Core.h"

#include "Engine/Graphics/ConstantBuffer.h"
#include "Engine/Graphics/IndexBuffer.h"
#include "Engine/Graphics/PixelShader.h"
#include "Engine/Graphics/VertexBuffer.h"
#include "Engine/Graphics/VertexShader.h"
#include "Engine/Math/Matrix4.h"

namespace Engine
{
	class Renderer;

	class RenderComponent final : public AComponent
	{
	public:
		struct VertexData
		{
			void* VertexList;

			size_t VertexListCount;
		};

		struct VertexLayoutData
		{
			D3D11_INPUT_ELEMENT_DESC* VertexLayout;

			size_t VertexLayoutCount;
		};

		struct IndexData
		{
			uint32_t* IndexList;

			size_t IndexListCount;
		};

		RenderComponent(Entity* owner);
		~RenderComponent() override;

		void Initialize(
			VertexData vertexData,
			VertexLayoutData vertexLayoutData,
			IndexData indexLayoutData,
			const String shaderName,
			void* constantBufferData,
			size_t constantBufferDataSize);

		void Terminate();

		void Draw(Renderer* rendererRef); // Draw(Renderer* renderer);
		

	private:
		// Material
		//	Shader
		//		VertexShader
		//		PixelShader
		//	ConstantBuffers
		// Buffers
		//	VertexBuffer
		//	IndexBuffer
		//
		VertexData* m_VertexData;
		
		VertexLayoutData* m_VertexLayoutData;
		
		IndexData* m_IndexData;
		
		SharedPtr<VertexShader> m_VertexShader;
		
		SharedPtr<PixelShader> m_PixelShader;
		
		UniquePtr<VertexBuffer> m_VertexBuffer;
		
		UniquePtr<IndexBuffer> m_IndexBuffer;

		UniquePtr<ConstantBuffer> m_ConstantBuffer;
		
		void* m_Constant;
	};
}
