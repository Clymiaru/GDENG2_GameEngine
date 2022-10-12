#pragma once
#include <d3d11.h>

#include "Engine/Graphics/IndexBuffer.h"
#include "Engine/Graphics/PixelShader.h"
#include "Engine/Graphics/VertexBuffer.h"
#include "Engine/Graphics/VertexShader.h"

#include "Engine/Utils/Pointers.h"

namespace Engine
{
	class RenderObject
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

		RenderObject();

		virtual ~RenderObject();

		[[nodiscard]]
		VertexBuffer& GetVertexBuffer() const;

		[[nodiscard]]
		IndexBuffer& GetIndexBuffer() const;

	protected:
		VertexData m_VertexData;

		VertexLayoutData m_VertexLayoutData;

		IndexData m_IndexData;

		SharedPtr<VertexShader> m_VertexShader;

		SharedPtr<PixelShader> m_PixelShader;

		UniquePtr<VertexBuffer> m_VertexBuffer;

		UniquePtr<IndexBuffer> m_IndexBuffer;

	private:
		virtual VertexData InitializeVertexData() = 0;

		virtual VertexLayoutData InitializeVertexLayout() = 0;

		virtual IndexData InitializeIndexData() = 0;

		virtual void InitializeShaderData() = 0;
	};
}
