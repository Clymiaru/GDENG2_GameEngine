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
			Uint* IndexList;

			size_t IndexListCount;
		};

		Primitive();

		virtual ~Primitive();

		[[nodiscard]]
		VertexBuffer& GetVertexBuffer() const;

		[[nodiscard]]
		IndexBuffer& GetIndexBuffer() const;

	protected:
		void InitializeImpl(VertexData vertexData,
		                    VertexLayoutData vertexLayoutData,
		                    IndexData indexLayoutData,
		                    WString shaderName);

		void TerminateImpl() const;

		VertexData* m_VertexData;

		VertexLayoutData* m_VertexLayoutData;

		IndexData* m_IndexData;

		SharedPtr<VertexShader> m_VertexShader;

		SharedPtr<PixelShader> m_PixelShader;

		UniquePtr<VertexBuffer> m_VertexBuffer;

		UniquePtr<IndexBuffer> m_IndexBuffer;

		UniquePtr<ConstantBuffer> m_ConstantBuffer;

	private:
		virtual void InitializeBuffers() = 0;

		virtual std::pair<Vertex*, size_t> CreateVertices() = 0;

		virtual std::pair<D3D11_INPUT_ELEMENT_DESC*, size_t> CreateVertexLayout() = 0;

		virtual std::pair<Uint*, size_t> CreateIndices() = 0;
	};
}
