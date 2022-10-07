#pragma once
#include <d3d11.h>

#include "IndexBuffer.h"
#include "PixelShader.h"
#include "VertexBuffer.h"
#include "VertexShader.h"

#include "Engine/Utils/Pointers.h"

namespace Engine
{
	class ARenderObject
	{
	public:
		ARenderObject();
		virtual ~ARenderObject();

		[[nodiscard]]
		auto GetVertexBuffer() const -> VertexBuffer&;

		[[nodiscard]]
		auto GetIndexBuffer() const -> IndexBuffer&;
		
	protected:

		struct VertexData
		{
			void* VertexList;
			size_t VertexListCount;
			
		} m_VertexData;

		struct VertexLayoutData
		{
			D3D11_INPUT_ELEMENT_DESC* VertexLayout;
			size_t VertexLayoutCount;
		} m_VertexLayoutData;

		struct IndexData
		{
			Uint* IndexList;
			size_t IndexListCount;
		} m_IndexData;
		
		VertexShader* m_VertexShader;
		PixelShader* m_PixelShader;

		UniquePtr<VertexBuffer> m_VertexBuffer;
		UniquePtr<IndexBuffer> m_IndexBuffer;

	private:
		virtual auto InitializeVertexData() -> VertexData = 0;
		virtual auto InitializeVertexLayout() -> VertexLayoutData = 0;
		virtual auto InitializeIndexData() -> IndexData = 0;
		virtual auto InitializeShaderData() -> void = 0;
	};
}
