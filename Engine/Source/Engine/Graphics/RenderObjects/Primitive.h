#pragma once
#include <d3d11.h>

#include "Engine/Core/Core.h"

#include "Engine/Graphics/ConstantBuffer.h"
#include "Engine/Graphics/IndexBuffer.h"
#include "Engine/Graphics/PixelShader.h"
#include "Engine/Graphics/VertexBuffer.h"
#include "Engine/Graphics/VertexShader.h"

namespace Engine
{
	struct Vertex;

	class Primitive
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

		Primitive();

		virtual ~Primitive();

		void Initialize(VertexData vertexData,
		                VertexLayoutData vertexLayoutData,
		                IndexData indexLayoutData,
		                String shaderName);

		void InitializeBuffers(size_t vertexSize,
		                       void* constantBufferData,
		                       size_t constantBufferDataSize);

		void Draw(const void* newConstantData);

		void Terminate() const;

		// [[nodiscard]]
		// VertexBuffer& GetVertexBuffer() const;
		//
		// [[nodiscard]]
		// IndexBuffer& GetIndexBuffer() const;

	private:
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
