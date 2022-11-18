#pragma once
#include "Buffer.h"
#include "Engine/Graphics/RenderData.h"
#include "Engine/Graphics/Shader/Shader.h"

namespace Engine
{
	class RenderDevice;
	class RenderContext;

	class VertexBuffer final : public Buffer
	{
	public:
		explicit VertexBuffer(ID3D11Device& deviceRef,
					  const RenderData& renderDataRef,
					  const Shader& shaderRef);

		~VertexBuffer() override;
		
		VertexBuffer(const VertexBuffer&)                = delete;
		VertexBuffer& operator=(const VertexBuffer&)     = delete;
		VertexBuffer(VertexBuffer&&) noexcept            = delete;
		VertexBuffer& operator=(VertexBuffer&&) noexcept = delete;

	private:


		ID3D11InputLayout* m_DataLayout;

		friend class RenderContext;
		friend class RenderDevice;
	};
}
