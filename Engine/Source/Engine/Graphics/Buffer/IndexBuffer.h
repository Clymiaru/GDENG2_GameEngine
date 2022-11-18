#pragma once
#include "Buffer.h"
#include "Engine/Graphics/RenderData.h"

namespace Engine
{
	class RenderDevice;
	class RenderContext;

	class IndexBuffer final : public Buffer
	{
	public:
		explicit IndexBuffer(ID3D11Device& deviceRef,
					 const RenderData& renderDataRef);
		~IndexBuffer() override;
		
		IndexBuffer(const IndexBuffer&)                = delete;
		IndexBuffer& operator=(const IndexBuffer&)     = delete;
		IndexBuffer(IndexBuffer&&) noexcept            = delete;
		IndexBuffer& operator=(IndexBuffer&&) noexcept = delete;

	private:


		friend class RenderDevice;
		friend class RenderContext;
	};
}
