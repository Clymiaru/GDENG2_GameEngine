#pragma once
#include "Buffer.h"
#include "RenderData.h"
#include "Shader.h"

namespace Engine
{
	class DeviceContext;

	class VertexBuffer final : public Buffer
	{
	public:
		explicit VertexBuffer(const RenderData& renderDataRef,
		                      const Shader& shaderRef);

		~VertexBuffer() override;

		VertexBuffer(const VertexBuffer&) = delete;

		VertexBuffer& operator=(const VertexBuffer&) = delete;

		VertexBuffer(VertexBuffer&&) noexcept = delete;

		VertexBuffer& operator=(VertexBuffer&&) noexcept = delete;

	private:
		ID3D11InputLayout* m_DataLayout;

		friend class DeviceContext;
	};
}
