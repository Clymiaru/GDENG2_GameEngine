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
		IndexBuffer(const IndexBuffer&)                = delete;
		IndexBuffer& operator=(const IndexBuffer&)     = delete;
		IndexBuffer(IndexBuffer&&) noexcept            = delete;
		IndexBuffer& operator=(IndexBuffer&&) noexcept = delete;

	private:
		explicit IndexBuffer(ID3D11Device& deviceRef,
		                     const RenderData& renderDataRef);
		~IndexBuffer() override;

		friend class RenderDevice;
		friend class RenderContext;
	};
}
