#pragma once
#include "VertexBuffer.h"

#include "Engine/Utils/Pointers.h"

namespace Engine
{
	class IRenderable final
	{
	public:
		IRenderable(void* listOfVertices,
		            UINT vertexSize,
		            UINT listSize,
		            void* shaderByteCode,
		            UINT byteShaderSize);

		~IRenderable();

		auto GetVertexBuffer() -> const Scope<VertexBuffer>&;

		auto Release() const -> void;

	private:
		Scope<VertexBuffer> m_VertexBuffer;
	};
}
